/**
	@file
	sy.normalize.c
	
	@name 
	sy.normalize
	
	@realname 
	sy.normalize

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	Normalize Unicode sequences
	
	@description
	Performs canonical or compatibility composition or decomposition of Unicode sequences.
	
	@discussion
	
	@category
	sy

	@keywords
	normalize, decompose, compose, normalization, form, decomposition, composition, diacritic, equivalent
	
	@seealso
	sy.convert, sy.filter
	
	@owner
	Daniele Ghisi
*/


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h


////////////////////////// object struct
typedef struct _normalize 
{
	t_sy_object		n_ob;		// the object itself (must be first)

	char			mode;		// the operation mode

	void			*n_outlet;
} t_normalize;



///////////////////////// function prototypes
//// standard set
void *normalize_new(t_symbol *s, long argc, t_atom *argv);
void normalize_free(t_normalize *x);
void normalize_assist(t_normalize *x, void *b, long m, long a, char *s);

void normalize_int(t_normalize *x, t_atom_long num);
void normalize_float(t_normalize *x, double num);
void normalize_anything(t_normalize *x, t_symbol *msg, long ac, t_atom *av);
void normalize_bang(t_normalize *x);
	

t_max_err normalize_setattr_mode(t_normalize *x, t_object *attr, long ac, t_atom *av);

	
//////////////////////// global class pointer variable
void *normalize_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();

	c = class_new("sy.normalize", (method)normalize_new, (method)normalize_free, (long)sizeof(t_normalize), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)normalize_assist,			"assist",		A_CANT, 0);  

	// @method anything @digest Normalize symbols
	// @description Normalizes each individual symbol in the incoming list and outputs the result.
	class_addmethod(c, (method)normalize_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)normalize_float,			"float",		A_FLOAT,	0);
	class_addmethod(c, (method)normalize_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)normalize_anything,		"anything",		A_GIMME,	0);

	// @method bang @digest Perform normalization
	// @description Performs the normalization on the most recently received input list.
	class_addmethod(c, (method)normalize_bang,			"bang",			0);

	syobj_class_add_numin_attr(c);
	syobj_class_add_numout_attr(c);
	syobj_class_add_maxdecimals_attr(c);
    syobj_class_add_listout_attr(c);

	CLASS_ATTR_CHAR(c, "mode", 0, t_normalize, mode); 
	CLASS_ATTR_STYLE_LABEL(c,"mode",0,"enumindex","Mode");
	CLASS_ATTR_ENUMINDEX(c,"mode", 0, "None NFD NFKD NFC NFKC FCD"); 
	CLASS_ATTR_BASIC(c,"mode",0);
	CLASS_ATTR_ACCESSORS(c, "mode", (method)NULL, (method)normalize_setattr_mode);
	// @description Sets the mode for the normalization: <br />
	// - None: no decomposition/composition <br />
	// - NFD: canonical decomposition <br />
	// - NFKD: compatibility decomposition <br />
	// - NFC (default): canonical decomposition followed by canonical composition <br />
	// - NFKC: compatibility decomposition followed by canonical composition <br />
	// - FCD: "fast C or D" form <br />
	
	
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	normalize_class = c;

	return 0;
}

t_max_err normalize_setattr_mode(t_normalize *x, t_object *attr, long ac, t_atom *av){
	if (ac && av) {
		x->mode = CLAMP(atom_getlong(av), 0, 5);
//		object_attr_setdisabled((t_object *)x, gensym("nonseparationchars"), x->mode != SY_CASE_MODE_TITLE);
	}
	return MAX_ERR_NONE;
}


void normalize_assist(t_normalize *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type symbol/list @digest Incoming symbol or list
		sprintf(s, "Incoming symbol");
	} 
	else {	// @out 0 @type symbol/list @digest Converted symbols
		sprintf(s, "Converted symbols"); 			
	}
}

void normalize_free(t_normalize *x)
{
	syobj_obj_free((t_sy_object *)x);
}


void *normalize_new(t_symbol *s, long argc, t_atom *argv)
{
	t_normalize *x = NULL;
	long true_ac = attr_args_offset(argc, argv);
    
	if ((x = (t_normalize *)object_alloc(normalize_class))) {
		
		// @arg 0 @name mode @optional 1 @type atom @digest Mode
		// @description The optional argument sets the value for the "mode" attribute.
		// This can be either the integer value of the attribute, or one of the following
		// symbols: "NFD", "NFKD", "NFC", "NFKC", "FCD".

		x->mode = 3;
		
		if (true_ac && atom_gettype(argv) == A_SYM) {
			t_symbol *sym = atom_getsym(argv);
			if (sym == gensym("NFD"))
				x->mode = 1;
			else if (sym == gensym("NFKD"))
				x->mode = 2;
			else if (sym == gensym("NFC"))
				x->mode = 3;
			else if (sym == gensym("NFKC"))
				x->mode = 4;
			else if (sym == gensym("FCD"))
				x->mode = 5;
		} else if (true_ac && atom_gettype(argv) == A_LONG) {
			x->mode = CLAMP(atom_getlong(argv), 0, 5);
		}

        syobj_obj_setup((t_sy_object *)x, 1);

        attr_args_process(x, argc, argv);
		
		x->n_outlet = syout((t_object *)x);
	}
	return (x);
}

void normalize_int(t_normalize *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	normalize_anything(x, _sym_list, 1, argv);
}

void normalize_float(t_normalize *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	normalize_anything(x, _sym_list, 1, argv);
}

void normalize_bang(t_normalize *x)
{	
	normalize_anything(x, _sym_bang, 0, NULL);
}

void normalize_anything(t_normalize *x, t_symbol *msg, long ac, t_atom *av)
{
	long	stored_ac, out_ac;
	t_atom	*stored_av = NULL;
	t_atom	*out_av = NULL;
	long	mode = x->mode;
	
	if (msg != _sym_bang) 
		syobj_store_content((t_sy_object *) x, msg, ac, av, 0);
	
	stored_ac = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_MODE, &stored_av);
	
	out_ac = iterate_on_gimme((t_sy_object *) x, NULL, stored_ac, stored_av, &out_av, (atom_modif_fn)normalize_fn, &mode, NULL, NULL);

	syobj_atom_array_reparse_account_for_numout((t_sy_object *)x, out_ac, out_av);
    syobj_atom_array_reparse_account_for_listout((t_sy_object *)x, &out_ac, &out_av);

	if (out_ac > 0)
		sy_outlet(x->n_outlet, NULL, out_ac, out_av);
	
	sysmem_freeptr(stored_av);
	sysmem_freeptr(out_av);
}
