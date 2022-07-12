/**
	@file
	sy.filterempty.c
	
	@name 
	sy.filterempty
	
	@realname 
	sy.filterempty

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	Filter out empty symbols
	
	@description
	Let through every non-empty symbol
	
	@discussion
	
	@category
	sy

	@keywords
	filter, empty, symbol, null, none
	
	@seealso
	sy.filter, sy.nth
	
	@owner
	Daniele Ghisi
*/


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h


////////////////////////// object struct
typedef struct _filterempty 
{
	t_sy_object		n_ob;		// the object itself (must be first)

	void			*n_outlet1;
    void            *n_outlet2;
} t_filterempty;



///////////////////////// function prototypes
//// standard set
void *filterempty_new(t_symbol *s, long argc, t_atom *argv);
void filterempty_free(t_filterempty *x);
void filterempty_assist(t_filterempty *x, void *b, long m, long a, char *s);

void filterempty_int(t_filterempty *x, t_atom_long num);
void filterempty_float(t_filterempty *x, double num);
void filterempty_anything(t_filterempty *x, t_symbol *msg, long ac, t_atom *av);
void filterempty_bang(t_filterempty *x);


	
//////////////////////// global class pointer variable
void *filterempty_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();

	c = class_new("sy.filterempty", (method)filterempty_new, (method)filterempty_free, (long)sizeof(t_filterempty), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)filterempty_assist,			"assist",		A_CANT, 0);  

    
    // @method anything @digest Filter empty symbols
    // @description Any input is let through the first outlet unless it is an empty symbol, in which case a bang is
    // sent through the second outlet.
    class_addmethod(c, (method)filterempty_int,			"int",			A_LONG,		0);
    class_addmethod(c, (method)filterempty_float,		"float",		A_FLOAT,	0);
    class_addmethod(c, (method)filterempty_anything,		"list",			A_GIMME,	0);
    class_addmethod(c, (method)filterempty_anything,		"anything",		A_GIMME,	0);
	class_addmethod(c, (method)filterempty_bang,			"bang",			0);

    
    syobj_class_add_listin_attr(c);
    syobj_class_add_listout_attr(c);

    
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	filterempty_class = c;

	return 0;
}


void filterempty_assist(t_filterempty *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type anything @digest Symbol or list
        sprintf(s, "anything: symbol or list");
    }
	else {
        if (a == 0) // @out 0 @type anything @digest Symbol or list if not empty
            sprintf(s, "Incoming symbol or list, if not empty");
        else  // @out 1 @type bang @digest bang for empty symbols
            sprintf(s, "bang for empty symbols");
	}
}

void filterempty_free(t_filterempty *x)
{
	syobj_obj_free((t_sy_object *)x);
}


void *filterempty_new(t_symbol *s, long argc, t_atom *argv)
{
	t_filterempty *x = NULL;
    
	if ((x = (t_filterempty *)object_alloc(filterempty_class))) {
		
		syobj_obj_setup((t_sy_object *)x, 1);

        attr_args_process(x, argc, argv);
		
		x->n_outlet2 = bangout((t_object *)x);
        x->n_outlet1 = syout((t_object *)x);
	}
	return (x);
}



void filterempty_int(t_filterempty *x, t_atom_long num)
{
    t_atom argv[1];
    atom_setlong(argv, num);
    filterempty_anything(x, _sym_list, 1, argv);
}

void filterempty_float(t_filterempty *x, double num)
{
    t_atom argv[1];
    atom_setfloat(argv, num);
    filterempty_anything(x, _sym_list, 1, argv);
}

void filterempty_bang(t_filterempty *x)
{	
    filterempty_anything(x, _sym_bang, 0, NULL);
}


long filterempty_fn(t_sy_object *x, t_atom *atom_in, t_atom *atom_out, void *dummy1, void *dummy2, void *dummy3)
{
    t_filterempty *fx = (t_filterempty *)x;
    char type_in = atom_gettype(atom_in);
    
    if (type_in == A_SYM) {
        if (atom_getsym(atom_in) == _sym_nothing) {
            outlet_bang(fx->n_outlet2);
            return 0;
        } else
            *atom_out = *atom_in;
    } else if (type_in == A_LONG || type_in == A_FLOAT) {
        *atom_out = *atom_in;
    } else {
        return 0;
    }
    
    return 1;
}


void filterempty_anything(t_filterempty *x, t_symbol *msg, long ac, t_atom *av)
{
    long	stored_ac = 0;
    t_atom	*stored_av = NULL;
    long    listin_mode = x->n_ob.l_listin_mode;
    
    syobj_store_content((t_sy_object *) x, msg, ac, av, 0);
    stored_ac = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE, &stored_av);

    if (stored_ac > 0) {
        if (listin_mode == SY_LISTIN_MODE_GLOBALLY) {
            if (!(stored_ac == 1 && atom_gettype(stored_av) == A_SYM && atom_getsym(stored_av) == _sym_nothing)) {
                syobj_atom_array_reparse_account_for_listout((t_sy_object *)x, &stored_ac, &stored_av);
                sy_outlet(x->n_outlet1, NULL, stored_ac, stored_av);
            } else {
                outlet_bang(x->n_outlet2);
            }
        } else {
            t_atom *out_av = NULL;
            long out_ac = iterate_on_gimme((t_sy_object *)x, NULL, stored_ac, stored_av, &out_av, filterempty_fn, NULL, NULL, NULL);
            syobj_atom_array_reparse_account_for_listout((t_sy_object *)x, &out_ac, &out_av);
            sy_outlet(x->n_outlet1, NULL, out_ac, out_av);
            sysmem_freeptr(out_av);
        }
        
        sysmem_freeptr(stored_av);
    }
}



