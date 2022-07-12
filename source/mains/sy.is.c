/**
	@file
	sy.is.c
	
	@name 
	sy.is
	
	@realname 
	sy.is

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	Map each character to its category

	@description
	Translates any incoming symbol into a list of numbers or symbols, one for each character, determining the character type.
	
	@discussion
	
	@category
	sy

	@keywords
	is, translate, category, type, character, codepoint
	
	@seealso
	sy.filter
	
	@owner
	Daniele Ghisi
*/


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h


////////////////////////// object struct
typedef struct _is 
{
	t_sy_object		n_ob;		// the object itself (must be first)

	char			output_letter_groups;
	
	void			*n_outlet1;
	void			*n_outlet2;
} t_is;



///////////////////////// function prototypes
//// standard set
void *is_new(t_symbol *s, long argc, t_atom *argv);
void is_free(t_is *x);
void is_assist(t_is *x, void *b, long m, long a, char *s);

void is_int(t_is *x, t_atom_long num);
void is_float(t_is *x, double num);
void is_anything(t_is *x, t_symbol *msg, long ac, t_atom *av);
void is_bang(t_is *x);
	

	
//////////////////////// global class pointer variable
void *is_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();

	c = class_new("sy.is", (method)is_new, (method)is_free, (long)sizeof(t_is), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)is_assist,			"assist",		A_CANT, 0);  

	// @method anything @digest Output character types
	// @description For each character of any incoming symbol, an integer is created in the output list,
	// representing the character type.
	class_addmethod(c, (method)is_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)is_float,		"float",		A_FLOAT,	0);
	class_addmethod(c, (method)is_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)is_anything,		"anything",		A_GIMME,	0);

	// @method bang @digest Output character types of last input
	// @description Output the character types for the most recently received input data.
	class_addmethod(c, (method)is_bang,			"bang",			0);

	syobj_class_add_numin_attr(c);
	syobj_class_add_maxdecimals_attr(c);	

	CLASS_ATTR_CHAR(c, "groups", 0, t_is, output_letter_groups); 
	CLASS_ATTR_STYLE_LABEL(c,"groups",0,"onoff","Output Letter Groups");
	CLASS_ATTR_BASIC(c, "groups", 0); 
	// @description Toggles the ability to only output the letter group (first uppercase letter) in the textual representation of characters.
	// By default this is inactive, so categories are represented by two letters (a uppercase one and a lowercase one, as a further specification)
	
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	is_class = c;

	return 0;
}


void is_assist(t_is *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {  // @in 0 @type symbol/list @digest Incoming symbol or list of symbols
		sprintf(s, "Symbol");
	} 
	else {
		if (a == 0)
			sprintf(s, "list: Character Types as integers"); // @out 0 @type list @digest List of integers representing character types
		else
			sprintf(s, "list: Character Types as symbols"); // @out 1 @type list @digest List of symbols representing character types
	}
}

void is_free(t_is *x)
{
	syobj_obj_free((t_sy_object *)x);
}


void *is_new(t_symbol *s, long argc, t_atom *argv)
{
	t_is *x = NULL;
    
	if ((x = (t_is *)object_alloc(is_class))) {
        syobj_obj_setup((t_sy_object *)x, 1);

        attr_args_process(x, argc, argv);
		
		x->n_outlet2 = syout((t_object *)x);
		x->n_outlet1 = syout((t_object *)x);
	}
	return (x);
}

void is_int(t_is *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	is_anything(x, _sym_list, 1, argv);
}

void is_float(t_is *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	is_anything(x, _sym_list, 1, argv);
}

void is_bang(t_is *x)
{	
	is_anything(x, _sym_bang, 0, NULL);
}


long substitute_with_symbol_fn(t_sy_object *x, t_atom *atom_in, t_atom *atom_out, void *only_output_grouped_letters, void *dummy2, void *dummy3)
{
	char type_in = atom_gettype(atom_in); 
	
	if (type_in == A_LONG) {
		t_symbol *sym = category_to_symbol(atom_getlong(atom_in));
		if (*((char *)only_output_grouped_letters)) {
			char buf[2];
			buf[0] = sym->s_name[0];
			buf[1] = 0;
			sym = gensym(buf);
		}
		atom_setsym(atom_out, sym);
	} else if (type_in == A_LONG || type_in == A_FLOAT) {
		*atom_out = *atom_in;
	} else 
		 return 0;
	return 1;
}


void is_anything(t_is *x, t_symbol *msg, long ac, t_atom *av)
{
	long	stored_ac = 0;
	t_atom	*stored_av = NULL;
	long	i, j;
	char	groups = x->output_letter_groups;
	
	if (msg != _sym_bang) 
		syobj_store_content((t_sy_object *) x, msg, ac, av, 0);
	
	stored_ac = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_MODE, &stored_av);
	
	const long	ALLOCATE_STEP_SIZE = 256;
	t_atom		*out_av = (t_atom *)sysmem_newptr(ALLOCATE_STEP_SIZE * sizeof(t_atom));
	long		num_allocated_elem = ALLOCATE_STEP_SIZE;
	long		out_ac = 0;
	
	for (i = 0; i < stored_ac; i++) {
		if (atom_gettype(stored_av + i) == A_SYM) {
			int32_t buf_size = 0; 
			UChar32 *buf = symbol_to_uchar32_array(atom_getsym(stored_av + i), &buf_size);
			
			for (j = 0; j < buf_size; j++) {
				if (buf[j] == 0)
					break;
				
				atom_setlong(out_av + out_ac++, u_charType(buf[j]));
				
				if (out_ac >= num_allocated_elem) {
					// resize
					num_allocated_elem += ALLOCATE_STEP_SIZE;
					out_av = (t_atom *)sysmem_resizeptr(out_av, num_allocated_elem * sizeof(t_atom));
				}
			}
		} else {
			*(out_av + out_ac++) = *(stored_av + i);
			if (out_ac >= num_allocated_elem) {
				// resize
				num_allocated_elem += ALLOCATE_STEP_SIZE;
				out_av = (t_atom *)sysmem_resizeptr(out_av, num_allocated_elem * sizeof(t_atom));
			}
		}
		
		if (i < stored_ac - 1) {
			atom_setlong(out_av + out_ac++, u_charType(' '));
			if (out_ac >= num_allocated_elem) {
				// resize
				num_allocated_elem += ALLOCATE_STEP_SIZE;
				out_av = (t_atom *)sysmem_resizeptr(out_av, num_allocated_elem * sizeof(t_atom));
			}
		}
	}
	
	if (out_ac > 0) {
		t_atom *out_av2 = NULL;
		long out_ac2 = iterate_on_gimme((t_sy_object *)x, NULL, out_ac, out_av, &out_av2, (atom_modif_fn)substitute_with_symbol_fn, &groups, NULL, NULL);
		
		sy_outlet(x->n_outlet2, NULL, out_ac2, out_av2);
		sy_outlet(x->n_outlet1, NULL, out_ac, out_av);
	}
	sysmem_freeptr(stored_av);
	sysmem_freeptr(out_av);
}
