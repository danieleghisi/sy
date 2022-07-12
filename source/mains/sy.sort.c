/**
	@file
	sy.sort.c
	
	@name 
	sy.sort
	
	@realname 
	sy.sort

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	Sort symbols alphabetically
	
	@description
	Sorts the incoming list of symbols alphabetically.
	
	@discussion
	
	@category
	sy

	@keywords
	sort, alphabetical, ASCII, order, equal, different, before, after
	
	@seealso
	sy.compare
	
	@owner
	Daniele Ghisi
*/


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h

////////////////////////// object struct
typedef struct _sort 
{
	t_sy_object		n_ob;		// the object itself (must be first)

	char			casefirst;	// the priority of cases
	long			strength;	// strength of the comparison 
	char			digits;		// numeric collation: sequences of digits are sortd by value (i.e. "100" is before "2")
	char			ignorepunctuation;	// if set, all the alternate characters and punctuations are moved from the first to the quaternary level, 
										// so that up to the tertiary level, for instance, "a-b" and "ab" are the same.
	char			reverse;
	
	void			*n_outlet1;
	void			*n_outlet2;
} t_sort;



///////////////////////// function prototypes
//// standard set
void *sort_new(t_symbol *s, long argc, t_atom *argv);
void sort_free(t_sort *x);
void sort_assist(t_sort *x, void *b, long m, long a, char *s);
void sort_inletinfo(t_sort *x, void *b, long a, char *t);

void sort_int(t_sort *x, t_atom_long num);
void sort_float(t_sort *x, double num);
void sort_anything(t_sort *x, t_symbol *msg, long ac, t_atom *av);
void sort_bang(t_sort *x);
	

	
//////////////////////// global class pointer variable
void *sort_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();

	c = class_new("sy.sort", (method)sort_new, (method)sort_free, (long)sizeof(t_sort), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)sort_assist,			"assist",		A_CANT, 0);  
	class_addmethod(c, (method)sort_inletinfo,	"inletinfo",	A_CANT,		0);

	// @method anything @digest Sort symbols
	// @description Sorts all symbols in the incoming list alphabetically and outputs the result.
	class_addmethod(c, (method)sort_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)sort_float,			"float",		A_FLOAT,	0);
	class_addmethod(c, (method)sort_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)sort_anything,		"anything",		A_GIMME,	0);

	// @method bang @digest Sort symbols
	// @description Performs the sorting on the most recently received input list.
	class_addmethod(c, (method)sort_bang,			"bang",			0);

	syobj_class_add_numin_attr(c);
	syobj_class_add_maxdecimals_attr(c);
	syobj_class_add_locale_attr(c);
	
	CLASS_ATTR_CHAR(c, "case", 0, t_sort, casefirst); 
	CLASS_ATTR_STYLE_LABEL(c,"case",0,"enumindex","Case Priority");
	CLASS_ATTR_ENUMINDEX(c,"case", 0, "Default Upper First Lower First"); 
	// @description Controls the ordering of upper and lower case letters: <br />
	// - Default: upper and lower case letters are findd in accordance to their tertiary weights (see <m>strength</m>); <br />
	// - Upper First: forces upper case letters to sort before lower case letters; <br />
	// - Lower First: forces lower case letters to sort before upper case letters. <br />
	

	CLASS_ATTR_LONG(c, "strength", 0, t_sort, strength); 
	CLASS_ATTR_STYLE_LABEL(c,"strength",0,"enumindex","Comparison Strength");
	CLASS_ATTR_ENUMINDEX(c,"strength", 0, "Zero (nothing) Primary (characters) Secondary (accents) Tertiary (case) Quaternary (punctuation) Identical"); 
	CLASS_ATTR_BASIC(c,"strength",0);
	// @description Sets the strength for the sorting comparisons.
	// @copy SY_DOC_COMPARISON_STRENGTH

	
	CLASS_ATTR_CHAR(c, "digits", 0, t_sort, digits); 
	CLASS_ATTR_STYLE_LABEL(c,"digits",0,"onoff","Digit Sequences Compared By Values");
	CLASS_ATTR_BASIC(c,"digits",0);
	// @description Toggles the ability to sort sequences of digits by values, e.g. "100" will thus be before "2". Defaults to 1.

	
	CLASS_ATTR_CHAR(c, "reverse", 0, t_sort, reverse); 
	CLASS_ATTR_STYLE_LABEL(c,"reverse",0,"onoff","Reverse Sorting");
	CLASS_ATTR_BASIC(c,"reverse",0);
	// @description Toggles the ability to reverse the sorting (e.g. alphabetical ordering will span from Z to A, instead and not from A to Z).
	

	CLASS_ATTR_CHAR(c, "alternate", 0, t_sort, ignorepunctuation); 
	CLASS_ATTR_STYLE_LABEL(c,"alternate",0,"onoff","Ignore Alternate Characters");
	// @description Toggles the ability to move the differences of punctuation and alternate characters from the first to the fourth strength 
	// level (see <m>strength</m> attribute). When this attribute is active, for instance, it means that up to the tertiary level symbols like
	// "ab" and "a-b" are equal. Defaults to 0.
	
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	sort_class = c;

	return 0;
}

void sort_assist(t_sort *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { 
		// @in 0 @type list @digest Symbols to be sorted
		sprintf(s, "List: Symbols to Be Sorted");
	} else {
		if (a == 0) // @out 0 @type list @digest Sorted symbols 
			sprintf(s, "list: Sorted Symbols"); 			
		else  // @out 1 @type list @digest Sorted indices 
			sprintf(s, "list: Sorted Symbols"); 			
	}	
		
}

void sort_inletinfo(t_sort *x, void *b, long a, char *t)
{
	if (a)
		*t = 1;
}

void sort_free(t_sort *x)
{
	syobj_obj_free((t_sy_object *)x);
}

void *sort_new(t_symbol *s, long argc, t_atom *argv)
{
	t_sort *x = NULL;
    
	if ((x = (t_sort *)object_alloc(sort_class))) {

		x->strength = 3;  // tertiary
		x->digits = 1;    // on
		x->casefirst = 0; // none
		x->ignorepunctuation = 0; // don't ignore punctuation
		x->reverse = 0;
		
        syobj_obj_setup((t_sy_object *)x, 1);

        attr_args_process(x, argc, argv);
		
		x->n_outlet2 = syout((t_object *)x);
		x->n_outlet1 = syout((t_object *)x);
	}
	return (x);
}

void sort_int(t_sort *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	sort_anything(x, _sym_list, 1, argv);
}

void sort_float(t_sort *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	sort_anything(x, _sym_list, 1, argv);
}

void sort_bang(t_sort *x)
{	
	sort_anything(x, _sym_bang, 0, NULL);
}


static int cmpfunc (void *data, const void *a, const void *b)
{
	UCollator *coll = (UCollator *)(((void **)data)[0]);
	t_atom *stored_av = (t_atom *)(((void **)data)[1]);
	long index_a = atom_getlong((t_atom *)a) - 1;
	long index_b = atom_getlong((t_atom *)b) - 1;
	return atoms_compare((UCollator *)coll, stored_av + index_a, stored_av + index_b);
}

static int cmpfunc_rev (void *data, const void *a, const void *b)
{
	return -cmpfunc(data, a, b);
}


void sort_anything(t_sort *x, t_symbol *msg, long ac, t_atom *av)
{
	long	stored_ac;
	t_atom	*stored_av = NULL;
	long strength = x->strength;
	char reverse = x->reverse;
	
	if (msg != _sym_bang) 
		syobj_store_content((t_sy_object *) x, msg, ac, av, 0);
	
	stored_ac = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_MODE, &stored_av);
	
	t_atom *output_av = (t_atom *)sysmem_newptr(stored_ac * sizeof(t_atom));
	t_atom *indices_av = (t_atom *)sysmem_newptr(stored_ac * sizeof(t_atom));
	long i = 0;
	for (i = 0; i < stored_ac; i++)
		atom_setlong(indices_av + i, i + 1);
	
	
	UErrorCode status = U_ZERO_ERROR; 
	UCollator *coll = ucol_open(x->n_ob.l_locale->s_name, &status); 
	if (U_SUCCESS(status)) {
		ucol_setAttribute(coll, UCOL_STRENGTH, strength_attribute_to_ICU_flag((t_sy_object *)x, strength), &status);
		if (U_FAILURE(status)) goto error;
		
		ucol_setAttribute(coll, UCOL_NUMERIC_COLLATION, x->digits ? UCOL_ON : UCOL_OFF, &status);
		if (U_FAILURE(status)) goto error;
		
		ucol_setAttribute(coll,	UCOL_CASE_FIRST, x->casefirst == 1 ? UCOL_UPPER_FIRST : (x->casefirst == 2 ? UCOL_LOWER_FIRST : UCOL_OFF), &status);
		if (U_FAILURE(status)) goto error;
		
		ucol_setAttribute(coll,	UCOL_ALTERNATE_HANDLING, x->ignorepunctuation == 1 ? UCOL_SHIFTED : UCOL_NON_IGNORABLE, &status);
		if (U_FAILURE(status)) goto error;
		
		void *data[2];
		data[0] = coll;
		data[1] = stored_av;
		
		qsort_r (indices_av, stored_ac, sizeof(t_atom), data, reverse ? cmpfunc_rev : cmpfunc);
//		qsort_r (stored_av, stored_ac, sizeof(t_atom), coll, reverse ? cmpfunc_rev : cmpfunc);
		
		// reconstructing atoms from indices
		for (i = 0; i < stored_ac; i++)
			*(output_av + i) = *(stored_av + atom_getlong(indices_av + i) - 1);
		
		ucol_close(coll); 
		
		sy_outlet(x->n_outlet2, NULL, stored_ac, indices_av);
		sy_outlet(x->n_outlet1, NULL, stored_ac, output_av);
		
		
	error:
		if (U_FAILURE(status))
			dev_post("Error in sorting.");

        sysmem_freeptr(stored_av);
        sysmem_freeptr(indices_av);
		sysmem_freeptr(output_av);
	}
}
