/**
	@file
	sy.join.c
	
	@name 
	sy.join
	
	@realname 
	sy.join

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	Join characters
	
	@description
	Join characters of input symbols.
	
	@discussion
	
	@category
	sy

	@keywords
	join, append, combine
	
	@seealso
	sy.append, sy.prepend, combine, sprintf
	
	@owner
	Daniele Ghisi
*/


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h
#define SY_JOIN_MAX_INLETS 256

////////////////////////// object struct
typedef struct _join 
{
	t_sy_object		n_ob;		// the object itself (must be first)

	long			n_in;   // space for the inlet number used by all the proxies
    long			n_proxies;
    void			**n_proxy;
    long			n_triggers[SY_JOIN_MAX_INLETS];
    long			n_ntriggers;

	void			*n_outlet;
} t_join;



///////////////////////// function prototypes
//// standard set
void *join_new(t_symbol *s, long argc, t_atom *argv);
void join_free(t_join *x);
void join_assist(t_join *x, void *b, long m, long a, char *s);
void join_inletinfo(t_join *x, void *b, long a, char *t);

void join_int(t_join *x, t_atom_long num);
void join_float(t_join *x, double num);
void join_anything(t_join *x, t_symbol *msg, long ac, t_atom *av);
void join_bang(t_join *x);
	

t_max_err join_setattr_mode(t_join *x, t_object *attr, long ac, t_atom *av);

	
//////////////////////// global class pointer variable
void *join_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();

	c = class_new("sy.join", (method)join_new, (method)join_free, (long)sizeof(t_join), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)join_assist,			"assist",		A_CANT, 0);  
    class_addmethod(c, (method)join_inletinfo,	"inletinfo",	A_CANT,		0);

	// @method anything @digest Function depends on inlet
	// @description The characters defined by the argument or via the right inlet
	// will be joined to anything coming in the left inlet, and the result will be output.
	// Anything in the right inlet sets the characters to be joined to the input data.
	class_addmethod(c, (method)join_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)join_float,			"float",		A_FLOAT,	0);
	class_addmethod(c, (method)join_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)join_anything,		"anything",		A_GIMME,	0);

	// @method clear @digest join no characters
	// @description A <m>clear</m> symbol in the right inlet will force no characters to be joined.
	class_addmethod(c, (method)join_anything,		"clear",		A_GIMME,	0);

	// @method bang @digest join character to last input
	// @description Performs the operation of the most recently received input data.
	class_addmethod(c, (method)join_bang,			"bang",			0);

	syobj_class_add_numin_attr(c);
	syobj_class_add_numout_attr(c);
	syobj_class_add_maxdecimals_attr(c);
    syobj_class_add_listout_attr(c);

    
    CLASS_ATTR_LONG_VARSIZE(c, "triggers",	0,	t_join, n_triggers, n_ntriggers, SY_JOIN_MAX_INLETS);
    CLASS_ATTR_LABEL(c, "triggers", 0, "Triggers");
    CLASS_ATTR_FILTER_CLIP(c, "triggers", -1, SY_JOIN_MAX_INLETS);
    // @description A list setting which inlets are "hot" (i.e., which will will trigger the result).
    // <m>0</m> means all inlets are hot. No arguments mean all inlets are cold. Default is 1.

    
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	join_class = c;

	return 0;
}


void join_assist(t_join *x, void *b, long m, long a, char *s)
{
    if (m == ASSIST_INLET) { // @in 0 @loop 1  @type anything @digest Incoming symbol or list to be joined to the others
        sprintf(s, "Symbol or list to be joined");
	} else {	// @out 0 @type anything @digest Symbols with joined characters
		sprintf(s, "Symbol or list with joined characters"); 			
	}
}

void join_free(t_join *x)
{
    long i;
    for (i = x->n_proxies; i > 0; i--)
        object_free(x->n_proxy[i]);
    sysmem_freeptr(x->n_proxy);
	syobj_obj_free((t_sy_object *)x);
}


void *join_new(t_symbol *s, long argc, t_atom *argv)
{
	t_join *x = NULL;
	long true_ac = attr_args_offset(argc, argv);
    long i, proxies = 0;

	if ((x = (t_join *)object_alloc(join_class))) {
		
        // @arg 0 @name count @optional 1 @type int @digest Number of inlets
        proxies = true_ac ? MAX(atom_getlong(argv) - 1, 0) : 1;
        x->n_ntriggers = 1;
        x->n_triggers[0] = 1;

        
		syobj_obj_setup((t_sy_object *)x, proxies + 1);

        attr_args_process(x, argc, argv);
		
        x->n_proxies = MIN(proxies, SY_JOIN_MAX_INLETS);
        
        x->n_proxy = (void **) sysmem_newptr((x->n_proxies + 1) * sizeof (void *));
        for (i = x->n_proxies; i > 0; i--)
            x->n_proxy[i] = proxy_new((t_object *) x, i, &x->n_in);

		x->n_outlet = syout((t_object *)x);
	}
	return (x);
}

void join_int(t_join *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	join_anything(x, _sym_list, 1, argv);
}

void join_float(t_join *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	join_anything(x, _sym_list, 1, argv);
}

void join_bang(t_join *x)
{	
	join_anything(x, _sym_bang, 0, NULL);
}


long join_ishot(t_join *x, long inlet)
{
    long hot = 0, i;
    // should be locked
    if (x->n_ntriggers == 0)
        hot = inlet == 0;
    else {
        for (i = 0; !hot && i < x->n_ntriggers; i++)
            if (x->n_triggers[i] < 1 || x->n_triggers[i] == inlet + 1)
                hot = 1;
    }
    return hot;
}


void join_inletinfo(t_join *x, void *b, long a, char *t)
{
    *t = !join_ishot(x, a);
}


void join_anything(t_join *x, t_symbol *msg, long ac, t_atom *av)
{
	long	out_ac = 0;
	t_atom	*out_av = NULL;
	long inlet = proxy_getinlet((t_object *) x);
    long count = x->n_proxies + 1;

	if (msg == _sym_clear && inlet == 1)
		syobj_store_content((t_sy_object *) x, NULL, 0, NULL, 1);
	else if (msg != _sym_bang) 
		syobj_store_content((t_sy_object *) x, msg, ac, av, inlet);
	
	if (join_ishot(x, inlet)) {
        for (long i = 0; i < count; i++) {
            t_atom *stored_av = NULL;
            long stored_ac = syobj_get_store_contents((t_sy_object *) x, i, SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_MODE, &stored_av);
            t_atom *new_av = NULL;
            long new_ac = 0;
            if (!out_ac || !stored_ac || atom_gettype(stored_av) != A_SYM) {
                new_ac = atom_array_join(out_ac, out_av, stored_ac, stored_av, &new_av);
            } else {
                new_ac = atom_array_join(out_ac, out_av, stored_ac - 1, stored_av + 1, &new_av);
                atom_setsym(new_av + out_ac - 1, symbol_join(atom_getsym(new_av + out_ac - 1), atom_getsym(stored_av)));
            }
            
            if (out_av)
                sysmem_freeptr(out_av);
            if (stored_av)
                sysmem_freeptr(stored_av);
            out_av = new_av;
            out_ac = new_ac;
        }
		
		syobj_atom_array_reparse_account_for_numout((t_sy_object *)x, out_ac, out_av);
        syobj_atom_array_reparse_account_for_listout((t_sy_object *)x, &out_ac, &out_av);
		
		if (out_ac > 0)
			sy_outlet(x->n_outlet, NULL, out_ac, out_av);
		
		sysmem_freeptr(out_av);
	}
}
