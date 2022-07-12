/**
	@file
	sy.length.c
	
	@name 
	sy.length
	
	@realname 
	sy.length

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	Length of a symbol
	
	@description
	Counts the number of Unicode codepoints in a symbol.
	
	@discussion
	
	@category
	sy

	@keywords
	get, retrieve, length, character, number, count, size
	
	@seealso
	sy.utoi, atoi
	
	@owner
	Daniele Ghisi
*/


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h


////////////////////////// object struct
typedef struct _length 
{
	t_sy_object		n_ob;		// the object itself (must be first)

	char			nonstandard;
	
    void			*n_outlet;
} t_length;



///////////////////////// function prototypes
//// standard set
void *length_new(t_symbol *s, long argc, t_atom *argv);
void length_free(t_length *x);
void length_assist(t_length *x, void *b, long m, long a, char *s);

void length_int(t_length *x, t_atom_long num);
void length_float(t_length *x, double num);
void length_anything(t_length *x, t_symbol *msg, long ac, t_atom *av);
void length_bang(t_length *x);
	

	
//////////////////////// global class pointer variable
void *length_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();

	c = class_new("sy.length", (method)length_new, (method)length_free, (long)sizeof(t_length), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)length_assist,			"assist",		A_CANT, 0);  

	// @method anything @digest Get the number of characters
	// @description Returns the length of each symbol and outputs the result.
	// The length of a symbol is, more specifically, the number of codepoints of its string, in Unicode representation.
	class_addmethod(c, (method)length_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)length_float,		"float",		A_FLOAT,	0);
	class_addmethod(c, (method)length_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)length_anything,		"anything",		A_GIMME,	0);

	// @method bang @digest Return the length
	// @description Returns the length of each symbol in the most recently received input list.
	class_addmethod(c, (method)length_bang,			"bang",			0);

	syobj_class_add_numin_attr(c);
	syobj_class_add_maxdecimals_attr(c);	
    syobj_class_add_listin_attr(c);

	CLASS_ATTR_CHAR(c, "nonstandard", 0, t_length, nonstandard);
	CLASS_ATTR_STYLE_LABEL(c,"nonstandard",0,"onoff","Count Non-Standard Characters");
	// @description Toggles the ability to count non-standard characters 
	// (e.g. combining marks, control codepoints, space modifiers, control codepoints, etc). Defaults to 0.

	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	length_class = c;

	return 0;
}


void length_assist(t_length *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type symbol/list @digest Incoming symbol or list
		sprintf(s, "Incoming symbol/list");
	} 
	else {	// @out 0 @type int/list @digest Length of incoming symbol, or list of lengths of incoming symbols 
		sprintf(s, "int/list: Number of characters of incoming element(s)"); // @description The length is the number of Unicode codepoints in the symbol string.
	}
}

void length_free(t_length *x)
{
	syobj_obj_free((t_sy_object *)x);
}


void *length_new(t_symbol *s, long argc, t_atom *argv)
{
	t_length *x = NULL;
    
	if ((x = (t_length *)object_alloc(length_class))) {
		x->nonstandard = 0;
		
        syobj_obj_setup((t_sy_object *)x, 1);

        attr_args_process(x, argc, argv);
		
		x->n_outlet = syout((t_object *)x);
	}
	return (x);
}

void length_int(t_length *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	length_anything(x, _sym_list, 1, argv);
}

void length_float(t_length *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	length_anything(x, _sym_list, 1, argv);
}

void length_bang(t_length *x)
{	
	length_anything(x, _sym_bang, 0, NULL);
}

long substitute_with_length_fn(t_sy_object *x, t_atom *atom_in, t_atom *atom_out, void *nonstandard, void *dummy2, void *dummy3)
{
	char type_in = atom_gettype(atom_in); 
	
	if (type_in == A_SYM) {
		atom_setlong(atom_out, (long)symbol_get_num_codepoints(atom_getsym(atom_in), *((char *)nonstandard)));
	} else if (type_in == A_LONG || type_in == A_FLOAT) {
		*atom_out = *atom_in;
	} else {
		return 0;
	}

	return 1;
}


void length_anything(t_length *x, t_symbol *msg, long ac, t_atom *av)
{
	long	stored_ac, out_ac;
	t_atom	*stored_av = NULL;
	t_atom	*out_av = NULL;
	
	if (msg != _sym_bang) 
		syobj_store_content((t_sy_object *) x, msg, ac, av, 0);
	
    stored_ac = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_AND_LIST_MODE, &stored_av);
	
	out_ac = iterate_on_gimme((t_sy_object *) x, NULL, stored_ac, stored_av, &out_av, (atom_modif_fn)substitute_with_length_fn, &x->nonstandard, NULL, NULL);

	if (out_ac > 0)
		sy_outlet(x->n_outlet, NULL, out_ac, out_av);
	
	sysmem_freeptr(stored_av);
	sysmem_freeptr(out_av);
}
