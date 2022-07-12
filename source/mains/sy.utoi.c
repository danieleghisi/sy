/**
	@file
	sy.utoi.c
	
	@name 
	sy.utoi
	
	@realname 
	sy.utoi

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	Decode UTF-8 characters into a list of integers (code units)

	@description
	Converts symbols (in UTF-8 encoding), into a list of integers, representing code units.
	The output integers can represent UTF-8, UTF-16 or UTF-32 encoding of each codepoint.
	
	@discussion
	Information about leading and trailing code units is also output from the right outlet.
	
	@category
	sy

	@keywords
	convert, unicode, character, decode, trailing, leading, code unit, codepoint, encoding, integer, output
	
	@seealso
	sy.itou, atoi, spell
	
	@owner
	Daniele Ghisi
*/


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h


////////////////////////// object struct
typedef struct _utoi 
{
	t_sy_object		n_ob;		// the object itself (must be first)
	char			output_encoding;
	void			*n_outlet1;
	void			*n_outlet2;
} t_utoi;



///////////////////////// function prototypes
//// standard set
void *utoi_new(t_symbol *s, long argc, t_atom *argv);
void utoi_free(t_utoi *x);
void utoi_assist(t_utoi *x, void *b, long m, long a, char *s);

void utoi_int(t_utoi *x, t_atom_long num);
void utoi_float(t_utoi *x, double num);
void utoi_anything(t_utoi *x, t_symbol *msg, long ac, t_atom *av);
void utoi_bang(t_utoi *x);
	

	
//////////////////////// global class pointer variable
void *utoi_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();

	c = class_new("sy.utoi", (method)utoi_new, (method)utoi_free, (long)sizeof(t_utoi), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)utoi_assist,			"assist",		A_CANT, 0);  

	// @method anything @digest Decode symbol, output result
	// @description Outputs the incoming list of symbols, each converted with the defined <m>encoding</m>
	// into a sequence of integers. Space between atoms is replaced by a <m>32</m> (space character).
	// For each output integer, another list contains the information whether the integer is a leading integer 
	// (1, if the integer starting the codepoint encoding) or not (0, if the integer is a trailing one). 
	// This latter list is output from the right outlet, then the forme is output from the left one.
	class_addmethod(c, (method)utoi_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)utoi_float,		"float",		A_FLOAT,	0);
	class_addmethod(c, (method)utoi_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)utoi_anything,		"anything",		A_GIMME,	0);

	// @method bang @digest Decode last input symbol
	// @description Output the integer lists for the most recently received input data.
	class_addmethod(c, (method)utoi_bang,			"bang",			0);

	syobj_class_add_numin_attr(c);
	syobj_class_add_maxdecimals_attr(c);	
	
	CLASS_ATTR_CHAR(c, "encoding", 0, t_utoi, output_encoding); 
	CLASS_ATTR_STYLE_LABEL(c,"encoding",0,"enumindex","Output Encoding");
	CLASS_ATTR_ENUMINDEX(c,"encoding", 0, "UTF-8 UTF-16 UTF-32"); 
	// @description Sets the output encoding: default is UTF-32.

	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	utoi_class = c;

	return 0;
}


void utoi_assist(t_utoi *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {  // @in 0 @type symbol/list @digest Incoming symbol or list
		sprintf(s, "Incoming symbol/list");
	} 
	else {	// outlet 
		if (a == 0) // @in 0 @type list @digest List of integer values, depending on the encoding 
			sprintf(s, "List of integers"); 			
		else // @in 1 @type list @digest Leading integer information
			sprintf(s, "1 if leading, 0 if trailing"); //	@description For each element of the list output at left, there's an integer in this list:
															 // 1 if the element starts a codepoint (leading integer), 0 otherwise (trailing integer).
	}
}

void utoi_free(t_utoi *x)
{
	syobj_obj_free((t_sy_object *)x);
}


void *utoi_new(t_symbol *s, long argc, t_atom *argv)
{
	t_utoi *x = NULL;
    
	if ((x = (t_utoi *)object_alloc(utoi_class))) {
		x->output_encoding = SY_UTF_32;
		
        syobj_obj_setup((t_sy_object *)x, 1);

        attr_args_process(x, argc, argv);
		
		x->n_outlet2 = syout((t_object *)x);
		x->n_outlet1 = syout((t_object *)x);
	}
	return (x);
}

void utoi_int(t_utoi *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	utoi_anything(x, _sym_list, 1, argv);
}

void utoi_float(t_utoi *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	utoi_anything(x, _sym_list, 1, argv);
}

void utoi_bang(t_utoi *x)
{	
	utoi_anything(x, _sym_bang, 0, NULL);
}

void utoi_anything(t_utoi *x, t_symbol *msg, long ac, t_atom *av)
{
	long	stored_ac, out_ac, i;
	t_atom	*stored_av = NULL;
	t_atom	*out_av = NULL, *out_av_flags = NULL, *cur_in, *cur_out, *cur_out_flags;
	
	if (msg != _sym_bang)
		syobj_store_content((t_sy_object *) x, msg, ac, av, 0);
	
	stored_ac = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_MODE, &stored_av);
	
	// allocating initial memory 
	const long BUFFER_STEP = 512;
	const long SAFETY = 10;
	long allocated_memory = BUFFER_STEP, j;
	out_ac = 0;
	out_av = (t_atom *)sysmem_newptr(BUFFER_STEP * sizeof(t_atom));
	out_av_flags = (t_atom *)sysmem_newptr(BUFFER_STEP * sizeof(t_atom));
	for (cur_in = stored_av, cur_out = out_av, cur_out_flags = out_av_flags, i = 0; i < stored_ac; i++, cur_in++) {
		if (atom_gettype(cur_in) == A_SYM) {
			t_symbol *sym = atom_getsym(cur_in);
			long len_sym = strlen(sym->s_name);
			switch (x->output_encoding) {
				case SY_UTF_8: // UTF-8: we just copy input values!!
				{
					char *cur = sym->s_name;
					for (j = 0; j < len_sym; j++) {
						atom_setlong(cur_out++, *((unsigned char*)cur));
						atom_setlong(cur_out_flags++, is_utf8_byte_leading(*((unsigned char*)cur)));  
						out_ac++;
						cur++;

						if (out_ac + SAFETY >= allocated_memory) {
							out_av = (t_atom *)sysmem_resizeptr(out_av, (allocated_memory + BUFFER_STEP) * sizeof(t_atom));
							out_av_flags = (t_atom *)sysmem_resizeptr(out_av_flags, (allocated_memory + BUFFER_STEP) * sizeof(t_atom));
							cur_out = &out_av[out_ac];
							cur_out_flags = &out_av_flags[out_ac];
							allocated_memory += BUFFER_STEP;
						}
					}
					break;
				}
				case SY_UTF_16: // UTF-16
				{
					int32_t out_size;
					UChar *buffer = symbol_to_uchar_array(sym, &out_size);
					if (buffer) {
						UChar *cur = buffer;
						for (j = 0; j < out_size; j++) {
							if (*cur == 0)
								break; // terminating char
							
							atom_setlong(cur_out++, *cur);
							atom_setlong(cur_out_flags++, is_utf16_surrogate_leading(*((t_uint32 *)cur))); 
							out_ac++;
							cur++;
							
							if (out_ac + SAFETY >= allocated_memory) {
								out_av = (t_atom *)sysmem_resizeptr(out_av, (allocated_memory + BUFFER_STEP) * sizeof(t_atom));
								out_av_flags = (t_atom *)sysmem_resizeptr(out_av_flags, (allocated_memory + BUFFER_STEP) * sizeof(t_atom));
								cur_out = &out_av[out_ac];
								cur_out_flags = &out_av_flags[out_ac];
								allocated_memory += BUFFER_STEP;
							}
						}
					}
					sysmem_freeptr(buffer);
					break;
				}
				case SY_UTF_32: // UTF-32
				{
					int32_t out_size;
					UChar32 *buffer = symbol_to_uchar32_array(sym, &out_size);
					if (buffer) {
						UChar32 *cur = buffer;
						for (j = 0; j < out_size; j++) {
							if (*cur == 0)
								break; // terminating char
							
							atom_setlong(cur_out++, *cur);
							atom_setlong(cur_out_flags++, 1);
							out_ac++;
							cur++;
							
							if (out_ac + SAFETY >= allocated_memory) {
								out_av = (t_atom *)sysmem_resizeptr(out_av, (allocated_memory + BUFFER_STEP) * sizeof(t_atom));
								out_av_flags = (t_atom *)sysmem_resizeptr(out_av_flags, (allocated_memory + BUFFER_STEP) * sizeof(t_atom));
								cur_out = &out_av[out_ac];
								cur_out_flags = &out_av_flags[out_ac];
								allocated_memory += BUFFER_STEP;
							}
						}
					}
					sysmem_freeptr(buffer);
					break;
				}
				default:
					break;
			}
		} else {
			*cur_out = *cur_in;
			atom_setlong(cur_out_flags++, 1);
			cur_out++;
			cur_in++;
			out_ac++;
		}
		
		if (out_ac + SAFETY >= allocated_memory) {
			out_av = (t_atom *)sysmem_resizeptr(out_av, (allocated_memory + BUFFER_STEP) * sizeof(t_atom));
			out_av_flags = (t_atom *)sysmem_resizeptr(out_av_flags, (allocated_memory + BUFFER_STEP) * sizeof(t_atom));
			cur_out = &out_av[out_ac];
			cur_out_flags = &out_av_flags[out_ac];
			allocated_memory += BUFFER_STEP;
		}
		
		if (i < stored_ac - 1) {
			atom_setlong(cur_out++, 32); // we insert a space char between atoms, as [atoi] does
			atom_setlong(cur_out_flags++, 1);
			out_ac++;
		}
	}
	
	if (out_ac > 0) {
		sy_outlet(x->n_outlet2, NULL, out_ac, out_av_flags);
		sy_outlet(x->n_outlet1, NULL, out_ac, out_av);
	}
	
	sysmem_freeptr(stored_av);
	sysmem_freeptr(out_av);
	sysmem_freeptr(out_av_flags);
}
