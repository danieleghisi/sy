/**
	@file
	sy.replace.c
	
	@name 
	sy.replace
	
	@realname 
	sy.replace

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	Replace characters or sequences of characters
	
	@description
	Substitutes all occurrences of a sequence of character with another one, or deletes them
	
	@discussion
	<o>sy.replace</o> also supports regular expression. 
    When using the regular expression mode (<m>re</m> attribute), any special regular expression symbol
	must be escaped with backslashes in order to be used literally.
    Refer to http://userguide.icu-project.org/strings/regexp for a detailed documentation on 
    accepted regular expression syntax.
 
	@category
	sy

	@keywords
	replace, substitute, swap, sequence, character, regular, expression, re, regexp
	
	@seealso
	sy.find, regexp
	
	@owner
	Daniele Ghisi
*/


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h
#define SY_REPLACE_MAX_PATTERNS 100


////////////////////////// object struct
typedef struct _replace 
{
	t_sy_object		n_ob;		// the object itself (must be first)

    char            re_mode;    // regexp on or off?
	t_symbol		*search[SY_REPLACE_MAX_PATTERNS];
	t_symbol		*substitution[SY_REPLACE_MAX_PATTERNS];
	long			pattern_size;
	
	void			*n_outlet;
} t_replace;



///////////////////////// function prototypes
//// standard set
void *replace_new(t_symbol *s, long argc, t_atom *argv);
void replace_free(t_replace *x);
void replace_assist(t_replace *x, void *b, long m, long a, char *s);

void replace_int(t_replace *x, t_atom_long num);
void replace_float(t_replace *x, double num);
void replace_anything(t_replace *x, t_symbol *msg, long ac, t_atom *av);
void replace_bang(t_replace *x);
	
t_max_err syobj_setattr_search(t_replace *x, t_object *attr, long ac, t_atom *av);
t_max_err syobj_setattr_substitute(t_replace *x, t_object *attr, long ac, t_atom *av);

	
//////////////////////// global class pointer variable
void *replace_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();

	c = class_new("sy.replace", (method)replace_new, (method)replace_free, (long)sizeof(t_replace), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)replace_assist,			"assist",		A_CANT, 0);  

	// @method anything @digest Replace characters
	// @description For each incoming symbol, the <m>search</m> characters are searched, and substituted
	// with the corresponding <m>replace</m> characters. The result is then output.
	// 	Notice that since <o>sy.replace</o> support regular expression, any special regular expression symbol 
	// must be escaped with backslashes in order to be used literally.
	class_addmethod(c, (method)replace_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)replace_float,			"float",		A_FLOAT,	0);
	class_addmethod(c, (method)replace_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)replace_anything,		"anything",		A_GIMME,	0);

	// @method bang @digest Replace characters
	// @description Replace characters of the most recently received input list.
	class_addmethod(c, (method)replace_bang,			"bang",			0);

	syobj_class_add_numin_attr(c);
	syobj_class_add_numout_attr(c);
	syobj_class_add_maxdecimals_attr(c);
    syobj_class_add_listout_attr(c);


    CLASS_ATTR_CHAR(c, "re", 0, t_replace, re_mode);
    CLASS_ATTR_STYLE_LABEL(c,"re",0,"onoff","Use Regular Expressions");
    CLASS_ATTR_BASIC(c,"re",0);
    // @description Toggles the ability to use regular expressions for searching (default: off).
    // The regular expression syntax is the standard one, except for capture group, identified via the dollar sign, and
    // not the percentage sign (notice that you might need to escape dollar sign in Max if it is at the beginning of a symbol).

    CLASS_ATTR_SYM_VARSIZE(c, "search", 0, t_replace, search, pattern_size, SY_REPLACE_MAX_PATTERNS);
	CLASS_ATTR_STYLE_LABEL(c,"search",0,"text","Patterns to Search");
	CLASS_ATTR_ACCESSORS(c, "search", (method)NULL, (method)syobj_setattr_search);
	CLASS_ATTR_BASIC(c,"search",0);
	// @description Sets the symbol (or symbols) determining the patterns to be searched.

	CLASS_ATTR_SYM_VARSIZE(c, "substitute", 0, t_replace, substitution, pattern_size, SY_REPLACE_MAX_PATTERNS); 
	CLASS_ATTR_STYLE_LABEL(c,"substitute",0,"text","Patterns to Substitute");
	CLASS_ATTR_ACCESSORS(c, "substitute", (method)NULL, (method)syobj_setattr_substitute);
	CLASS_ATTR_BASIC(c,"substitute",0);
	// @description Sets the symbol (or symbols) containing the patterns to be substituted.
    // Default is the empty symbol (i.e. deletion of matched searched strings).
    // Just send a <m>substitute</m> message with no symbols to delete all matches of searched patterns.
	
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	replace_class = c;

	return 0;
}

t_max_err syobj_setattr_search(t_replace *x, t_object *attr, long ac, t_atom *av){
    long i;
    x->pattern_size = 0;
    for (i = 0; i < ac && i < SY_REPLACE_MAX_PATTERNS; i++) {
        t_symbol *s = atom_to_symbol(av+i, x->n_ob.l_maxdecimals);
        if (s)
            x->search[x->pattern_size++] = s;
    }
	return MAX_ERR_NONE;
}

t_max_err syobj_setattr_substitute(t_replace *x, t_object *attr, long ac, t_atom *av){
    long i;
    for (i = 0; i < ac && i < SY_REPLACE_MAX_PATTERNS; i++) {
        t_symbol *s = atom_to_symbol(av+i, x->n_ob.l_maxdecimals);
        if (s)
            x->substitution[i] = s;
    }
    for (; i < x->pattern_size; i++)
        x->substitution[i] = gensym("");
	return MAX_ERR_NONE;
}


void replace_assist(t_replace *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type symbol/list @digest Incoming symbol or list
		sprintf(s, "Incoming symbol or list");
	} 
	else {	// @out 0 @type symbol/list @digest Symbols with replaced characters
		sprintf(s, "Modified output"); 			
	}
}

void replace_free(t_replace *x)
{
	syobj_obj_free((t_sy_object *)x);
}


void *replace_new(t_symbol *s, long argc, t_atom *argv)
{
	t_replace *x = NULL;
	long true_ac = attr_args_offset(argc, argv);
	long i;
    
	if ((x = (t_replace *)object_alloc(replace_class))) {

		x->pattern_size = 0;
		for (i = 0; i < SY_REPLACE_MAX_PATTERNS; i++) {
			x->search[i] = gensym("");
			x->substitution[i] = gensym("");
		}

        syobj_obj_setup((t_sy_object *)x, 1);
        
        attr_args_process(x, argc, argv);

		// @arg 0 @name param @optional 1 @type list @digest Parameters
		// @description Sets the parameters for the search and replace.
		// the first argument is the first symbol to <m>search</m>, the second argument
		// is the first symbol to <m>substitute</m>, the third argument is the second symbol to <m>search</m>,
		// while the fourth argument is the third symbol to <m>substitute</m> and so on.
        // Use the empty symbol "" to delete a search string, or if you define just two arguments and drop
        // the second one, replace will just delete the searched string.
		
		for (i = 0; i < true_ac; i++) {
            t_symbol *s = atom_to_symbol(argv+i, x->n_ob.l_maxdecimals);
			if (s) {
				if (i%2)
					x->substitution[i/2] = s;
				else
					x->search[i/2] = s;
			}
		}
        x->pattern_size = (true_ac % 2 == 0 ? true_ac/2 : (true_ac+1)/2);
		
		x->n_outlet = syout((t_object *)x);
	}
	return (x);
}

void replace_int(t_replace *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	replace_anything(x, _sym_list, 1, argv);
}

void replace_float(t_replace *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	replace_anything(x, _sym_list, 1, argv);
}

void replace_bang(t_replace *x)
{	
	replace_anything(x, _sym_bang, 0, NULL);
}

long replace_symbol_by_length_pattern(t_symbol *s, long *pattern, long pattern_length, t_symbol ***out_syms, long max_out_syms)
{
	long i, pattern_sum = 0;
	for (i = 0; i < pattern_length; i++) 
		pattern_sum += labs(pattern[i]);
	
	int32_t size = 0;
	UChar32 *symbol32 = symbol_to_uchar32_array(s, &size);
	if (symbol32[size-1] == 0)
		size--;
	long max_output_num = (size/pattern_sum + 1) * pattern_length;
	long num_outs = 0;
	
	*out_syms = (t_symbol **)sysmem_newptr(max_output_num * sizeof(t_symbol *));
	long pattern_idx = 0, cur_idx = 0;
	UChar32 *cur = symbol32;

	if (max_out_syms == 0)
		max_out_syms = size;

	while (true) {
		long this_size = pattern[pattern_idx];
		
		if (cur_idx + this_size > size)
			this_size = size - cur_idx;
		
		if (num_outs + 1 >= max_out_syms)
			this_size = size - cur_idx;
		
		UChar32 *sub = (UChar32 *)sysmem_newptr((this_size + 1) * sizeof(UChar32));
		sysmem_copyptr(cur, sub, this_size * sizeof(UChar32));
		sub[this_size] = 0;
		cur += this_size;
		cur_idx += this_size;
		(*out_syms)[num_outs++] = symbol_from_uchar32_array(sub, this_size);
		sysmem_freeptr(sub);
		
		pattern_idx = (pattern_idx + 1) % pattern_length;
		
		if (cur_idx >= size)
			break;
	}
	return num_outs;
}




long replace_once_easy_fn(t_sy_object *x, t_atom *atom_in, t_atom *atom_out, void *search, void *replace, void *dummy)
{
	char type_in = atom_gettype(atom_in); 
	
	if (type_in == A_SYM) {	
		t_symbol *res = symbol_replace_easy(atom_getsym(atom_in), (t_symbol *)search, (t_symbol *)replace);
		atom_setsym(atom_out, res ? res : atom_getsym(atom_in));
	} else if (type_in == A_LONG || type_in == A_FLOAT) {
		*atom_out = *atom_in;
	} else
		return 0; // dropped
	return 1;
}


long replace_once_regexp_fn(t_sy_object *x, t_atom *atom_in, t_atom *atom_out, void *search, void *replace, void *dummy)
{
    char type_in = atom_gettype(atom_in);
    
    if (type_in == A_SYM) {
        t_symbol *res = symbol_replace_regexp(atom_getsym(atom_in), (t_symbol *)search, (t_symbol *)replace);
        atom_setsym(atom_out, res ? res : atom_getsym(atom_in));
    } else if (type_in == A_LONG || type_in == A_FLOAT) {
        *atom_out = *atom_in;
    } else
        return 0; // dropped
    return 1;
}


void replace_anything(t_replace *x, t_symbol *msg, long ac, t_atom *av)
{
	long	stored_ac = 0;
	t_atom	*stored_av = NULL;
	t_atom	*out_av = NULL;
	long	i;
	
	if (msg != _sym_bang) 
		syobj_store_content((t_sy_object *) x, msg, ac, av, 0);
	
	stored_ac = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_MODE, &stored_av);
	atom_array_duplicate(stored_ac, stored_av, &out_av, SY_NUMIN_MODE_LET_THROUGH, 0);

	systhread_mutex_lock(x->n_ob.l_mutex);
	for (i = 0; i < x->pattern_size; i++) {
        iterate_on_gimme((t_sy_object *)x, NULL, stored_ac, out_av, &out_av, x->re_mode ? replace_once_regexp_fn : replace_once_easy_fn, x->search[i], x->substitution[i], NULL);
	}
	systhread_mutex_unlock(x->n_ob.l_mutex);
	
	syobj_atom_array_reparse_account_for_numout((t_sy_object *)x, stored_ac, out_av);
    syobj_atom_array_reparse_account_for_listout((t_sy_object *)x, &stored_ac, &out_av);

	if (stored_ac > 0)
		sy_outlet(x->n_outlet, NULL, stored_ac, out_av);
	
	sysmem_freeptr(out_av); 
	sysmem_freeptr(stored_av);
}
