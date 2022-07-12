/**
	@file
	sy.convert.c
	
	@name
	sy.convert
	
	@realname
	sy.convert
 
	@type
	object
	
	@module
	sy
 
	@author
	Daniele Ghisi
	
	@digest
	Perform encoding conversions
	
	@description
	Converts the encoding of the incoming Unicode sequence.
	
	@discussion
	
	@category
	sy
 
	@keywords
	convert, normalization, remove, diacritic, ascii, toascii
	
	@seealso
	sy.transform, sy.normalize, sy.utoi
	
	@owner
	Daniele Ghisi
 */


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h


////////////////////////// object struct
typedef struct _convert
{
    t_sy_object		n_ob;		// the object itself (must be first)
    
    t_symbol		*from;          // the input encoding
    t_symbol		*to;            // the output encoding
    t_symbol		*subsseq;		// the substitution sequence
    UConverter      *conv_from;
    UConverter      *conv_to;

    
    void			*n_outlet1;
    void			*n_outlet2;
} t_convert;



///////////////////////// function prototypes
//// standard set
void *convert_new(t_symbol *s, long argc, t_atom *argv);
void convert_free(t_convert *x);
void convert_assist(t_convert *x, void *b, long m, long a, char *s);

void convert_int(t_convert *x, t_atom_long num);
void convert_float(t_convert *x, double num);
void convert_anything(t_convert *x, t_symbol *msg, long ac, t_atom *av);
void convert_bang(t_convert *x);


t_max_err convert_setattr_from(t_convert *x, t_object *attr, long ac, t_atom *av);
t_max_err convert_setattr_to(t_convert *x, t_object *attr, long ac, t_atom *av);
t_max_err convert_setattr_subseq(t_convert *x, t_object *attr, long ac, t_atom *av);


//////////////////////// global class pointer variable
void *convert_class;


int C74_EXPORT main(void)
{
    // object initialization, NEW STYLE
    t_class *c;
    
    common_symbols_init();
    
    c = class_new("sy.convert", (method)convert_new, (method)convert_free, (long)sizeof(t_convert),
                  0L /* leave NULL!! */, A_GIMME, 0);
    
    /* you CAN'T call this from the patcher */
    class_addmethod(c, (method)convert_assist,			"assist",		A_CANT, 0);
    
    // @method anything @digest Convert symbols
    // @description Converts each individual symbol in the incoming list and outputs the result.
    class_addmethod(c, (method)convert_int,			"int",			A_LONG,		0);
    class_addmethod(c, (method)convert_float,			"float",		A_FLOAT,	0);
    class_addmethod(c, (method)convert_anything,		"list",			A_GIMME,	0);
    class_addmethod(c, (method)convert_anything,		"anything",		A_GIMME,	0);
    
    // @method getlist @digest Output list of encodings
    // @description Outputs all the allowed encodings from the right outlet.
    // Such encodings also have aliases, refer to
    // http://demo.icu-project.org/icu-bin/convexp for a full list.
    class_addmethod(c, (method)convert_anything,			"getlist",	A_GIMME,		0);
    

    // @method bang @digest Perform conversion
    // @description Performs the conversion on the most recently received input list.
    class_addmethod(c, (method)convert_bang,			"bang",			0);
    
    syobj_class_add_numin_attr(c);
    syobj_class_add_numout_attr(c);
    syobj_class_add_maxdecimals_attr(c);
    syobj_class_add_listout_attr(c);

    CLASS_ATTR_SYM(c, "from", 0, t_convert, from);
    CLASS_ATTR_STYLE_LABEL(c,"from",0,"text","Input Encoding");
    CLASS_ATTR_BASIC(c,"from",0);
    CLASS_ATTR_ACCESSORS(c, "from", (method)NULL, (method)convert_setattr_from);
    // @description Sets the input string format. Default is "Unicode". For other values, choose from the list at
    // http://demo.icu-project.org/icu-bin/convexp (case insensitive).
    
    CLASS_ATTR_SYM(c, "to", 0, t_convert, to);
    CLASS_ATTR_STYLE_LABEL(c,"to",0,"text","Output Encoding");
    CLASS_ATTR_BASIC(c,"to",0);
    CLASS_ATTR_ACCESSORS(c, "to", (method)NULL, (method)convert_setattr_to);
    // @description Sets the output string format. Default is "Unicode". For other values choose among the list at
    // http://demo.icu-project.org/icu-bin/convexp (case insensitive).
    

    CLASS_ATTR_SYM(c, "subsseq", 0, t_convert, subsseq);
    CLASS_ATTR_STYLE_LABEL(c,"subsseq",0,"text","Substitution Sequence");
    CLASS_ATTR_BASIC(c,"subsseq",0);
    CLASS_ATTR_ACCESSORS(c, "subsseq", (method)NULL, (method)convert_setattr_subseq);
    // @description Sets the replacement characters for when conversion fails. Leave blank for dropping such characters (default).
    
    
    class_register(CLASS_BOX, c); /* CLASS_NOBOX */
    convert_class = c;
    
    return 0;
}


void update_converters(t_convert *x)
{
    systhread_mutex_lock(x->n_ob.l_mutex);
    if (x->conv_from) {
        ucnv_close(x->conv_from);
        x->conv_from = NULL;
    }

    
    if (x->from && strcasecmp(x->from->s_name, "Unicode") != 0 && strcasecmp(x->from->s_name, "default") != 0) {
        UErrorCode err = U_ZERO_ERROR;
        x->conv_from = ucnv_open(x->from->s_name, &err);
        
        if (err != U_ZERO_ERROR) {
            object_error((t_object *)x, "Can't create converter for encoding \"%s\".", x->from->s_name);
            x->conv_from = NULL;
            goto to;
        }
        
        if (x->subsseq) {
            int32_t subsseq_length;
            UChar *subsseq_buffer = symbol_to_uchar_array(x->subsseq, &subsseq_length);
            ucnv_setSubstString(x->conv_from, subsseq_buffer, subsseq_length, &err);
            sysmem_freeptr(subsseq_buffer);
        } else {
            UChar zero = 0;
            ucnv_setSubstString(x->conv_from, &zero, 1, &err);
        }
        
        
        if (err != U_ZERO_ERROR) {
            object_warn((t_object *)x, "Can't set substitution sequence.");
            err = U_ZERO_ERROR;
        }
        
    }

to:
    if (x->conv_to) {
        ucnv_close(x->conv_to);
        x->conv_to = NULL;
    }
    
    
    if (x->to && strcasecmp(x->to->s_name, "Unicode") != 0 && strcasecmp(x->to->s_name, "default") != 0) {
        UErrorCode err = U_ZERO_ERROR;
        x->conv_to = ucnv_open(x->to->s_name, &err);
        
        if (err != U_ZERO_ERROR) {
            object_error((t_object *)x, "Can't create converter for encoding \"%s\".", x->to->s_name);
            x->conv_to = NULL;
            goto end;
        }
        
        if (x->subsseq) {
            int32_t subsseq_length;
            UChar *subsseq_buffer = symbol_to_uchar_array(x->subsseq, &subsseq_length);
            ucnv_setSubstString(x->conv_to, subsseq_buffer, subsseq_length, &err);
            sysmem_freeptr(subsseq_buffer);
        } else {
            UChar zero = 0;
            ucnv_setSubstString(x->conv_to, &zero, 1, &err);
        }
        
        
        if (err != U_ZERO_ERROR) {
            object_warn((t_object *)x, "Can't set substitution sequence.");
            err = U_ZERO_ERROR;
        }
        
    }
    
    
end:
    systhread_mutex_unlock(x->n_ob.l_mutex);
}


t_max_err convert_setattr_from(t_convert *x, t_object *attr, long ac, t_atom *av)
{
    if (ac && av && atom_gettype(av) == A_SYM) {
        x->from = atom_getsym(av);
        update_converters(x);
    }
    return MAX_ERR_NONE;
}

t_max_err convert_setattr_to(t_convert *x, t_object *attr, long ac, t_atom *av)
{
    if (ac && av && atom_gettype(av) == A_SYM) {
        x->to = atom_getsym(av);
        update_converters(x);
    }
    return MAX_ERR_NONE;
}


t_max_err convert_setattr_subseq(t_convert *x, t_object *attr, long ac, t_atom *av)
{
    if (ac && av && atom_gettype(av) == A_SYM) {
        x->subsseq = atom_getsym(av);
        update_converters(x);
    }
        return MAX_ERR_NONE;
}


void convert_assist(t_convert *x, void *b, long m, long a, char *s)
{
    if (m == ASSIST_INLET) { // @in 0 @type symbol/list @digest Incoming symbol or list
        sprintf(s, "Incoming symbol");
    }
    else {	// @out 0 @type symbol/list @digest Converted symbols
        sprintf(s, "Converted symbols");
    }
}

void convert_free(t_convert *x)
{
    if (x->conv_to)
        ucnv_close(x->conv_to);
    if (x->conv_from)
        ucnv_close(x->conv_from);
    syobj_obj_free((t_sy_object *)x);
}


void *convert_new(t_symbol *s, long argc, t_atom *argv)
{
    t_convert *x = NULL;
    long true_ac = attr_args_offset(argc, argv);
    
    if ((x = (t_convert *)object_alloc(convert_class))) {
        
        // @arg 0 @name from @optional 1 @type symbol @digest Input encoding
        // @description Sets the input string format. Choose among the list at
        // http://demo.icu-project.org/icu-bin/convexp (case insensitive).

        // @arg 1 @name to @optional 0 @type symbol @digest Output encoding
        // @description Sets the output string format. Choose among the list at
        // http://demo.icu-project.org/icu-bin/convexp (case insensitive).
        // If a single argument is given, this is interpreted as the output encoding.

        x->from = gensym("Unicode");
        x->to = gensym("Unicode");
        x->subsseq = _sym_nothing;
        x->conv_from = x->conv_to = NULL;
        
        if (true_ac >= 2 && atom_gettype(argv) == A_SYM && atom_gettype(argv + 1) == A_SYM) {
            x->from = atom_getsym(argv);
            x->to = atom_getsym(argv+1);
        } else if (true_ac && atom_gettype(argv) == A_SYM) {
            x->to = atom_getsym(argv);
        }
        
        syobj_obj_setup((t_sy_object *)x, 1);
        
        attr_args_process(x, argc, argv);
        
        update_converters(x);
        
        x->n_outlet2 = syout((t_object *)x);
        x->n_outlet1 = syout((t_object *)x);
    }
    return (x);
}

void convert_int(t_convert *x, t_atom_long num)
{
    t_atom argv[1];
    atom_setlong(argv, num);
    convert_anything(x, _sym_list, 1, argv);
}

void convert_float(t_convert *x, double num)
{
    t_atom argv[1];
    atom_setfloat(argv, num);
    convert_anything(x, _sym_list, 1, argv);
}

void convert_bang(t_convert *x)
{
    convert_anything(x, _sym_bang, 0, NULL);
}

void convert_anything(t_convert *x, t_symbol *msg, long ac, t_atom *av)
{
    long	stored_ac, out_ac = 0;
    t_atom	*stored_av = NULL;
    t_atom	*out_av = NULL;
    long dir;
    
    if (msg == gensym("getlist")) {
        t_atom av;
        long i, cnvCount = ucnv_countAvailable();
//        printf("Got %i converters\n", cnvCount);
        for (i = 0; i < cnvCount; ++i) {
            atom_setsym(&av, gensym(ucnv_getAvailableName(i)));
            sy_outlet(x->n_outlet2, NULL, 1, &av);
        }
    } else if (msg != _sym_bang)
        syobj_store_content((t_sy_object *) x, msg, ac, av, 0);
    
    stored_ac = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_MODE, &stored_av);
    
    systhread_mutex_lock(x->n_ob.l_mutex);
    if (x->conv_from && x->conv_to) {
        t_atom *out_av_temp = NULL;
        long out_ac_temp;
        dir = -1;
        out_ac_temp = iterate_on_gimme((t_sy_object *) x, NULL, stored_ac, stored_av, &out_av_temp, (atom_modif_fn)convert_fn, x->conv_from, &dir, NULL);
        dir = 1;
        out_ac = iterate_on_gimme((t_sy_object *) x, NULL, stored_ac, stored_av, &out_av, (atom_modif_fn)convert_fn, x->conv_to, &dir, NULL);
        sysmem_freeptr(out_av_temp);
    } else if (x->conv_from) {
        dir = -1;
        out_ac = iterate_on_gimme((t_sy_object *) x, NULL, stored_ac, stored_av, &out_av, (atom_modif_fn)convert_fn, x->conv_from, &dir, NULL);
    } else if (x->conv_to) {
        dir = 1;
        out_ac = iterate_on_gimme((t_sy_object *) x, NULL, stored_ac, stored_av, &out_av, (atom_modif_fn)convert_fn, x->conv_to, &dir, NULL);
    }
    systhread_mutex_unlock(x->n_ob.l_mutex);
    
    syobj_atom_array_reparse_account_for_numout((t_sy_object *)x, out_ac, out_av);
    syobj_atom_array_reparse_account_for_listout((t_sy_object *)x, &out_ac, &out_av);

    if (out_ac > 0)
        sy_outlet(x->n_outlet1, NULL, out_ac, out_av);
    
    sysmem_freeptr(stored_av);
    sysmem_freeptr(out_av);
}
