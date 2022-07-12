/**
	@file
	sy.prepend.c
	
	@name 
	sy.prepend
	
	@realname 
	sy.prepend

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	Prepend characters
	
	@description
	Prepend characters to input symbols.
	
	@discussion
	
	@category
	sy

	@keywords
	prepend, join
	
	@seealso
	sy.append, combine
	
	@owner
	Daniele Ghisi
*/


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h


////////////////////////// object struct
typedef struct _prepend 
{
	t_sy_object		n_ob;		// the object itself (must be first)

	long			n_in;   // space for the inlet number used by all the proxies
    void			*n_proxy1;

	void			*n_outlet;
} t_prepend;



///////////////////////// function prototypes
//// standard set
void *prepend_new(t_symbol *s, long argc, t_atom *argv);
void prepend_free(t_prepend *x);
void prepend_assist(t_prepend *x, void *b, long m, long a, char *s);

void prepend_int(t_prepend *x, t_atom_long num);
void prepend_float(t_prepend *x, double num);
void prepend_anything(t_prepend *x, t_symbol *msg, long ac, t_atom *av);
void prepend_bang(t_prepend *x);
	

t_max_err prepend_setattr_mode(t_prepend *x, t_object *attr, long ac, t_atom *av);

	
//////////////////////// global class pointer variable
void *prepend_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();

	c = class_new("sy.prepend", (method)prepend_new, (method)prepend_free, (long)sizeof(t_prepend), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)prepend_assist,			"assist",		A_CANT, 0);  

	// @method anything @digest Function depends on inlet
	// @description The characters defined by the argument or via the right inlet
	// will be prepended to anything coming in the left inlet, and the result will be output.
	// Anything in the right inlet sets the characters to be prepended to the input data.
	class_addmethod(c, (method)prepend_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)prepend_float,			"float",		A_FLOAT,	0);
	class_addmethod(c, (method)prepend_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)prepend_anything,		"anything",		A_GIMME,	0);

	// @method clear @digest Prepend no characters
	// @description A <m>clear</m> symbol in the right inlet will force no characters to be prepended.
	class_addmethod(c, (method)prepend_anything,		"clear",		A_GIMME,	0);

	// @method bang @digest Prepend character to last input
	// @description Performs the operation of the most recently received input data.
	class_addmethod(c, (method)prepend_bang,			"bang",			0);

	syobj_class_add_numin_attr(c);
	syobj_class_add_numout_attr(c);
	syobj_class_add_maxdecimals_attr(c);
    syobj_class_add_listin_attr(c);
    syobj_class_add_listout_attr(c);

	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	prepend_class = c;

	return 0;
}


void prepend_assist(t_prepend *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type anything @digest Incoming symbol or list
		sprintf(s, "Incoming symbol or list");
	} 
	else {	// @out 0 @type anything @digest Symbols with prepended characters
		sprintf(s, "Symbol or list with prepended characters"); 			
	}
}

void prepend_free(t_prepend *x)
{
	object_free(x->n_proxy1);
	syobj_obj_free((t_sy_object *)x);
}


void *prepend_new(t_symbol *s, long argc, t_atom *argv)
{
	t_prepend *x = NULL;
	long true_ac = attr_args_offset(argc, argv);
    
	if ((x = (t_prepend *)object_alloc(prepend_class))) {
		
		syobj_obj_setup((t_sy_object *)x, 2);

		// @arg 0 @name chars @optional 1 @type anything @digest Characters to prepend
		// @description Sets the initial characters to be prepended to the input (also see <m>anything</m> method, right inlet).
		
		if (true_ac)
			syobj_store_content((t_sy_object *)x, NULL, true_ac, argv, 1);

        attr_args_process(x, argc, argv);
		
		x->n_proxy1 = proxy_new((t_object *) x, 1, &x->n_in);
		x->n_outlet = syout((t_object *)x);
	}
	return (x);
}

void prepend_int(t_prepend *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	prepend_anything(x, _sym_list, 1, argv);
}

void prepend_float(t_prepend *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	prepend_anything(x, _sym_list, 1, argv);
}

void prepend_bang(t_prepend *x)
{	
	prepend_anything(x, _sym_bang, 0, NULL);
}

long prepend_fn(t_sy_object *x, t_atom *atom_in, t_atom *atom_out, void *symbol, void *dummy1, void *dummy2)
{
    char type_in = atom_gettype(atom_in);
    t_symbol *sym = ((t_symbol *)symbol);
    
    if (type_in == A_SYM) {
        atom_setsym(atom_out, symbol_join(sym, atom_getsym(atom_in)));
    } else if (type_in == A_LONG || type_in == A_FLOAT) {
        *atom_out = *atom_in;
    } else {
        return 0;
    }
    
    return 1;
}


void prepend_anything(t_prepend *x, t_symbol *msg, long ac, t_atom *av)
{
	long	stored_ac1, stored_ac2, out_ac;
	t_atom	*stored_av1 = NULL, *stored_av2 = NULL, *out_av = NULL;
	long inlet = proxy_getinlet((t_object *) x);
	
	if (msg == _sym_clear && inlet == 1)
		syobj_store_content((t_sy_object *) x, NULL, 0, NULL, 1);
	else if (msg != _sym_bang) 
		syobj_store_content((t_sy_object *) x, msg, ac, av, inlet);
	
	if (inlet == 0) {
        if (x->n_ob.l_listin_mode == SY_LISTIN_MODE_GLOBALLY) {
            stored_ac1 = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_MODE, &stored_av1);
            stored_ac2 = syobj_get_store_contents((t_sy_object *) x, 1, SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_MODE, &stored_av2);
            
            if (!stored_ac1 || !stored_ac2 || atom_gettype(stored_av1 + stored_ac1 - 1) != A_SYM || atom_gettype(stored_av2) != A_SYM) {
                out_ac = atom_array_join(stored_ac2, stored_av2, stored_ac1, stored_av1, &out_av);
            } else {
                out_ac = atom_array_join(stored_ac2, stored_av2, stored_ac1 - 1, stored_av1 + 1, &out_av);
                atom_setsym(out_av + stored_ac2 - 1, symbol_join(atom_getsym(out_av + stored_ac2 - 1), atom_getsym(stored_av1)));
            }
        } else {
            stored_ac1 = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_MODE, &stored_av1);
            t_symbol *to_append = syobj_get_store_contents_as_single_symbol((t_sy_object *) x, 1);
            out_ac = iterate_on_gimme((t_sy_object *)x, NULL, stored_ac1, stored_av1, &out_av, (atom_modif_fn)prepend_fn, to_append, NULL, NULL);
        }
        
        syobj_atom_array_reparse_account_for_numout((t_sy_object *)x, out_ac, out_av);
        syobj_atom_array_reparse_account_for_listout((t_sy_object *)x, &out_ac, &out_av);
		
		if (out_ac > 0)
			sy_outlet(x->n_outlet, NULL, out_ac, out_av);
		
		sysmem_freeptr(stored_av1);
		sysmem_freeptr(stored_av2);
		sysmem_freeptr(out_av);
	}
}
