/**
	@file
	sy.transform.c
	
	@name
	sy.transform
	
	@realname
	sy.transform
 
	@type
	object
	
	@module
	sy
 
	@author
	Daniele Ghisi
	
	@digest
	Perform translitterations and more general text transformation
	
	@description
	Performs a wide range of transformations on incoming text, including case change, normalization, and translitteration.
	
	@discussion
	
	@category
	sy
 
	@keywords
	transform, normalization, remove, diacritic, latin, convert, translitterate, translitteration, case, change, modify
	
	@seealso
	sy.case, sy.normalize, sy.convert
	
	@owner
	Daniele Ghisi
 */


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h


////////////////////////// object struct
typedef struct _transform
{
    t_sy_object		n_ob;               // the object itself (must be first)
    
    t_symbol		*instructions;		// the instructions as string
    UTransliterator *trans;             // the transformer
    
    char            backwards;
    
    void			*n_outlet1;
    void			*n_outlet2;
} t_transform;



///////////////////////// function prototypes
//// standard set
void *transform_new(t_symbol *s, long argc, t_atom *argv);
void transform_free(t_transform *x);
void transform_assist(t_transform *x, void *b, long m, long a, char *s);

void transform_int(t_transform *x, t_atom_long num);
void transform_float(t_transform *x, double num);
void transform_anything(t_transform *x, t_symbol *msg, long ac, t_atom *av);
void transform_bang(t_transform *x);


t_max_err transform_setattr_instr(t_transform *x, t_object *attr, long ac, t_atom *av);
t_max_err transform_setattr_order(t_transform *x, t_object *attr, long ac, t_atom *av);


//////////////////////// global class pointer variable
void *transform_class;


int C74_EXPORT main(void)
{
    // object initialization, NEW STYLE
    t_class *c;
    
    common_symbols_init();
    
    c = class_new("sy.transform", (method)transform_new, (method)transform_free, (long)sizeof(t_transform),
                  0L /* leave NULL!! */, A_GIMME, 0);
    
    /* you CAN'T call this from the patcher */
    class_addmethod(c, (method)transform_assist,			"assist",		A_CANT, 0);
    
    // @method anything @digest Transform input
    // @description Transforms each individual symbol in the incoming list and outputs the result.
    class_addmethod(c, (method)transform_int,			"int",			A_LONG,		0);
    class_addmethod(c, (method)transform_float,			"float",		A_FLOAT,	0);
    class_addmethod(c, (method)transform_anything,		"list",			A_GIMME,	0);
    class_addmethod(c, (method)transform_anything,		"anything",		A_GIMME,	0);

    // @method getlist @digest Output list of transformations
    // @description Outputs all the allowed transformations from the right outlet.
    class_addmethod(c, (method)transform_anything,			"getlist",	A_GIMME,		0);

    
    // @method bang @digest Perform transformation
    // @description Performs the transformation on the most recently received input list.
    class_addmethod(c, (method)transform_bang,			"bang",			0);
    
    syobj_class_add_numin_attr(c);
    syobj_class_add_numout_attr(c);
    syobj_class_add_maxdecimals_attr(c);
    syobj_class_add_listout_attr(c);
    
    CLASS_ATTR_SYM(c, "instr", 0, t_transform, instructions);
    CLASS_ATTR_STYLE_LABEL(c,"instr",0,"text","Instructions");
    CLASS_ATTR_BASIC(c,"instr",0);
    CLASS_ATTR_ACCESSORS(c, "instr", (method)NULL, (method)transform_setattr_instr);
    // @description Sets the output string format. Choose among the list at
    // http://demo.icu-project.org/icu-bin/convexp (case insensitive).

    
    CLASS_ATTR_CHAR(c, "order", 0, t_transform, backwards);
    CLASS_ATTR_STYLE_LABEL(c,"order",0,"text","Backwards Processing");
    CLASS_ATTR_ACCESSORS(c, "order", (method)NULL, (method)transform_setattr_order);
    // @description Forces processing backwards (from last to first character).

    
    
    class_register(CLASS_BOX, c); /* CLASS_NOBOX */
    transform_class = c;
    
    return 0;
}


void update_transformer(t_transform *x)
{
    systhread_mutex_lock(x->n_ob.l_mutex);
    if (x->trans) {
        utrans_close(x->trans);
        x->trans = NULL;
    }
    
    if (x->instructions) {
        UErrorCode err = U_ZERO_ERROR;
        int32_t rules_len = -1;
        UChar *rules = symbol_to_uchar_array(x->instructions, &rules_len);
        
        x->trans = utrans_openU(rules, -1, x->backwards ? UTRANS_REVERSE : UTRANS_FORWARD, 0, -1, NULL, &err);
//        printf("%s\n", u_errorName(errorcode));
        
//        utrans_register(lator, &errorcode);
//        printf("%s\n", u_errorName(errorcode));
        
        
        
        
        if (err != U_ZERO_ERROR) {
            object_error((t_object *)x, "Can't create transformer for instructions \"%s\".", x->instructions->s_name);
            x->trans = NULL;
            goto end;
        }
    }
    
end:
    systhread_mutex_unlock(x->n_ob.l_mutex);
}


t_max_err transform_setattr_instr(t_transform *x, t_object *attr, long ac, t_atom *av)
{
    x->instructions = symbol_from_gimme(ac, av);
    update_transformer(x);
    return MAX_ERR_NONE;
}

t_max_err transform_setattr_order(t_transform *x, t_object *attr, long ac, t_atom *av)
{
    x->backwards = (ac && atom_gettype(av) == A_LONG && atom_getlong(av) ? 1 : 0);
    update_transformer(x);
    return MAX_ERR_NONE;
}



void transform_assist(t_transform *x, void *b, long m, long a, char *s)
{
    if (m == ASSIST_INLET) { // @in 0 @type symbol/list @digest Incoming symbol or list
        sprintf(s, "Incoming symbol");
    }
    else {	// @out 0 @type symbol/list @digest transformed symbols
        sprintf(s, "Transformed symbols");
    }
}

void transform_free(t_transform *x)
{
    if (x->trans)
        utrans_close(x->trans);
    syobj_obj_free((t_sy_object *)x);
}


void *transform_new(t_symbol *s, long argc, t_atom *argv)
{
    t_transform *x = NULL;
    long true_ac = attr_args_offset(argc, argv);
    
    if ((x = (t_transform *)object_alloc(transform_class))) {
        
        // @arg 0 @name instructions @optional 1 @type symbol @digest Output encoding
        // @description The optional argument sets the value for the "mode" attribute.
        // This can be either the integer value of the attribute, or one of the following
        // symbols: "NFD", "NFKD", "NFC", "NFKC", "FCD".
        
        x->instructions = gensym("Any-Null");
        x->trans = NULL;
        
        if (true_ac)
            x->instructions = symbol_from_gimme(true_ac, argv);
        
        syobj_obj_setup((t_sy_object *)x, 1);
        
        attr_args_process(x, argc, argv);
        
        update_transformer(x);
        
        x->n_outlet2 = syout((t_object *)x);
        x->n_outlet1 = syout((t_object *)x);
    }
    return (x);
}

void transform_int(t_transform *x, t_atom_long num)
{
    t_atom argv[1];
    atom_setlong(argv, num);
    transform_anything(x, _sym_list, 1, argv);
}

void transform_float(t_transform *x, double num)
{
    t_atom argv[1];
    atom_setfloat(argv, num);
    transform_anything(x, _sym_list, 1, argv);
}

void transform_bang(t_transform *x)
{
    transform_anything(x, _sym_bang, 0, NULL);
}

void transform_anything(t_transform *x, t_symbol *msg, long ac, t_atom *av)
{
    long	stored_ac, out_ac;
    t_atom	*stored_av = NULL;
    t_atom	*out_av = NULL;

    if (msg == gensym("getlist")) {
        UErrorCode err = U_ZERO_ERROR;
        UEnumeration *all = utrans_openIDs (&err);
        const char *c;
        t_atom av;
        while ((c = uenum_next (all, 0, &err))) {
            atom_setsym(&av, gensym(c));
            sy_outlet(x->n_outlet2, NULL, 1, &av);
        }
        return;
    }
    
    if (msg != _sym_bang)
        syobj_store_content((t_sy_object *) x, msg, ac, av, 0);
    
    stored_ac = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_MODE, &stored_av);
    
    systhread_mutex_lock(x->n_ob.l_mutex);
    out_ac = iterate_on_gimme((t_sy_object *) x, NULL, stored_ac, stored_av, &out_av, (atom_modif_fn)transform_fn, x->trans, NULL, NULL);
    systhread_mutex_unlock(x->n_ob.l_mutex);
    
    syobj_atom_array_reparse_account_for_numout((t_sy_object *)x, out_ac, out_av);
    syobj_atom_array_reparse_account_for_listout((t_sy_object *)x, &out_ac, &out_av);
    
    if (out_ac > 0)
        sy_outlet(x->n_outlet1, NULL, out_ac, out_av);
    
    sysmem_freeptr(stored_av);
    sysmem_freeptr(out_av);
}
