/**
	@file
	sy.slice.c
	
	@name 
	sy.slice
	
	@realname 
	sy.slice

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	Split symbol into two
	
	@description
	Splits the incoming symbol into two, according to a split point.
	
	@discussion
	
	@category
	sy

	@keywords
	split, point, slice, divide, two, index
	
	@seealso
	sy.nth, sy.split
	
	@owner
	Daniele Ghisi
*/


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h

////////////////////////// object struct
typedef struct _slice 
{
	t_sy_object		n_ob;		// the object itself (must be first)

	long			index;		// split point
	
	void			*n_outlet1;
	void			*n_outlet2;
} t_slice;



///////////////////////// function prototypes
//// standard set
void *slice_new(t_symbol *s, long argc, t_atom *argv);
void slice_free(t_slice *x);
void slice_assist(t_slice *x, void *b, long m, long a, char *s);

void slice_int(t_slice *x, t_atom_long num);
void slice_float(t_slice *x, double num);
void slice_anything(t_slice *x, t_symbol *msg, long ac, t_atom *av);
void slice_bang(t_slice *x);
	

	
//////////////////////// global class pointer variable
void *slice_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();

	c = class_new("sy.slice", (method)slice_new, (method)slice_free, (long)sizeof(t_slice), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)slice_assist,			"assist",		A_CANT, 0);  

	// @method anything @digest Split symbol into two
	// @description Splits the incoming symbol according to the split point (see <m>index</m> attribute). Outputs
	// the right part from the right outlet, and the left part from the left outlet.
	class_addmethod(c, (method)slice_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)slice_float,			"float",		A_FLOAT,	0);
	class_addmethod(c, (method)slice_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)slice_anything,		"anything",		A_GIMME,	0);

	// @method bang @digest Perform last operation
	// @description Splits the most recently received input symbol.
	class_addmethod(c, (method)slice_bang,			"bang",			0);

	syobj_class_add_numin_attr(c);
	syobj_class_add_numout_attr(c);
	syobj_class_add_maxdecimals_attr(c);
    syobj_class_add_listin_attr(c);
    syobj_class_add_listout_attr(c);
	
	CLASS_ATTR_LONG(c, "index", 0, t_slice, index); 
	CLASS_ATTR_STYLE_LABEL(c,"index",0,"text","Index");
	CLASS_ATTR_BASIC(c,"index",0);
	// @description Sets the index of the split point, that is the position of the first element of the second part of the symbol. 
	// If a negative position is set, it is counted from the end of the symbol.
	
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	slice_class = c;

	return 0;
}


void slice_assist(t_slice *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type symbol @digest Incoming symbol
		sprintf(s, "Incoming symbol");
	} 
	else {	
		if (a == 0) // @in 0 @type symbol @digest Left split part
			sprintf(s, "symbol: Left split part"); 			
		else // @in 1 @type symbol @digest Right split part
			sprintf(s, "symbol: Right split part"); 			
	}
}

void slice_free(t_slice *x)
{
	syobj_obj_free((t_sy_object *)x);
}


void *slice_new(t_symbol *s, long argc, t_atom *argv)
{
	t_slice *x = NULL;
	long true_ac = attr_args_offset(argc, argv);
    
	if ((x = (t_slice *)object_alloc(slice_class))) {
		
		syobj_obj_setup((t_sy_object *)x, 2);

		// @arg 0 @name index @optional 1 @type int @digest Split point
		// @description Sets the initial split point (see <m>index</m> attribute).
		if (true_ac && atom_gettype(argv) == A_LONG)
			x->index = atom_getlong(argv);

        attr_args_process(x, argc, argv);
		
		x->n_outlet2 = syout((t_object *)x);
		x->n_outlet1 = syout((t_object *)x);
	}
	return (x);
}

void slice_int(t_slice *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	slice_anything(x, _sym_list, 1, argv);
}

void slice_float(t_slice *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	slice_anything(x, _sym_list, 1, argv);
}

void slice_bang(t_slice *x)
{	
	slice_anything(x, _sym_bang, 0, NULL);
}

void slice_anything(t_slice *x, t_symbol *msg, long ac, t_atom *av)
{
	long	stored_ac;
	t_atom	*stored_av = NULL;
	t_atom	*out_av1 = NULL, *out_av2 = NULL;
    long c;
    
	if (msg != _sym_bang) 
		syobj_store_content((t_sy_object *) x, msg, ac, av, 0);
	
	stored_ac = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_AND_LIST_MODE, &stored_av);
				
	if (stored_ac > 0) {
        out_av1 = (t_atom *)sysmem_newptr(stored_ac * sizeof(t_atom));
        out_av2 = (t_atom *)sysmem_newptr(stored_ac * sizeof(t_atom));
        for (c = 0; c < stored_ac; c++) {
            if (atom_gettype(stored_av + c) == A_SYM) {
                t_symbol *left = NULL, *right = NULL;
                symbol_slice_at_codepoint(atom_getsym(stored_av + c), x->index, &left, &right);
                atom_setsym(out_av1 + c, left ? left : _sym_nothing);
                atom_setsym(out_av2 + c, right ? right : _sym_nothing);
            } else {
                *(out_av1 + c) = stored_av[c];
                atom_setsym(out_av2 + c, _sym_nothing);
            }
            
        }
        
        long stored_ac1 = stored_ac, stored_ac2 = stored_ac;
        syobj_atom_array_reparse_account_for_numout((t_sy_object *)x, stored_ac1, out_av1);
        syobj_atom_array_reparse_account_for_numout((t_sy_object *)x, stored_ac2, out_av2);

        syobj_atom_array_reparse_account_for_listout((t_sy_object *)x, &stored_ac1, &out_av1);
        syobj_atom_array_reparse_account_for_listout((t_sy_object *)x, &stored_ac2, &out_av2);

        sy_outlet(x->n_outlet2, NULL, stored_ac1, out_av2);
        sy_outlet(x->n_outlet1, NULL, stored_ac2, out_av1);
        
        sysmem_freeptr(out_av1);
        sysmem_freeptr(out_av2);
	}
	sysmem_freeptr(stored_av);
}
