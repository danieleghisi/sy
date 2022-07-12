/**
	@file
	sy.insert.c
	
	@name 
	sy.insert
	
	@realname 
	sy.insert

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	Insert characters
	
	@description
	Insert characters at specific positions of input symbols.
	
	@discussion
	
	@category
	sy

	@keywords
	insert, wedge
	
	@seealso
	sy.subs, sy.nth, combine, sprintf
	
	@owner
	Daniele Ghisi
*/


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h


////////////////////////// object struct
typedef struct _insert 
{
	t_sy_object		n_ob;		// the object itself (must be first)

    t_symbol        *n_pad;     // padding character
    
	long			n_in;   // space for the inlet number used by all the proxies
    void			*n_proxy1;
    void			*n_proxy2;

	void			*n_outlet;
} t_insert;


typedef struct _insert_helper
{
    long    positions_ac;
    long    positions_av;
    t_symbol    *insertion;
    t_symbol    *pad;
} t_insert_helper;


///////////////////////// function prototypes
//// standard set
void *insert_new(t_symbol *s, long argc, t_atom *argv);
void insert_free(t_insert *x);
void insert_assist(t_insert *x, void *b, long m, long a, char *s);

void insert_int(t_insert *x, t_atom_long num);
void insert_float(t_insert *x, double num);
void insert_anything(t_insert *x, t_symbol *msg, long ac, t_atom *av);
void insert_bang(t_insert *x);
	

	
//////////////////////// global class pointer variable
void *insert_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();

	c = class_new("sy.insert", (method)insert_new, (method)insert_free, (long)sizeof(t_insert), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)insert_assist,			"assist",		A_CANT, 0);  

	// @method anything @digest Function depends on inlet
	// @description The characters defined via the third inlet
	// will be inserted to anything coming in the first inlet, and the result will be output.
	// Anything in the third inlet sets the characters to be inserted to the input data.
	class_addmethod(c, (method)insert_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)insert_float,		"float",		A_FLOAT,	0);
	class_addmethod(c, (method)insert_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)insert_anything,		"anything",		A_GIMME,	0);

	// @method clear @digest Insert no characters
	// @description A <m>clear</m> symbol in the third inlet will force no characters to be inserted.
	class_addmethod(c, (method)insert_anything,		"clear",		A_GIMME,	0);

	// @method bang @digest Perform insertion on last input
	// @description Performs the operation of the most recently received input data.
	class_addmethod(c, (method)insert_bang,			"bang",			0);

	syobj_class_add_numout_attr(c);
    syobj_class_add_listin_attr(c);
    syobj_class_add_listout_attr(c);

    CLASS_ATTR_SYM(c, "pad", 0, t_insert, n_pad);
    CLASS_ATTR_STYLE_LABEL(c,"pad",0,"text","Padding Character");
    CLASS_ATTR_BASIC(c,"pad",0);
    // @description Sets a padding character

	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	insert_class = c;

	return 0;
}


void insert_assist(t_insert *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type anything @digest Incoming symbol or list
        if (a == 0)
            sprintf(s, "Incoming symbol or list");
        else if (a == 1)
            sprintf(s, "int: Insertion position");
        else
            sprintf(s, "Characters to be inserted");
	}
	else {	// @out 0 @type anything @digest Symbols with inserted characters
		sprintf(s, "Symbol or list with inserted characters");
	}
}

void insert_free(t_insert *x)
{
	object_free(x->n_proxy1);
	syobj_obj_free((t_sy_object *)x);
}


void *insert_new(t_symbol *s, long argc, t_atom *argv)
{
	t_insert *x = NULL;
	long true_ac = attr_args_offset(argc, argv);
    
	if ((x = (t_insert *)object_alloc(insert_class))) {
		
        x->n_pad = gensym(" ");
		syobj_obj_setup((t_sy_object *)x, 3);

		// @arg 0 @name position @optional 1 @type int/list @digest Insertion position
		// @description Sets the insertion position, as an integer. Negative integers
        // count from the end; 0 means: no insertion (default).
        // Use a list of integers for multiple insertions
		
		if (true_ac && atom_gettype(argv) == A_LONG)
            syobj_store_content((t_sy_object *)x, NULL, true_ac, argv, 1);

        attr_args_process(x, argc, argv);
		
        x->n_proxy2 = proxy_new((t_object *) x, 2, &x->n_in);
		x->n_proxy1 = proxy_new((t_object *) x, 1, &x->n_in);
		x->n_outlet = syout((t_object *)x);
	}
	return (x);
}

void insert_int(t_insert *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	insert_anything(x, _sym_list, 1, argv);
}

void insert_float(t_insert *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	insert_anything(x, _sym_list, 1, argv);
}

void insert_bang(t_insert *x)
{	
	insert_anything(x, _sym_bang, 0, NULL);
}


long insert_fn(t_sy_object *x, t_atom *atom_in, t_atom *atom_out, void *insert_helper, void *dummy2, void *dummy3)
{
    char type_in = atom_gettype(atom_in);
    t_insert_helper *help = (t_insert_helper *)insert_helper;
    t_symbol *insertion = help->insertion;
    long stored_ac2 = help->positions_ac;
    t_atom *stored_av2 = help->positions_av;
    t_symbol *padsym = help->pad;
    
    if (type_in == A_SYM) {
        t_symbol *sym_in = atom_getsym(atom_in);
        long length_in = symbol_get_num_codepoints_fast(sym_in);
        long positions[MAX(1, stored_ac2)];
        long num_positions = 0;
        for (long i = 0; i < stored_ac2; i++) {
            long l = (atom_gettype(stored_av2 + i) == A_LONG) ? atom_getlong(stored_av2 + i) : 0;
            if (l != 0) {
                positions[i] = l;
                if (positions[i] < 0)
                    positions[i] += length_in + 2;
                num_positions++;
            }
        }
        
        t_symbol *s = NULL;
        if (sym_in && insertion) {
            s = sym_in;
            for (long i = 0; i < num_positions; i++)
                s = symbol_insert(s, positions[i], insertion, padsym, positions, num_positions);
        }
        
        if (s)
            atom_setsym(atom_out, s);
        else
            return 0;
    } else if (type_in == A_LONG || type_in == A_FLOAT) {
        *atom_out = *atom_in;
    } else {
        return 0;
    }
    
    return 1;
}


void insert_anything(t_insert *x, t_symbol *msg, long ac, t_atom *av)
{
	long	stored_ac1, stored_ac2, out_ac;
	t_atom	*stored_av1 = NULL, *stored_av2 = NULL, *out_av = NULL;
	long inlet = proxy_getinlet((t_object *) x);
    t_symbol *padsym = x->n_pad == _sym_none ? NULL : x->n_pad;
	
	if (msg == _sym_clear && (inlet == 1 || inlet == 2))
		syobj_store_content((t_sy_object *) x, NULL, 0, NULL, inlet);
	else if (msg != _sym_bang) 
		syobj_store_content((t_sy_object *) x, msg, ac, av, inlet);
	
    if (inlet == 0) {
		stored_ac1 = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE_ALL_SYMBOLS_AND_ACCOUNT_FOR_LIST_MODE, &stored_av1);
        stored_ac2 = syobj_get_store_contents((t_sy_object *) x, 1, SY_STORE_CLONE, &stored_av2); // address
		t_symbol *insertion = syobj_get_store_contents_as_single_symbol((t_sy_object *) x, 2);

        t_insert_helper helper;
        helper.insertion = insertion;
        helper.pad = padsym;
        helper.positions_ac = stored_ac2;
        helper.positions_av = stored_av2;
        
        out_ac = iterate_on_gimme((t_sy_object *)x, NULL, stored_ac1, stored_av1, &out_av, (atom_modif_fn)insert_fn, &helper, NULL, NULL);
        
		syobj_atom_array_reparse_account_for_numout((t_sy_object *)x, out_ac, out_av);
        syobj_atom_array_reparse_account_for_listout((t_sy_object *)x, &out_ac, &out_av);
		
		if (out_ac > 0)
			sy_outlet(x->n_outlet, NULL, out_ac, out_av);
		
		sysmem_freeptr(stored_av1);
		sysmem_freeptr(stored_av2);
		sysmem_freeptr(out_av);
	}
}
