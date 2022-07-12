/**
	@file
	sy.find.c
	
	@name 
	sy.find
	
	@realname 
	sy.find

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	Find occurrences of substrings in a symbol
	
	@description
	Searches all the occurrences of substrings in a given symbol.
	
	@discussion
	
	@category
	sy

	@keywords
	search, find, substring, subsymbol, match, retrieve
	
	@seealso
	sy.replace, regexp
	
	@owner
	Daniele Ghisi
*/


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h
#include "unicode/ucol.h"

////////////////////////// object struct
typedef struct _find 
{
	t_sy_object		n_ob;		// the object itself (must be first)
	
	long			strength;	// strength of the comparison for the matches
	char			ignorepunctuation;	// if set, all the alternate characters and punctuations are moved from the first to the quaternary level, 
										// so that up to the tertiary level, for instance, "a-b" and "ab" are the same.
	char			overlap;
	char			elcomparison; // 0 for USEARCH_STANDARD_ELEMENT_COMPARISON, 1 for USEARCH_PATTERN_BASE_WEIGHT_IS_WILDCARD, 2 for USEARCH_ANY_BASE_WEIGHT_IS_WILDCARD
	
	long			n_in;   // space for the inlet number used by all the proxies
    void			*n_proxy1;
	void			*n_outlet1;
	void			*n_outlet2;
	void			*n_outlet3;
} t_find;



///////////////////////// function prototypes
//// standard set
void *find_new(t_symbol *s, long argc, t_atom *argv);
void find_free(t_find *x);
void find_assist(t_find *x, void *b, long m, long a, char *s);
void find_inletinfo(t_find *x, void *b, long a, char *t);

void find_int(t_find *x, t_atom_long num);
void find_float(t_find *x, double num);
void find_anything(t_find *x, t_symbol *msg, long ac, t_atom *av);
void find_bang(t_find *x);



//////////////////////// global class pointer variable
void *find_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();
	
	c = class_new("sy.find", (method)find_new, (method)find_free, (long)sizeof(t_find), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)find_assist,			"assist",		A_CANT, 0);  
	class_addmethod(c, (method)find_inletinfo,	"inletinfo",	A_CANT,		0);

	// @method symbol @digest Set pattern
	// A <m>symbol</m> in the right inlet sets the pattern to be found (a single symbol is expected, a number will be converted automatically to symbol). 

	// @method list @digest Find pattern
	// @description A <m>list</m> in the left inlet triggers the search of the pattern set via the right inlet in any of the elements
	// of such list. The matches are output from the first outlet, along with their indices (starting Unicode code point position of each match, counting from 1),
	// and the indices of the symbols in the list where they have been found (counting from 1).
	// Numeric atoms of the list are automatically converted to symbols.
	class_addmethod(c, (method)find_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)find_float,			"float",		A_FLOAT,	0);
	class_addmethod(c, (method)find_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)find_anything,		"anything",		A_GIMME,	0);
	
	// @method bang @digest Change find
	// @description Changes the find of the most recently received input list.
	class_addmethod(c, (method)find_bang,			"bang",			0);
	
	syobj_class_add_maxdecimals_attr(c);
	syobj_class_add_locale_attr(c);
	
	CLASS_ATTR_LONG(c, "strength", 0, t_find, strength); 
	CLASS_ATTR_STYLE_LABEL(c,"strength",0,"enumindex","Comparison Strength");
	CLASS_ATTR_ENUMINDEX(c,"strength", 0, "Zero (nothing) Primary (characters) Secondary (accents) Tertiary (case) Quaternary (punctuation) Identical"); 
	CLASS_ATTR_BASIC(c,"strength",0);
	// @description Sets the comparison strength for the substring matching.
	// @copy SY_DOC_COMPARISON_STRENGTH
	
	CLASS_ATTR_CHAR(c, "alternate", 0, t_find, ignorepunctuation); 
	CLASS_ATTR_STYLE_LABEL(c,"alternate",0,"onoff","Ignore Alternate Characters");
	// @description Toggles the ability to move the differences of punctuation and alternate characters from the first to the fourth strength 
	// level (see <m>strength</m> attribute). When this attribute is active, for instance, it means that up to the tertiary level symbols like
	// "ab" and "a-b" are equal. Defaults to 0.
	
	CLASS_ATTR_CHAR(c, "overlap", 0, t_find, overlap); 
	CLASS_ATTR_STYLE_LABEL(c,"overlap",0,"onoff","Allow Overlapping Matches");
	CLASS_ATTR_BASIC(c,"overlap",0);
	// @description Toggles the ability to allow overlapping matches. Defaults to 1.
	
//	CLASS_ATTR_CHAR(c, "compare", 0, t_find, elcomparison); 
//	CLASS_ATTR_STYLE_LABEL(c,"compare",0,"enumindex","Element Comparison");
//	CLASS_ATTR_ENUMINDEX(c,"compare", 0, "Standard Pattern Base Weight Is Wildchar Any Base Weight Is Wildchar"); 
	// @exclude all
	// @description Sets the options for comparing elements (collation): <br />  <br />
	// - Standard (default): standard collation element comparison at the specified collator <m>strength</m>. <br /> <br />
	// - Pattern Base Weight Is Wildchar: collation element comparison is modified to effectively provide behavior between 
	// the specified <m>strength</m> and <m>strength</m> - 1.	Collation elements in the pattern that have the base weight for the specified 
	// strength are treated as "wildcards" that match an element with any other weight at that collation level in the searched text. 
	// For example, with a secondary-strength English collator, a plain 'e' in the pattern will match a plain e or an e with any 
	// diacritic in the searched text, but an e with diacritic in the pattern will only match an e with the same diacritic in the 
	// searched text. <br /> <br />
	// - Any Base Weight Is Wildchar: collation element comparison is modified to effectively provide behavior between the specified 
	// <m>strength</m> and <m>strength</m> - 1. 
	// Collation elements in either the pattern or the searched text that have the base weight for the specified strength are treated as 
	// "wildcards" that match an element with any other weight at that collation level. For example, with a secondary-strength English 
	// collator, a plain 'e' in the pattern will match a plain e or an e with any diacritic in the searched text, but an e with diacritic 
	// in the pattern will only match an e with the same diacritic or a plain e in the searched text.
	
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	find_class = c;
	
	return 0;
}



void find_assist(t_find *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // inlet
		if (a == 0)  // @in 0 @type symbol/list @digest Element or elements to be searched
			sprintf(s, "symbol/list: Element(s) to be searched");
		else // @in 1 @type symbol @digest Pattern to be found
			sprintf(s, "symbol: Substring to be searched");
	} 
	else {	// outlet
		if (a == 0) // @out 0 @type list @digest Found occurrences of the pattern
			sprintf(s, "list: Occurrences"); 			
		else if (a == 1) // @out 0 @type list @digest Indices of occurrences
			sprintf(s, "list: Index of each occurrence"); // @description The index of an occurrence is the index of the character (meant as code point) where the pattern starts, counting from 1. 			
		else if (a == 2) // @out 1 @type list @digest Indices of atoms where occurrences are found
			sprintf(s, "list: Index of the atom of each occurrence"); 			
	}
}


void find_inletinfo(t_find *x, void *b, long a, char *t)
{
	if (a)
		*t = 1;
}

void find_free(t_find *x)
{
	object_free(x->n_proxy1);
	syobj_obj_free((t_sy_object *)x);
}


void *find_new(t_symbol *s, long argc, t_atom *argv)
{
	t_find *x = NULL;
	long true_ac = attr_args_offset(argc, argv);
    
	if ((x = (t_find *)object_alloc(find_class))) {
		
		syobj_obj_setup((t_sy_object *)x, 2);

		x->strength = 3;  // tertiary
		x->ignorepunctuation = 0;
		x->overlap = 1;
		x->elcomparison = 0;
		
		// @arg 0 @name pattern @optional 1 @type symbol @digest Pattern to be found
		// @description The optional argument sets the initial value for the pattern to be found.
		if (true_ac)
			syobj_store_content((t_sy_object *)x, NULL, true_ac, argv, 1);
		
		
/*		// TEST
		char *tgtstr = "The quick brown fox jumps over the lazy dog.";
		char *patstr = "fox";
		UChar target[64];
		UChar pattern[16];
		UErrorCode status = U_ZERO_ERROR;
		
		u_uastrcpy(target, tgtstr);
		u_uastrcpy(pattern, patstr);
        UCollator     *collator = ucol_open("en_US", &status);
//		UStringSearch *searcher = usearch_open(pattern, -1, target, -1, "en_US", NULL, &status);
		UStringSearch *searcher = usearch_openFromCollator(pattern, -1, target, -1, collator, NULL, &status);
		
		if (U_FAILURE(status))
			post("Failure1");
		
		usearch_setAttribute(searcher, USEARCH_ELEMENT_COMPARISON, USEARCH_PATTERN_BASE_WEIGHT_IS_WILDCARD, &status);
		if (U_FAILURE(status))
			post("Failure2");

*/		
		
		
		
        attr_args_process(x, argc, argv);
		
		x->n_proxy1 = proxy_new((t_object *) x, 1, &x->n_in);

		x->n_outlet3 = syout((t_object *)x);
		x->n_outlet2 = syout((t_object *)x);
		x->n_outlet1 = syout((t_object *)x);
	}
	return (x);
}

void find_int(t_find *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	find_anything(x, _sym_list, 1, argv);
}

void find_float(t_find *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	find_anything(x, _sym_list, 1, argv);
}

void find_bang(t_find *x)
{	
	find_anything(x, _sym_bang, 0, NULL);
}

void find_anything(t_find *x, t_symbol *msg, long ac, t_atom *av)
{
	long	stored_ac1, stored_ac2;
	t_atom	*stored_av1 = NULL, *stored_av2 = NULL, *cur_in;
	long i, inlet = proxy_getinlet((t_object *) x);
	long strength = x->strength;
	char overlap = x->overlap;
	char ignorepunctuation = x->ignorepunctuation;
//	char elcompare = x->elcomparison;
	
	if (msg != _sym_bang)  {
		syobj_store_content((t_sy_object *) x, msg, ac, av, inlet);
		if (inlet == 1)
			warn_if_ac_greater_than_one((t_sy_object *)x, ac);
	}
	
	
	// TO DO : handle strength = 0 case;
	
	if (inlet == 0) {
		stored_ac1 = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_MODE, &stored_av1);
		stored_ac2 = syobj_get_store_contents((t_sy_object *) x, 1, SY_STORE_DONT_CLONE, &stored_av2);
		
		if (stored_ac2 > 0) {
			t_symbol *pattern_sym = atom_to_symbol(stored_av2, x->n_ob.l_maxdecimals);
			
			if (atom_gettype(stored_av2) != A_SYM) 
				object_warn((t_object *)x, "Pattern to be found will be converted to symbol.");
			
			if (pattern_sym) {
				const long ALLOCATE_STEP_SIZE = 256;
				t_atom		*matches_atom_idx = (t_atom *)sysmem_newptr(ALLOCATE_STEP_SIZE * sizeof(t_atom));
				t_atom		*matches_idx = (t_atom *)sysmem_newptr(ALLOCATE_STEP_SIZE * sizeof(t_atom));
				t_atom		*matches = (t_atom *)sysmem_newptr(ALLOCATE_STEP_SIZE * sizeof(t_atom));
				long		num_allocated_elem = ALLOCATE_STEP_SIZE;
				long		match_count = 0;

				
				for (i = 0, cur_in = stored_av1; i < stored_ac1; i++, cur_in++) {
					UErrorCode status = U_ZERO_ERROR; 
					UChar *pattern = symbol_to_uchar_array(pattern_sym, NULL);
					t_symbol *container_sym = atom_to_symbol(cur_in, x->n_ob.l_maxdecimals);

					if (container_sym) {
						UChar *container = symbol_to_uchar_array(container_sym, NULL);
						UCollator *coll = ucol_open(x->n_ob.l_locale->s_name, &status); 
						if (U_SUCCESS(status)) {
							
							ucol_setAttribute(coll, UCOL_STRENGTH, strength_attribute_to_ICU_flag((t_sy_object *)x, strength), &status);
							if (U_FAILURE(status)) goto error;
							
							ucol_setAttribute(coll,	UCOL_ALTERNATE_HANDLING, ignorepunctuation == 1 ? UCOL_SHIFTED : UCOL_NON_IGNORABLE, &status);
							if (U_FAILURE(status)) goto error;
							
							UStringSearch *search = usearch_openFromCollator(pattern, -1, container, -1, coll, NULL, &status);
							if (U_FAILURE(status)) goto error;
							
							usearch_setAttribute(search, USEARCH_OVERLAP, overlap ? USEARCH_ON : USEARCH_OFF, &status);
							if (U_FAILURE(status)) goto error;
							

//							THIS THROWS AN ERROR! WHY????
//							usearch_setAttribute(search, USEARCH_ELEMENT_COMPARISON, elcompare == 1 ? USEARCH_PATTERN_BASE_WEIGHT_IS_WILDCARD :
//												 (elcompare == 2 ? USEARCH_ANY_BASE_WEIGHT_IS_WILDCARD : USEARCH_STANDARD_ELEMENT_COMPARISON), &status);
//							if (U_FAILURE(status)) goto error;
							
							if (U_SUCCESS(status)) {
								int pos = 0;
								for (pos = usearch_first(search, &status); 
									 U_SUCCESS(status) && pos != USEARCH_DONE; 
									 pos = usearch_next(search, &status)) {
									
									int32_t match_len = usearch_getMatchedLength(search);
									UChar *match = (UChar *)sysmem_newptr((match_len + 1) * sizeof(UChar));
									usearch_getMatchedText(search, match, match_len + 1, &status);
									
									if (status != 0)
										post("Status: %ld", status);
									
									if (U_FAILURE(status)) 
										break;
									
									atom_setlong(matches_idx + match_count, pos + 1);
									atom_setlong(matches_atom_idx + match_count, i + 1);
									atom_setsym(matches + match_count, symbol_from_uchar_array(match, -1));
									
									match_count++;
									
									if (match_count >= num_allocated_elem) {
										// resize pointers
										num_allocated_elem += ALLOCATE_STEP_SIZE;
										matches_atom_idx = (t_atom *)sysmem_resizeptr(matches_atom_idx, num_allocated_elem * sizeof(t_atom));
										matches_idx = (t_atom *)sysmem_resizeptr(matches_idx, num_allocated_elem * sizeof(t_atom));
										matches = (t_atom *)sysmem_resizeptr(matches, num_allocated_elem * sizeof(t_atom));
									}
									
									sysmem_freeptr(match);
								}
								
								if (U_FAILURE(status)) 
									post("Error searching for pattern.");
								
								usearch_close(search); 
								
								sy_outlet(x->n_outlet3, NULL, match_count, matches_atom_idx);
								sy_outlet(x->n_outlet2, NULL, match_count, matches_idx);
								sy_outlet(x->n_outlet1, NULL, match_count, matches);
							}	
						error:
							ucol_close(coll);
							if (U_FAILURE(status)) {
								object_error((t_object *)x, "Error searching for pattern – %s", u_errorName(status));
								sysmem_freeptr(pattern);
								break;
							}
						}
					}
					
					
					sysmem_freeptr(pattern);
				}
				
				sysmem_freeptr(matches);
				sysmem_freeptr(matches_idx);
				sysmem_freeptr(matches_atom_idx);
			}
		}
		sysmem_freeptr(stored_av1);
	}
}