/**
	@file
	sy.rev.c
	
	@name 
	sy.rev
	
	@realname 
	sy.rev

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	Reverse symbols
	
	@description
	Reverses the order of characters in incoming symbols.
	
	@discussion
	
	@category
	sy

	@keywords
	reverse, mirror, backward, inverse, character
	
	@seealso
	sy.rot
	
	@owner
	Daniele Ghisi
*/


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h


////////////////////////// object struct
typedef struct _rev 
{
	t_sy_object		n_ob;		// the object itself (must be first)
	void			*n_outlet;
} t_rev;



///////////////////////// function prototypes
//// standard set
void *rev_new(t_symbol *s, long argc, t_atom *argv);
void rev_free(t_rev *x);
void rev_assist(t_rev *x, void *b, long m, long a, char *s);

void rev_int(t_rev *x, t_atom_long num);
void rev_float(t_rev *x, double num);
void rev_anything(t_rev *x, t_symbol *msg, long ac, t_atom *av);
void rev_bang(t_rev *x);
	

	
//////////////////////// global class pointer variable
void *rev_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();

	c = class_new("sy.rev", (method)rev_new, (method)rev_free, (long)sizeof(t_rev), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)rev_assist,			"assist",		A_CANT, 0);  

	// @method anything @digest Reverse symbols
	// @description Each incoming symbol is reversed, i.e. its characters are read right-to-left.
	// Unless <m>global</m> is set to 0, also the atoms of the incoming list are reversed.
	// Finally, the result is output.
	class_addmethod(c, (method)rev_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)rev_float,		"float",		A_FLOAT,	0);
	class_addmethod(c, (method)rev_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)rev_anything,		"anything",		A_GIMME,	0);

	// @method bang @digest Reverse last input symbols
	// @description Perform the reversal on the most recently received input symbols.
	class_addmethod(c, (method)rev_bang,			"bang",			0);

	syobj_class_add_numin_attr(c);
	syobj_class_add_numout_attr(c);
	syobj_class_add_maxdecimals_attr(c);	
    syobj_class_add_listin_attr(c);
    syobj_class_add_listout_attr(c);

	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	rev_class = c;

	return 0;
}


void rev_assist(t_rev *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type anything @digest Incoming symbols
		sprintf(s, "anything: Incoming symbols");
	} 
	else {	// @out 0 @type anything @digest Reversed input 
		sprintf(s, "anything: Reversed input");
	}
}

void rev_free(t_rev *x)
{
	syobj_obj_free((t_sy_object *)x);
}


void *rev_new(t_symbol *s, long argc, t_atom *argv)
{
	t_rev *x = NULL;
    
	if ((x = (t_rev *)object_alloc(rev_class))) {
		syobj_obj_setup((t_sy_object *)x, 1);

        attr_args_process(x, argc, argv);
		
		x->n_outlet = syout((t_object *)x);
	}
	return (x);
}

void rev_int(t_rev *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	rev_anything(x, _sym_list, 1, argv);
}

void rev_float(t_rev *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	rev_anything(x, _sym_list, 1, argv);
}

void rev_bang(t_rev *x)
{	
	rev_anything(x, _sym_bang, 0, NULL);
}

long substitute_with_rev_fn(t_sy_object *x, t_atom *atom_in, t_atom *atom_out, void *dummy1, void *dummy2, void *dummy3)
{
	char type_in = atom_gettype(atom_in); 
	
	if (type_in == A_SYM) {
		atom_setsym(atom_out, symbol_reverse(atom_getsym(atom_in)));
	} else if (type_in == A_LONG || type_in == A_FLOAT) {
		*atom_out = *atom_in;
	} else {
		return 0;
	}

	return 1;
}


void rev_anything(t_rev *x, t_symbol *msg, long ac, t_atom *av)
{
	long	stored_ac, out_ac;
	t_atom	*stored_av = NULL;
	t_atom	*out_av = NULL;
	
	if (msg != _sym_bang) 
		syobj_store_content((t_sy_object *) x, msg, ac, av, 0);
	
	stored_ac = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_AND_LIST_MODE, &stored_av);
	
	out_ac = iterate_on_gimme((t_sy_object *) x, NULL, stored_ac, stored_av, &out_av, (atom_modif_fn)substitute_with_rev_fn, NULL, NULL, NULL);

	if (x->n_ob.l_listin_mode == SY_LISTIN_MODE_GLOBALLY)
		atom_array_reverse(out_ac, out_av);
	
	syobj_atom_array_reparse_account_for_numout((t_sy_object *)x, out_ac, out_av);
    syobj_atom_array_reparse_account_for_listout((t_sy_object *)x, &out_ac, &out_av);

	if (out_ac > 0)
		sy_outlet(x->n_outlet, NULL, out_ac, out_av);
	
	sysmem_freeptr(stored_av);
	sysmem_freeptr(out_av);
}
