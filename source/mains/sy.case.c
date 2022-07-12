/**
	@file
	sy.case.c
	
	@name 
	sy.case
	
	@realname 
	sy.case

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	Map case
	
	@description
	Converts the case of the incoming symbols, depending on the chosen mode.
	
	@discussion
	
	@category
	sy

	@keywords
	convert, change, case, lower, upper, switch, invert, symbol_capitalize, title, fold, unicode, capital
	
	@seealso
	
	
	@owner
	Daniele Ghisi
*/


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h


////////////////////////// object struct
typedef struct _case 
{
	t_sy_object		n_ob;		// the object itself (must be first)

	char			mode;		// the operation mode
	t_symbol		*non_separators_for_capitalization;		// String containing possible non-alphanumeric separators for capitalization (e.g.: ') 

	void			*n_outlet;
} t_case;



///////////////////////// function prototypes
//// standard set
void *case_new(t_symbol *s, long argc, t_atom *argv);
void case_free(t_case *x);
void case_assist(t_case *x, void *b, long m, long a, char *s);

void case_int(t_case *x, t_atom_long num);
void case_float(t_case *x, double num);
void case_anything(t_case *x, t_symbol *msg, long ac, t_atom *av);
void case_bang(t_case *x);
	

t_max_err case_setattr_mode(t_case *x, t_object *attr, long ac, t_atom *av);

	
//////////////////////// global class pointer variable
void *case_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();

	c = class_new("sy.case", (method)case_new, (method)case_free, (long)sizeof(t_case), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)case_assist,			"assist",		A_CANT, 0);  

	// @method anything @digest Change case
	// @description Changes the case of each individual symbol in the incoming list and outputs the result.
	class_addmethod(c, (method)case_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)case_float,			"float",		A_FLOAT,	0);
	class_addmethod(c, (method)case_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)case_anything,		"anything",		A_GIMME,	0);

	// @method bang @digest Change case
	// @description Changes the case of the most recently received input list.
	class_addmethod(c, (method)case_bang,			"bang",			0);

	syobj_class_add_numin_attr(c);
	syobj_class_add_numout_attr(c);
	syobj_class_add_maxdecimals_attr(c);
	syobj_class_add_locale_attr(c);
    syobj_class_add_listout_attr(c);

	CLASS_ATTR_CHAR(c, "mode", 0, t_case, mode); 
	CLASS_ATTR_STYLE_LABEL(c,"mode",0,"enumindex","Mode");
	CLASS_ATTR_ENUMINDEX(c,"mode", 0, "None Upper Lower Title Switch Fold"); 
	CLASS_ATTR_BASIC(c,"mode",0);
	CLASS_ATTR_ACCESSORS(c, "mode", (method)NULL, (method)case_setattr_mode);
	// @description Sets the mode for the case conversion: <br />
	// - None (default): don't convert case <br />
	// - Lower: convert to lower case <br />
	// - Upper: convert to upper case <br />
	// - Title: symbol_capitalize each word individually <br />
	// - Switch: switch the existing case, for each character <br />
	// - Fold: fold the case, for string comparison <br />
	
	
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	case_class = c;

	return 0;
}

t_max_err case_setattr_mode(t_case *x, t_object *attr, long ac, t_atom *av){
	if (ac && av) {
		x->mode = CLAMP(atom_getlong(av), 0, 5);
//		object_attr_setdisabled((t_object *)x, gensym("nonseparationchars"), x->mode != SY_CASE_MODE_TITLE);
	}
	return MAX_ERR_NONE;
}


void case_assist(t_case *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type symbol/list @digest Incoming symbol or list
		sprintf(s, "Incoming symbol");
	} 
	else {	// @out 0 @type symbol/list @digest Symbols with converted case
		sprintf(s, "Symbol with converted case"); 			
	}
}

void case_free(t_case *x)
{
	syobj_obj_free((t_sy_object *)x);
}


void *case_new(t_symbol *s, long argc, t_atom *argv)
{
	t_case *x = NULL;
	long true_ac = attr_args_offset(argc, argv);
    
	if ((x = (t_case *)object_alloc(case_class))) {
		
		// @arg 0 @name mode @optional 1 @type atom @digest Mode
		// @description The optional argument sets the value for the "mode" attribute.
		// This can be either the integer value of the attribute, or one of the following
		// symbols: "lower", "upper", "switch", "title", "fold".

		x->mode = SY_CASE_MODE_DONT;
		x->non_separators_for_capitalization = gensym("");
		
		if (true_ac && atom_gettype(argv) == A_SYM) {
			t_symbol *sym = atom_getsym(argv);
			if (sym == gensym("upper"))
				x->mode = SY_CASE_MODE_UPPER;
			else if (sym == gensym("lower"))
				x->mode = SY_CASE_MODE_LOWER;
			else if (sym == gensym("title") || sym == gensym("symbol_capitalize"))
				x->mode = SY_CASE_MODE_TITLE;
			else if (sym == gensym("switch"))
				x->mode = SY_CASE_MODE_SWITCH;
			else if (sym == gensym("fold"))
				x->mode = SY_CASE_MODE_FOLD;
		} else if (true_ac && atom_gettype(argv) == A_LONG) {
			x->mode = CLAMP(atom_getlong(argv), 0, 5);
		}

        syobj_obj_setup((t_sy_object *)x, 1);

        attr_args_process(x, argc, argv);
		
		x->n_outlet = syout((t_object *)x);
	}
	return (x);
}

void case_int(t_case *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	case_anything(x, _sym_list, 1, argv);
}

void case_float(t_case *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	case_anything(x, _sym_list, 1, argv);
}

void case_bang(t_case *x)
{	
	case_anything(x, _sym_bang, 0, NULL);
}

void case_anything(t_case *x, t_symbol *msg, long ac, t_atom *av)
{
	long	stored_ac, out_ac;
	t_atom	*stored_av = NULL;
	t_atom	*out_av = NULL;
	long	mode = x->mode;
	
	if (msg != _sym_bang) 
		syobj_store_content((t_sy_object *) x, msg, ac, av, 0);
	
	stored_ac = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_MODE, &stored_av);
	
	out_ac = iterate_on_gimme((t_sy_object *) x, NULL, stored_ac, stored_av, &out_av, (atom_modif_fn)change_case_fn, &mode, &x->n_ob.l_locale, &x->non_separators_for_capitalization);

	syobj_atom_array_reparse_account_for_numout((t_sy_object *)x, out_ac, out_av);
    syobj_atom_array_reparse_account_for_listout((t_sy_object *)x, &out_ac, &out_av);

	if (out_ac > 0)
		sy_outlet(x->n_outlet, NULL, out_ac, out_av);
	
	sysmem_freeptr(stored_av);
	sysmem_freeptr(out_av);
}
