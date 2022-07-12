/**
	@file
	sy.pad.c
	
	@name 
	sy.pad
	
	@realname 
	sy.pad

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	Pad symbols
	
	@description
	Appends or prepends characters to input symbols to match a given length.
	
	@discussion
    Length is defined as the number of codepoints in the Unicode string.
	
	@category
	sy

	@keywords
	pad, join
	
	@seealso
	sy.append, combine
	
	@owner
	Daniele Ghisi
*/


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h


////////////////////////// object struct
typedef struct _pad 
{
	t_sy_object		n_ob;		// the object itself (must be first)

    long                n_output_size; // output size
    t_symbol            *n_padsym; // padding reservoir
    
    
    char				n_mode;         // one of the #e_pad_mode
    long                n_loopsize;     // loop size (for loop mode only)
    char				n_trim;         // allow trimming
    char				n_align;        // alignment
    char                n_rounding;     // rounding direction (for non-evenly distributed center-alignment)

    
    
	long			n_in;   // space for the inlet number used by all the proxies
    void			*n_proxy1;
    void			*n_proxy2;

    void			*n_outlet;
} t_pad;



///////////////////////// function prototypes
//// standard set
void *pad_new(t_symbol *s, long argc, t_atom *argv);
void pad_free(t_pad *x);
void pad_assist(t_pad *x, void *b, long m, long a, char *s);

void pad_int(t_pad *x, t_atom_long num);
void pad_float(t_pad *x, double num);
void pad_anything(t_pad *x, t_symbol *msg, long ac, t_atom *av);
void pad_bang(t_pad *x);
	

t_max_err pad_setattr_mode(t_pad *x, t_object *attr, long ac, t_atom *av);

	
//////////////////////// global class pointer variable
void *pad_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();

	c = class_new("sy.pad", (method)pad_new, (method)pad_free, (long)sizeof(t_pad), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)pad_assist,			"assist",		A_CANT, 0);  

    // @method anything @digest Function depends on inlet
    // @description
    // In first inlet: the incoming symbol or list is padded or trimmed (accorded to the attribute values), and the result is output from the outlet.<br />
    // In third inlet: sets the padding character (or elements, for "Loop" <m>mode</m>).
    // This can be a one-character-symbol, such as <b>x</b> or <b>" "</b>, or - in "Loop" <m>mode</m> - any complex symbol,
    // interpreted as a reservoir from which the padding elements should be picked.
    // Setting the empty symbol forces <o>bach.pad</o> to repeat the elements of the incoming one (default)
	class_addmethod(c, (method)pad_float,			"float",		A_FLOAT,	0);
	class_addmethod(c, (method)pad_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)pad_anything,		"anything",		A_GIMME,	0);

    // @method int @digest Sets output length
    // @description A non-negative integer in the second inlet sets the desired output length for padding or trimming.
    class_addmethod(c, (method)pad_int,			"int",			A_LONG,		0);


	// @method bang @digest Perform padding
	// @description Performs the operation of the most recently received input data.
	class_addmethod(c, (method)pad_bang,			"bang",			0);

	syobj_class_add_numin_attr(c);
	syobj_class_add_numout_attr(c);
	syobj_class_add_maxdecimals_attr(c);
    syobj_class_add_listin_attr(c);
    syobj_class_add_listout_attr(c);

    
    CLASS_ATTR_CHAR(c, "mode", 0, t_pad, n_mode);
    CLASS_ATTR_STYLE_LABEL(c,"mode",0,"text","Padding Mode");
    CLASS_ATTR_ENUMINDEX(c, "mode", 0, "Repeat Loop Palindrome Loop Palindrome Loop No Repetitions");
    CLASS_ATTR_BASIC(c,"mode",0);
    // @description Sets the padding mode: <br />
    // - <b>Repeat</b> (default) just copies a single element (the first or last element, depending on the <m>align</m> attribute) over and over,
    // until the desired length has been reached (e.g.: ABCDDDDDD...); <br />
    // - <b>Loop</b> copies the whole llll (or a portion of it, depending on the <m>loopsize</m> attribute) over and over, until the desired length
    // has been reached. Last copy can of course be trimmed, if it overflows the desired length (e.g.: ABCDABCDABCDABCD...); <br />
    // - <b>Palindrome Loop</b> is like the previous one, but reverses the loop direction at each new loop (e.g.: ABCDDCBAABCDDCBA...); <br />
    // - <b>Palindrome Loop No Repetitions</b> is like the previous one, but avoids repetitions at the loop beginning or end (e.g.: ABCDCBABCDCBA...).
    
    CLASS_ATTR_LONG(c, "loopsize", 0, t_pad, n_loopsize);
    CLASS_ATTR_STYLE_LABEL(c,"loopsize",0,"text","Number of Elements to Repeat");
    // @description Sets the number of elements to be repeated in "Loop" <m>mode</m> (has no effect in "Repeat" <m>mode</m>)
    
    
    CLASS_ATTR_CHAR(c, "trim", 0, t_pad, n_trim);
    CLASS_ATTR_STYLE_LABEL(c,"trim",0,"onoff","Trim If Needed");
    CLASS_ATTR_BASIC(c,"trim",0);
    // @description If the <m>trim</m> attribute is set to 1 (default),
    // when the output length is less than the length of the original llll, this latter
    // is trimmed at output; otherwise it is output as it is.
    
    CLASS_ATTR_CHAR(c, "align", 0, t_pad, n_align);
    CLASS_ATTR_STYLE_LABEL(c,"align",0,"enumindex","Alignment");
    CLASS_ATTR_ENUMINDEX(c, "align", 0, "Left Center Right");
    CLASS_ATTR_BASIC(c,"align",0);
    // @description Sets the alignment of the original llll within the padded llll. <br />
    // - If alignment is 0 = <b>Left</b> (default), the padding will be done at right. <br />
    // - If alignment is 1 = <b>Center</b> the padding will be equally done at left and at right
    // (rounding to the right). <br />
    // - If alignment is 2 = <b>Right</b>, the padding will be done at left.
    
    CLASS_ATTR_CHAR(c, "roundalign", 0, t_pad, n_rounding);
    CLASS_ATTR_STYLE_LABEL(c,"roundalign",0,"enumindex","Rounding Alignment Direction");
    CLASS_ATTR_ENUMINDEX(c, "roundalign", 0, "Left Right");
    // @description Sets the rounding direction for the specific situation where the <m>align</m> attribute is set to "Center" and
    // an odd number of elements should be split into right and left padding. <br />
    // - If <m>roundalign</m> is 0 = <b>Left</b> (default), one more element is given at the right padding side; <br />
    // - If <m>roundalign</m> is 1 = <b>Right</b>, one more element is given at the left padding side. <br />
    

	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	pad_class = c;

	return 0;
}


void pad_assist(t_pad *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
        if (a == 0) sprintf(s, "Incoming symbol or list"); // @in 0 @type anything @digest Incoming symbol or list
        else if (a == 1) sprintf(s, "int: Output Length"); // @in 1 @type int @digest The output length
        else sprintf(s, "anything: Padding Characters"); // @in 2 @type anything @digest The padding characters
	}
	else {	// @out 0 @type anything @digest Symbols with padded characters
		sprintf(s, "Symbol or list with padded characters");
	}
}

void pad_free(t_pad *x)
{
    object_free(x->n_proxy1);
    object_free(x->n_proxy2);
	syobj_obj_free((t_sy_object *)x);
}


void *pad_new(t_symbol *s, long argc, t_atom *argv)
{
	t_pad *x = NULL;
	long true_ac = attr_args_offset(argc, argv);
    
	if ((x = (t_pad *)object_alloc(pad_class))) {
		
		syobj_obj_setup((t_sy_object *)x, 3);
        
        x->n_padsym = _sym_nothing;
        x->n_output_size = 0;
        
        // @arg 0 @name output_length @optional 0 @type int @digest Output length
        // @description The first integer argument sets the output length, i.e. the target length that
        // the output symbols must have.
        if (true_ac && atom_gettype(argv) == A_LONG) {
            x->n_output_size = atom_getlong(argv);
            
            if (true_ac > 1) {
                // @arg 1 @name padding_characters @optional 1 @type symbol @digest Padding character or characters
                // @description The second argument sets the character used for padding (or characters, in "Loop" <m>mode</m>).
                // This can be a symbol containing a single character, such as <b>"0"</b> or <b>_</b>,
                // or - in "Loop" <m>mode</m> - any symbol containing more than one character, from which the padding elements should be picked.
                // Setting this argument as the empty symbol <b>""</b> (also see <o>sy.empty</o>),
                // forces <o>sy.pad</o> to repeat the
                // elements of the incoming list (default).
                x->n_padsym = symbol_from_gimme(true_ac - 1, argv + 1);
            }
        }

        attr_args_process(x, argc, argv);
		
        x->n_proxy2 = proxy_new((t_object *) x, 2, &x->n_in);
		x->n_proxy1 = proxy_new((t_object *) x, 1, &x->n_in);
		x->n_outlet = syout((t_object *)x);
	}
	return (x);
}

void pad_int(t_pad *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	pad_anything(x, _sym_list, 1, argv);
}

void pad_float(t_pad *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	pad_anything(x, _sym_list, 1, argv);
}

void pad_bang(t_pad *x)
{	
	pad_anything(x, _sym_bang, 0, NULL);
}

void pad_anything(t_pad *x, t_symbol *msg, long ac, t_atom *av)
{
	long	stored_ac1, stored_ac2, out_ac;
	t_atom	*stored_av1 = NULL, *stored_av2 = NULL, *out_av = NULL;
	long inlet = proxy_getinlet((t_object *) x);
	
    if (msg == _sym_clear && inlet == 2) {
        x->n_padsym = _sym_nothing;
        syobj_store_content((t_sy_object *) x, NULL, 0, NULL, 2);
    } else if (msg != _sym_bang)
		syobj_store_content((t_sy_object *) x, msg, ac, av, inlet);
	
    if (inlet == 2) {
        stored_ac2 = syobj_get_store_contents((t_sy_object *) x, 2, SY_STORE_CLONE_AS_SINGLE_SYMBOL, &stored_av2);
        x->n_padsym = symbol_from_gimme(stored_ac2, stored_av2);
        sysmem_freeptr(stored_av2);
    } else if (inlet == 0) {
        stored_ac1 = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_AND_LIST_MODE, &stored_av1);
		
        t_sy_pad_params params;
        params.rounding_direction = x->n_rounding;
        params.align = x->n_align;
        params.allow_trimming = x->n_trim;
        params.mode = x->n_mode;
        params.num_loop_elems = x->n_loopsize;
        params.output_length = x->n_output_size;
        params.reservoir = x->n_padsym;
        
        out_ac = iterate_on_gimme((t_sy_object *) x, NULL, stored_ac1, stored_av1, &out_av, (atom_modif_fn)pad_fn, &params, NULL, NULL);
		
		syobj_atom_array_reparse_account_for_numout((t_sy_object *)x, out_ac, out_av);
        syobj_atom_array_reparse_account_for_listout((t_sy_object *)x, &out_ac, &out_av);
		
		if (out_ac > 0)
			sy_outlet(x->n_outlet, NULL, out_ac, out_av);
		
		sysmem_freeptr(stored_av1);
		sysmem_freeptr(out_av);
	}
}
