/**
	@file
	sy.itou.c
	
	@name 
	sy.itou
	
	@realname 
	sy.itou

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	Convert a list of integers (code units) into UTF-8 characters

	@description
	Converts a list of of integers, representing code units, into a symbol (in UTF-8 encoding).
	The input integers can be encoded either in UTF-8, in UTF-16 or in UTF-32.
	
	@discussion
	
	@category
	sy

	@keywords
	convert, unicode, character, code unit, codepoint, encoding, integer
	
	@seealso
	sy.utoi, itoa, spell
	
	@owner
	Daniele Ghisi
*/


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h


////////////////////////// object struct
typedef struct _itou 
{
	t_sy_object		n_ob;		// the object itself (must be first)
	char			input_encoding;
	void			*n_outlet1;
} t_itou;



///////////////////////// function prototypes
//// standard set
void *itou_new(t_symbol *s, long argc, t_atom *argv);
void itou_free(t_itou *x);
void itou_assist(t_itou *x, void *b, long m, long a, char *s);

void itou_int(t_itou *x, t_atom_long num);
void itou_float(t_itou *x, double num);
void itou_anything(t_itou *x, t_symbol *msg, long ac, t_atom *av);
void itou_bang(t_itou *x);
	

	
//////////////////////// global class pointer variable
void *itou_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();

	c = class_new("sy.itou", (method)itou_new, (method)itou_free, (long)sizeof(t_itou), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)itou_assist,			"assist",		A_CANT, 0);  

	// @method list @digest Encode list, output result
	// @description Converts the incoming list of integers into a symbol (in UTF-8 encoding)
	// and outputs it. The input encoding can be chosen via the <m>encoding</m> attribute.
	class_addmethod(c, (method)itou_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)itou_float,		"float",		A_FLOAT,	0);
	class_addmethod(c, (method)itou_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)itou_anything,		"anything",		A_GIMME,	0);

	// @method bang @digest Encode last input list
	// @description Output the encoded result for the most recently received input list.
	class_addmethod(c, (method)itou_bang,			"bang",			0);

	syobj_class_add_numin_attr(c);
	syobj_class_add_numout_attr(c);
	syobj_class_add_maxdecimals_attr(c);	
    syobj_class_add_listout_attr(c);
	
	CLASS_ATTR_CHAR(c, "encoding", 0, t_itou, input_encoding); 
	CLASS_ATTR_STYLE_LABEL(c,"encoding",0,"enumindex","Input Encoding");
	CLASS_ATTR_ENUMINDEX(c,"encoding", 0, "UTF-8 UTF-16 UTF-32"); 
	// @description Sets the input encoding. Default is UTF-32.

	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	itou_class = c;

	return 0;
}


void itou_assist(t_itou *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {  // @in 0 @type list @digest Incoming list of integers (code units)
		sprintf(s, "List of integers (code units)");
	} 
	else {
		sprintf(s, "Encoded symbol"); // @out 0 @type symbol @digest Encoded symbol
	}
}

void itou_free(t_itou *x)
{
	syobj_obj_free((t_sy_object *)x);
}


void *itou_new(t_symbol *s, long argc, t_atom *argv)
{
	t_itou *x = NULL;
    
	if ((x = (t_itou *)object_alloc(itou_class))) {
		x->input_encoding = SY_UTF_32;
		
        syobj_obj_setup((t_sy_object *)x, 1);

        attr_args_process(x, argc, argv);
		
		x->n_outlet1 = syout((t_object *)x);
	}
	return (x);
}

void itou_int(t_itou *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	itou_anything(x, _sym_list, 1, argv);
}

void itou_float(t_itou *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	itou_anything(x, _sym_list, 1, argv);
}

void itou_bang(t_itou *x)
{	
	itou_anything(x, _sym_bang, 0, NULL);
}

void itou_anything(t_itou *x, t_symbol *msg, long ac, t_atom *av)
{
	long	stored_ac = 0, i;
	t_atom	*stored_av = NULL;
	t_symbol *out_sym = NULL;
	
	if (msg != _sym_bang)
		syobj_store_content((t_sy_object *) x, msg, ac, av, 0);
	
	stored_ac = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_DONT_CLONE, &stored_av);
	
	if (stored_ac <= 0)
		return;
	
	switch (x->input_encoding) {
		case SY_UTF_8:
		{
			char *buf, *cur;
			t_atom *cur_av;
			buf = (char *)sysmem_newptr((stored_ac + 1) * sizeof(char));
			for (cur = buf, cur_av = stored_av, i = 0; i < stored_ac; i++, cur++, cur_av++) 
				*cur = atom_getlong(cur_av);
			buf[stored_ac] = 0;
			out_sym = gensym(buf);
			sysmem_freeptr(buf);
			break;
		}
		case SY_UTF_16:
		{
			UChar *buf, *cur;
			t_atom *cur_av;
			buf = (UChar *)sysmem_newptr((stored_ac + 1) * sizeof(UChar));
			for (cur = buf, cur_av = stored_av, i = 0; i < stored_ac; i++, cur++, cur_av++) 
				*cur = atom_getlong(cur_av);
			buf[stored_ac] = 0;
			
			out_sym = symbol_from_uchar_array(buf, stored_ac+1);
			sysmem_freeptr(buf);
			break;
		}
		case SY_UTF_32:
		{
			UChar32 *buf, *cur;
			t_atom *cur_av;
			buf = (UChar32 *)sysmem_newptr((stored_ac + 1) * sizeof(UChar32));
			for (cur = buf, cur_av = stored_av, i = 0; i < stored_ac; i++, cur++, cur_av++) 
				*cur = atom_getlong(cur_av);
			buf[stored_ac] = 0;
			
			out_sym = symbol_from_uchar32_array(buf, stored_ac+1);
			sysmem_freeptr(buf);
			break;
		}
	}
		
	if (out_sym) {
        long ac_out = 1;
		t_atom *av_out = (t_atom *)sysmem_newptr(1 * sizeof(t_atom));
		atom_setsym(av_out, out_sym);

        syobj_atom_array_reparse_account_for_numout((t_sy_object *)x, ac_out, av_out);
        syobj_atom_array_reparse_account_for_listout((t_sy_object *)x, &ac_out, &av_out);

		sy_outlet(x->n_outlet1, NULL, ac_out, av_out);
        
        sysmem_freeptr(av_out);
	}
}
