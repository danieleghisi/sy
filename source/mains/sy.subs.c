/**
	@file
	sy.subs.c
	
	@name 
	sy.subs
	
	@realname 
	sy.subs

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	Substitute characters
	
	@description
	Substitute characters at specific positions of input symbols.
	
	@discussion
	
	@category
	sy

	@keywords
	substitute, replace, modify
	
	@seealso
	sy.insert, sy.replace, sy.empty
	
	@owner
	Daniele Ghisi
*/


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h


////////////////////////// object struct
typedef struct _subs 
{
	t_sy_object		n_ob;		// the object itself (must be first)

    t_symbol        *n_pad;     // padding character
    long            n_segment_length;   // length of the segment to be overwritten (default 1)
    
	long			n_in;   // space for the inlet number used by all the proxies
    void			*n_proxy1;
    void			*n_proxy2;

	void			*n_outlet;
} t_subs;


typedef struct _subs_helper
{
    long    positions_ac;
    long    positions_av;
    t_symbol    *replacement;
    t_symbol    *pad;
    long    segment_length;
} t_subs_helper;




///////////////////////// function prototypes
//// standard set
void *subs_new(t_symbol *s, long argc, t_atom *argv);
void subs_free(t_subs *x);
void subs_assist(t_subs *x, void *b, long m, long a, char *s);

void subs_int(t_subs *x, t_atom_long num);
void subs_float(t_subs *x, double num);
void subs_anything(t_subs *x, t_symbol *msg, long ac, t_atom *av);
void subs_bang(t_subs *x);
	

	
//////////////////////// global class pointer variable
void *subs_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();

	c = class_new("sy.subs", (method)subs_new, (method)subs_free, (long)sizeof(t_subs), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)subs_assist,			"assist",		A_CANT, 0);  

	// @method anything @digest Function depends on inlet
	// @description The characters defined by the argument or via the right inlet
	// will be substituted to anything coming in the left inlet, and the result will be output.
	// Anything in the right inlet sets the characters to be subsed to the input data.
	class_addmethod(c, (method)subs_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)subs_float,		"float",		A_FLOAT,	0);
	class_addmethod(c, (method)subs_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)subs_anything,		"anything",		A_GIMME,	0);

	// @method clear @digest Substitute no characters
	// @description A <m>clear</m> symbol in the right inlet will force no characters to be substituted.
	class_addmethod(c, (method)subs_anything,		"clear",		A_GIMME,	0);

	// @method bang @digest Substitute characters to last input
	// @description Performs the operation of the most recently received input data.
	class_addmethod(c, (method)subs_bang,			"bang",			0);

	syobj_class_add_numout_attr(c);
    syobj_class_add_listin_attr(c);
    syobj_class_add_listout_attr(c);

    CLASS_ATTR_SYM(c, "pad", 0, t_subs, n_pad);
    CLASS_ATTR_STYLE_LABEL(c,"pad",0,"text","Padding Character");
    CLASS_ATTR_BASIC(c,"pad",0);
    // @description Sets a padding character

    
    CLASS_ATTR_LONG(c, "size", 0, t_subs, n_segment_length);
    CLASS_ATTR_STYLE_LABEL(c,"size",0,"text","Segment Size");
    CLASS_ATTR_BASIC(c,"size",0);
    // @description Size of the segment to be overwritten. Use 0 to match with the number of replacement characters
    // (true overwriting). Defaults to 1.

	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	subs_class = c;

	return 0;
}


void subs_assist(t_subs *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type anything @digest Incoming symbol or list
        if (a == 0)
            sprintf(s, "Incoming symbol or list");
        else if (a == 1)
            sprintf(s, "int: substitution position");
        else
            sprintf(s, "Replacement characters");
	}
	else {	// @out 0 @type anything @digest Symbol with replaced characters
		sprintf(s, "Symbol or list with replaced characters");
	}
}

void subs_free(t_subs *x)
{
	object_free(x->n_proxy1);
	syobj_obj_free((t_sy_object *)x);
}


void *subs_new(t_symbol *s, long argc, t_atom *argv)
{
	t_subs *x = NULL;
	long true_ac = attr_args_offset(argc, argv);
    
	if ((x = (t_subs *)object_alloc(subs_class))) {
		
        x->n_segment_length = 1;
        x->n_pad = gensym(" ");
		syobj_obj_setup((t_sy_object *)x, 3);

		// @arg 0 @name position @optional 1 @type int/list @digest Substitution position
		// @description Sets the subsion position, as an integer. Negative integers
        // count from the end; 0 means: no subsion (default).
        // Use a list of integers for multiple substitutions.
		
		if (true_ac && atom_gettype(argv) == A_LONG)
            syobj_store_content((t_sy_object *)x, NULL, true_ac, argv, 1);

        attr_args_process(x, argc, argv);
		
        x->n_proxy2 = proxy_new((t_object *) x, 2, &x->n_in);
		x->n_proxy1 = proxy_new((t_object *) x, 1, &x->n_in);
		x->n_outlet = syout((t_object *)x);
	}
	return (x);
}

void subs_int(t_subs *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	subs_anything(x, _sym_list, 1, argv);
}

void subs_float(t_subs *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	subs_anything(x, _sym_list, 1, argv);
}

void subs_bang(t_subs *x)
{	
	subs_anything(x, _sym_bang, 0, NULL);
}


long subs_fn(t_sy_object *x, t_atom *atom_in, t_atom *atom_out, void *subs_helper, void *dummy2, void *dummy3)
{
    char type_in = atom_gettype(atom_in);
    t_subs_helper *help = (t_subs_helper *)subs_helper;
    t_symbol *replacement = help->replacement;
    long stored_ac2 = help->positions_ac;
    t_atom *stored_av2 = help->positions_av;
    t_symbol *padsym = help->pad;
    long segment_length = help->segment_length;
    
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
                    positions[i] += length_in + 1;
                num_positions++;
            }
        }
        
        t_symbol *s = NULL;
        if (sym_in && replacement) {
            s = sym_in;
            for (long i = 0; i < num_positions; i++)
                s = symbol_substitute(s, positions[i], replacement, padsym, segment_length, positions, num_positions);
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


void subs_anything(t_subs *x, t_symbol *msg, long ac, t_atom *av)
{
	long	stored_ac1, stored_ac2, out_ac;
	t_atom	*stored_av1 = NULL, *stored_av2 = NULL, *out_av = NULL;
	long inlet = proxy_getinlet((t_object *) x);
    t_symbol *padsym = x->n_pad == _sym_none ? NULL : x->n_pad;
    long segment_length = x->n_segment_length;
    
    if (msg == _sym_clear && (inlet == 1 || inlet == 2))
        syobj_store_content((t_sy_object *) x, NULL, 0, NULL, inlet);
	else if (msg != _sym_bang)
		syobj_store_content((t_sy_object *) x, msg, ac, av, inlet);
	
    if (inlet == 0) {
        stored_ac1 = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE_ALL_SYMBOLS_AND_ACCOUNT_FOR_LIST_MODE, &stored_av1);
        stored_ac2 = syobj_get_store_contents((t_sy_object *) x, 1, SY_STORE_CLONE, &stored_av2);
        t_symbol *replacement = syobj_get_store_contents_as_single_symbol((t_sy_object *) x, 2);
        
        t_subs_helper helper;
        helper.replacement = replacement;
        helper.pad = padsym;
        helper.positions_ac = stored_ac2;
        helper.positions_av = stored_av2;
        helper.segment_length = segment_length;
        
        out_ac = iterate_on_gimme((t_sy_object *)x, NULL, stored_ac1, stored_av1, &out_av, (atom_modif_fn)subs_fn, &helper, NULL, NULL);

        syobj_atom_array_reparse_account_for_numout((t_sy_object *)x, out_ac, out_av);
        syobj_atom_array_reparse_account_for_listout((t_sy_object *)x, &out_ac, &out_av);
        
        if (out_ac > 0)
            sy_outlet(x->n_outlet, NULL, out_ac, out_av);
        
        sysmem_freeptr(stored_av1);
        sysmem_freeptr(stored_av2);
        sysmem_freeptr(out_av);
    }
}
