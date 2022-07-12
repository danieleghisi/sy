/**
	@file
	sy.compare.c
	
	@name 
	sy.compare
	
	@realname 
	sy.compare

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	Compare symbols
	
	@description
	Compares of the incoming symbols (or list of symbols), and returns -1 if the 
	left one comes first, 1 if the right one comes first, 0 if they are equivalent.
	
	@discussion
	
	@category
	sy

	@keywords
	compare, alphabetical, ASCII, order, equal, different, before, after
	
	@seealso
	sy.sort
	
	@owner
	Daniele Ghisi
*/


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h

////////////////////////// object struct
typedef struct _compare 
{
	t_sy_object		n_ob;		// the object itself (must be first)

	char			casefirst;	// the priority of cases
	long			strength;	// strength of the comparison 
	char			digits;		// numeric collation: sequences of digits are compared by value (i.e. "100" is before "2")
	char			ignorepunctuation;	// if set, all the alternate characters and punctuations are moved from the first to the quaternary level, 
										// so that up to the tertiary level, for instance, "a-b" and "ab" are the same.

	long			n_in;   // space for the inlet number used by all the proxies
    void			*n_proxy1;
	void			*n_outlet;
} t_compare;



///////////////////////// function prototypes
//// standard set
void *compare_new(t_symbol *s, long argc, t_atom *argv);
void compare_free(t_compare *x);
void compare_assist(t_compare *x, void *b, long m, long a, char *s);
void compare_inletinfo(t_compare *x, void *b, long a, char *t);

void compare_int(t_compare *x, t_atom_long num);
void compare_float(t_compare *x, double num);
void compare_anything(t_compare *x, t_symbol *msg, long ac, t_atom *av);
void compare_bang(t_compare *x);
	

	
//////////////////////// global class pointer variable
void *compare_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();

	c = class_new("sy.compare", (method)compare_new, (method)compare_free, (long)sizeof(t_compare), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)compare_assist,			"assist",		A_CANT, 0);  
	class_addmethod(c, (method)compare_inletinfo,	"inletinfo",	A_CANT,		0);

	// @method anything @digest Function depends on inlet
	// @description Compare the symbols in the left inlet with the ones in the right inlet; when symbols
    // are received in the  left inlet it also outputs the result of the comparison (-1 if the left symbol
    // comes first, 0 if they are equivalent, 1 if the right symbol comes first).
	class_addmethod(c, (method)compare_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)compare_float,			"float",		A_FLOAT,	0);
	class_addmethod(c, (method)compare_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)compare_anything,		"anything",		A_GIMME,	0);

	// @method bang @digest Perform comparison
	// @description Performs the comparison the most recently received input list.
	class_addmethod(c, (method)compare_bang,			"bang",			0);

	syobj_class_add_numin_attr(c);
	syobj_class_add_maxdecimals_attr(c);
	syobj_class_add_locale_attr(c);
	
	CLASS_ATTR_CHAR(c, "case", 0, t_compare, casefirst); 
	CLASS_ATTR_STYLE_LABEL(c,"case",0,"enumindex","Case Priority");
	CLASS_ATTR_ENUMINDEX(c,"case", 0, "None Upper First Lower First"); 
	// @description Controls the ordering of upper and lower case letters: <br />
	// - None (default): upper and lower case letters are findd in accordance to their tertiary weights (see <m>strength</m>); <br />
	// - Upper First: forces upper case letters to sort before lower case letters; <br />
	// - Lower First: forces lower case letters to sort before upper case letters. <br />
	

	CLASS_ATTR_LONG(c, "strength", 0, t_compare, strength); 
	CLASS_ATTR_STYLE_LABEL(c,"strength",0,"enumindex","Comparison Strength");
	CLASS_ATTR_ENUMINDEX(c,"strength", 0, "Zero (nothing) Primary (characters) Secondary (accents) Tertiary (case) Quaternary (punctuation) Identical"); 
	CLASS_ATTR_BASIC(c,"strength",0);
	// @description Sets the strength for the comparison.
	// @copy SY_DOC_COMPARISON_STRENGTH

	
	CLASS_ATTR_CHAR(c, "digits", 0, t_compare, digits); 
	CLASS_ATTR_STYLE_LABEL(c,"digits",0,"onoff","Digit Sequences Compared By Values");
	CLASS_ATTR_BASIC(c,"digits",0);
	// @description Toggles the ability to compare sequences of digits by values, e.g. "100" will thus be before "2". Defaults to 1.
	

	CLASS_ATTR_CHAR(c, "alternate", 0, t_compare, ignorepunctuation); 
	CLASS_ATTR_STYLE_LABEL(c,"alternate",0,"onoff","Ignore Alternate Characters");
	// @description Toggles the ability to move the differences of punctuation and alternate characters from the first to the fourth strength 
	// level (see <m>strength</m> attribute). When this attribute is active, for instance, it means that up to the tertiary level symbols like
	// "ab" and "a-b" are equal. Defaults to 0.
	
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	compare_class = c;

	return 0;
}

void compare_assist(t_compare *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { 
		if (a == 0) // @in 0 @type symbol/list @digest Left symbol or list
			sprintf(s, "Left symbol for comparison");
		else // @in 1 @type symbol/list @digest Right symbol or list
			sprintf(s, "Right symbol for comparison");
	} else {
		// @out 0 @type int @digest Comparison result 
		// @description 1 if left symbol precedes right one, -1 if right symbol precedes left one, 0 if symbols are equivalent.
		sprintf(s, "1 if left symbol precedes right one, -1 if right symbol precedes left one, 0 if symbols are equivalent"); 			
	}	
		
}

void compare_inletinfo(t_compare *x, void *b, long a, char *t)
{
	if (a)
		*t = 1;
}

void compare_free(t_compare *x)
{
	object_free(x->n_proxy1);
	syobj_obj_free((t_sy_object *)x);
}

void *compare_new(t_symbol *s, long argc, t_atom *argv)
{
	t_compare *x = NULL;
    
	if ((x = (t_compare *)object_alloc(compare_class))) {

		x->strength = 3;  // tertiary
		x->digits = 1;    // on
		x->casefirst = 0; // none
		x->ignorepunctuation = 0; // don't ignore punctuation

        syobj_obj_setup((t_sy_object *)x, 2);

        attr_args_process(x, argc, argv);
		
		x->n_proxy1 = proxy_new((t_object *) x, 1, &x->n_in);
		x->n_outlet = intout(x);
	}
	return (x);
}

void compare_int(t_compare *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	compare_anything(x, _sym_list, 1, argv);
}

void compare_float(t_compare *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	compare_anything(x, _sym_list, 1, argv);
}

void compare_bang(t_compare *x)
{	
	compare_anything(x, _sym_bang, 0, NULL);
}

void compare_anything(t_compare *x, t_symbol *msg, long ac, t_atom *av)
{
	long	stored_ac1, stored_ac2;
	t_atom	*stored_av1 = NULL, *stored_av2 = NULL;
	long inlet = proxy_getinlet((t_object *) x);
	long strength = x->strength;
	
	if (msg != _sym_bang) 
		syobj_store_content((t_sy_object *) x, msg, ac, av, inlet);
	
	if (inlet == 0) {
		stored_ac1 = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_MODE, &stored_av1);
		stored_ac2 = syobj_get_store_contents((t_sy_object *) x, 1, SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_MODE, &stored_av2);
		
		
		UErrorCode status = U_ZERO_ERROR; 
		UCollator *coll = ucol_open(x->n_ob.l_locale ? x->n_ob.l_locale->s_name : "", &status); 
		if (U_SUCCESS(status)) {
			long i;
			char res = UCOL_EQUAL;
			t_atom *av1 = stored_av1, *av2 = stored_av2;

			ucol_setAttribute(coll, UCOL_STRENGTH, strength_attribute_to_ICU_flag((t_sy_object *)x, strength), &status);
			if (U_FAILURE(status)) goto error;

			ucol_setAttribute(coll, UCOL_NUMERIC_COLLATION, x->digits ? UCOL_ON : UCOL_OFF, &status);
			if (U_FAILURE(status)) goto error;

			ucol_setAttribute(coll,	UCOL_CASE_FIRST, x->casefirst == 1 ? UCOL_UPPER_FIRST : (x->casefirst == 2 ? UCOL_LOWER_FIRST : UCOL_OFF), &status);
			if (U_FAILURE(status)) goto error;

			ucol_setAttribute(coll,	UCOL_ALTERNATE_HANDLING, x->ignorepunctuation == 1 ? UCOL_SHIFTED : UCOL_NON_IGNORABLE, &status);
			if (U_FAILURE(status)) goto error;

			for (i = 0; i < stored_ac1 && i < stored_ac2; i++, av1++, av2++) {
				if ((res = atoms_compare(coll, av1, av2)) != UCOL_EQUAL)
					break;
			}
			
			if (res == UCOL_EQUAL) {
				// if all the common words are equal, the longest sequence of symbols wins
				if (stored_ac1 < stored_ac2)
					res = UCOL_LESS;
				else if (stored_ac1 > stored_ac2)
					res = UCOL_GREATER;
			}
			
			ucol_close(coll); 
			outlet_int(x->n_outlet, res);
		}	
		
	error:
		if (U_FAILURE(status))
			dev_post("Error in string comparison.");
		sysmem_freeptr(stored_av1);
		sysmem_freeptr(stored_av2);
	}
}
