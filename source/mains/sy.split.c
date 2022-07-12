/**
	@file
	sy.split.c
	
	@name 
	sy.split
	
	@realname 
	sy.split

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	Split symbols according to separators
	
	@description
	Breaks incoming symbols according to pattern lengths or separators.
	
	@discussion
    Notice that since <o>sy.replace</o> support regular expression, any special regular expression symbol
	must be escaped with backslashes in order to be used literally.
    Refer to http://userguide.icu-project.org/strings/regexp for a detailed documentation on
    accepted regular expression syntax.

	@category
	sy

	@keywords
	split, separator, divide, break
	
	@seealso
	sy.slice
	
	@owner
	Daniele Ghisi
*/


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h
#define SY_SPLIT_MAX_PATTERN_LENGTH 100
#define SY_SPLIT_MAX_SEPARATORS 100

/** Case conversions */
typedef enum _sy_split_modes {
	SY_SPLIT_BY_LENGTH = 0,			///< Split by fixed length pattern
	SY_SPLIT_BY_SEPARATOR = 1,		///< Split by a separator
	SY_SPLIT_BY_CAPTURE_GROUP = 2,	///< Split by a capture group
} e_sy_split_modes;


////////////////////////// object struct
typedef struct _split 
{
	t_sy_object		n_ob;		// the object itself (must be first)

	char			mode;
	
	t_symbol		*separator_or_capture_group[SY_SPLIT_MAX_SEPARATORS];
	long			split_separators_size;
	long			split_length[SY_SPLIT_MAX_PATTERN_LENGTH];
	long			split_length_size;
	char			output_empty_syms;
	long			maxnum;
	
	void			*n_outlet;
} t_split;



///////////////////////// function prototypes
//// standard set
void *split_new(t_symbol *s, long argc, t_atom *argv);
void split_free(t_split *x);
void split_assist(t_split *x, void *b, long m, long a, char *s);

void split_int(t_split *x, t_atom_long num);
void split_float(t_split *x, double num);
void split_anything(t_split *x, t_symbol *msg, long ac, t_atom *av);
void split_bang(t_split *x);
	
t_max_err split_setattr_mode(t_split *x, t_object *attr, long ac, t_atom *av);

	
//////////////////////// global class pointer variable
void *split_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();

	c = class_new("sy.split", (method)split_new, (method)split_free, (long)sizeof(t_split), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)split_assist,			"assist",		A_CANT, 0);  

	// @method anything @digest Split symbols
	// @description Split each incoming symbol according to the defined <m>mode</m>.
	class_addmethod(c, (method)split_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)split_float,			"float",		A_FLOAT,	0);
	class_addmethod(c, (method)split_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)split_anything,		"anything",		A_GIMME,	0);

	// @method bang @digest Split symbols
	// @description Splits the symbols of the most recently received input list.
	class_addmethod(c, (method)split_bang,			"bang",			0);

	syobj_class_add_numin_attr(c);
	syobj_class_add_numout_attr(c);
	syobj_class_add_maxdecimals_attr(c);
    syobj_class_add_listin_attr(c);
    syobj_class_add_listout_attr(c);

	CLASS_ATTR_CHAR(c, "by", 0, t_split, mode); 
	CLASS_ATTR_STYLE_LABEL(c,"by",0,"enumindex","Split Mode");
	CLASS_ATTR_ENUMINDEX(c,"by", 0, "By Length By Separator By Capture Group"); 
	CLASS_ATTR_BASIC(c,"by",0);
	CLASS_ATTR_ACCESSORS(c, "by", (method)NULL, (method)split_setattr_mode);
	// @description Sets the mode for the splitting: <br />
	// - By Length (default): split is performed at regular interval of characters, given a length pattern set by <m>length</m> attribute; <br />
	// - By Separator: split is performed whenever a separating character is found, set by the <m>separator</m> attribute; <br />
	// - By Capture Group: split is performed according to capture groups, identified by a starting and ending group character (see <m>separator</m>). <br />
	
	CLASS_ATTR_SYM_VARSIZE(c, "separator", 0, t_split, separator_or_capture_group, split_separators_size, SY_SPLIT_MAX_SEPARATORS); 
	CLASS_ATTR_STYLE_LABEL(c,"separator",0,"text","Separator(s) Or Capture Group");
	CLASS_ATTR_BASIC(c,"separator",0);
	// @description In "By Separator" mode, sets the separating symbols. Default is the standard space.
	// In "By Capture Group" mode, only two symbols are expected, containing the capture group start and end.

	CLASS_ATTR_LONG_VARSIZE(c, "length", 0, t_split, split_length, split_length_size, SY_SPLIT_MAX_PATTERN_LENGTH); 
	CLASS_ATTR_STYLE_LABEL(c,"length",0,"text","Length (Or Length Pattern)");
	CLASS_ATTR_BASIC(c,"length",0);
	// @description In "By Length" mode, sets the length or the length pattern for splitting symbols.
	
	CLASS_ATTR_CHAR(c, "empty", 0, t_split, output_empty_syms); 
	CLASS_ATTR_STYLE_LABEL(c,"empty",0,"onoff","Output Empty Symbols");
	// @description Toggles the ability to also output empty symbols (e.g. when two separators in a row are found).

	CLASS_ATTR_LONG(c, "maxnum", 0, t_split, maxnum); 
	CLASS_ATTR_STYLE_LABEL(c,"maxnum",0,"text","Maximum Number Of Substrings");
	CLASS_ATTR_BASIC(c,"maxnum",0);
	// @description Sets the maximum number of substrings per symbol. Defaults to 0 (= no maximum).
	
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	split_class = c;

	return 0;
}

t_max_err split_setattr_mode(t_split *x, t_object *attr, long ac, t_atom *av){
	if (ac && av) {
		x->mode = CLAMP(atom_getlong(av), 0, 2);
		object_attr_setdisabled((t_object *)x, gensym("separator"), x->mode == SY_SPLIT_BY_LENGTH);
		object_attr_setdisabled((t_object *)x, gensym("length"), x->mode != SY_SPLIT_BY_LENGTH);
	}
	return MAX_ERR_NONE;
}


void split_assist(t_split *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type symbol/list @digest Incoming symbol or list
		sprintf(s, "Incoming symbol or list");
	} 
	else {	// @out 0 @type list @digest Symbols split according to the separator
		sprintf(s, "Split output"); 			
	}
}

void split_free(t_split *x)
{
	syobj_obj_free((t_sy_object *)x);
}


void *split_new(t_symbol *s, long argc, t_atom *argv)
{
	t_split *x = NULL;
	long true_ac = attr_args_offset(argc, argv);
	long i;
    
	if ((x = (t_split *)object_alloc(split_class))) {

		x->output_empty_syms = 0;
		x->maxnum = 0;
		x->mode = SY_SPLIT_BY_LENGTH;
		x->split_length[0] = 1;
		x->split_length_size = 1;
		x->split_separators_size = 1;
		x->separator_or_capture_group[0] = gensym(" ");
		
		// @arg 0 @name length_or_separator @optional 1 @type int/symbol/list @digest Split Length or Separator
		// @description If the first argument is an integer, the arguments set the initial value for the <m>length</m> attribute,
		// (i.e. the length or pattern length for the split chunks)
		// and the <m>by</m> attribute (determining the object mode) is set to "By Length".
		// If the first argument is a symbol, the arguments set the initial value for the <m>separator</m> attribute,
		// (i.e. the separator or separators for splitting)
		// and the <m>by</m> attribute is set to "By Separator".
		
		if (true_ac && atom_gettype(argv) == A_LONG) {
			x->mode = SY_SPLIT_BY_LENGTH;
			x->split_length_size = 0;
			for (i = 0; i < SY_SPLIT_MAX_PATTERN_LENGTH && i < true_ac; i++)
				if (atom_gettype(argv+i) == A_LONG)
					x->split_length[x->split_length_size++] = atom_getlong(argv);
		} else if (true_ac && atom_gettype(argv) == A_SYM) {
			x->split_separators_size = 0;
			x->mode = SY_SPLIT_BY_SEPARATOR;
			for (i = 0; i < SY_SPLIT_MAX_SEPARATORS && i < true_ac; i++)
				if (atom_gettype(argv+i) == A_SYM)
					x->separator_or_capture_group[x->split_separators_size++] = atom_getsym(argv);
		}

        syobj_obj_setup((t_sy_object *)x, 1);

        attr_args_process(x, argc, argv);
		
		x->n_outlet = syout((t_object *)x);
	}
	return (x);
}

void split_int(t_split *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	split_anything(x, _sym_list, 1, argv);
}

void split_float(t_split *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	split_anything(x, _sym_list, 1, argv);
}

void split_bang(t_split *x)
{	
	split_anything(x, _sym_bang, 0, NULL);
}

long split_symbol_by_length_pattern(t_symbol *s, long *pattern, long pattern_length, t_symbol ***out_syms, long max_out_syms)
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

UChar *separators_to_combined_or_char_array(t_symbol **separators, long num_separators)
{
	const long	ALLOCATE_STEP_SIZE = 256;
	UChar		*out = (UChar *)sysmem_newptr(ALLOCATE_STEP_SIZE * sizeof(UChar));
	long		num_allocated_elem = ALLOCATE_STEP_SIZE, i;
	long		cur = 0;
	for (i = 0; i < num_separators; i++) {
		int32_t this_size = 0;
		if (strlen(separators[i]->s_name) < 256) {
			UChar *thisText = symbol_to_uchar_array(separators[i], &this_size);
			
			if (cur + this_size + 2 > num_allocated_elem) {
				num_allocated_elem += ALLOCATE_STEP_SIZE;
				out = (UChar *)sysmem_resizeptr(out, num_allocated_elem * sizeof(UChar));
			}
			
			sysmem_copyptr(thisText, out + cur, this_size * sizeof(UChar));
			cur += this_size;
			if (i < num_separators - 1)
				*(out + cur++) = '|';
			
			sysmem_freeptr(thisText);
		}
	}
		 
	 out[cur] = 0;
	 return out;
}

long split_symbol_by_separator_or_capture_group(t_symbol *s, char mode, t_symbol **separators, long num_separators, 
												t_symbol ***out_syms, long max_out_syms)
{
    long	num_codepoints = symbol_get_num_codepoints(s, true);

	if (max_out_syms <= 0)
		max_out_syms = num_codepoints;
	
	UChar		*textToSplit = symbol_to_uchar_array(s, NULL);
	UChar		*textSeparator;
	UChar		*buf = (UChar *)sysmem_newptrclear((3 * num_codepoints + 1) * sizeof(UChar));
	UChar		**fields = (UChar **)sysmem_newptr(max_out_syms * sizeof(UChar *));
	int32_t		numFields = 0;
	int32_t		requiredCapacity;
//	int32_t		spaceNeeded;
	UErrorCode           status = U_ZERO_ERROR;
	long i;
	
	status = U_ZERO_ERROR;
	URegularExpression *re;
	
	if (mode == SY_SPLIT_BY_CAPTURE_GROUP) {
		t_symbol *groupopen = num_separators > 0 ? separators[0] : NULL;
		t_symbol *groupclose = num_separators > 1 ? separators[1] : NULL;
		if (!groupopen || !groupclose) {
			status = U_ILLEGAL_ARGUMENT_ERROR;
		} else {
			int32_t opensize = 0, closesize = 0;
			UChar *open = symbol_to_uchar_array(groupopen, &opensize);
			UChar *close = symbol_to_uchar_array(groupclose, &closesize);
			textSeparator = (UChar *)sysmem_newptr((5 + opensize + closesize + 1) * sizeof(UChar));
			sysmem_copyptr(open, textSeparator, opensize * sizeof(UChar));
			sysmem_copyptr(close, textSeparator + opensize + 5, closesize * sizeof(UChar));
			textSeparator[1] = '(';
			textSeparator[2] = '.';
			textSeparator[3] = '*';
			textSeparator[4] = '?';
			textSeparator[5] = ')';
			textSeparator[5+opensize+closesize] = 0;
			re = uregex_open(textSeparator, -1, 0, NULL, &status);
		}
	} else { 
		textSeparator = separators_to_combined_or_char_array(separators, num_separators);
		re = uregex_open(textSeparator, -1, 0, NULL, &status);
	}
	
	if (U_SUCCESS(status)) {
		//	URegularExpression *re = uregex_openC("p", 0, NULL, &status);
		uregex_setText(re, textToSplit, -1, &status); // simple split
		
		if (U_SUCCESS(status)) {
//			memset(fields, -1, sizeof(fields));
			numFields = uregex_split(re, buf, 3 * num_codepoints + 1, &requiredCapacity, fields, max_out_syms, &status);
			
			if(U_SUCCESS(status)) {
				
				*out_syms = (t_symbol **)sysmem_newptr(numFields * sizeof(t_symbol *));
				for (i = 0; i < numFields; i++) 
					(*out_syms)[i] = symbol_from_uchar_array(fields[i], -1);
			}
		}
	}
	
	sysmem_freeptr(buf);
	sysmem_freeptr(fields);
	sysmem_freeptr(textToSplit);
	sysmem_freeptr(textSeparator);
	
	uregex_close(re);
	return numFields;
}


void split_anything(t_split *x, t_symbol *msg, long ac, t_atom *av)
{
	long	stored_ac = 0;
	t_atom	*stored_av = NULL;
	long	i, j;
	long	maxnum = x->maxnum;
	char	output_empty_syms = x->output_empty_syms;
	char	mode = x->mode;
    long    listin = x->n_ob.l_listin_mode;
    
	if (msg != _sym_bang) 
		syobj_store_content((t_sy_object *) x, msg, ac, av, 0);
	
    stored_ac = syobj_get_store_contents((t_sy_object *) x, 0, listin == SY_LISTIN_MODE_GLOBALLY ? SY_STORE_CLONE_AS_SINGLE_SYMBOL : SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_MODE, &stored_av);
	
	const long	ALLOCATE_STEP_SIZE = 256;
	t_atom		*out_av = (t_atom *)sysmem_newptr(ALLOCATE_STEP_SIZE * sizeof(t_atom));
	long		num_allocated_elem = ALLOCATE_STEP_SIZE;
	long		out_ac = 0;

	for (i = 0; i < stored_ac; i++) {
		if (atom_gettype(stored_av + i) == A_SYM &&
			!(mode == SY_SPLIT_BY_LENGTH && x->split_length_size == 0)) {
			t_symbol **out_syms = NULL;
			long num_out;
			systhread_mutex_lock(x->n_ob.l_mutex);
			if (mode == SY_SPLIT_BY_LENGTH) {
				num_out = split_symbol_by_length_pattern(atom_getsym(stored_av+i), x->split_length, x->split_length_size, &out_syms, maxnum);
			} else
				num_out = split_symbol_by_separator_or_capture_group(atom_getsym(stored_av+i), mode, x->separator_or_capture_group, x->split_separators_size, &out_syms, maxnum);
			systhread_mutex_unlock(x->n_ob.l_mutex);
			
			for (j = 0; j < num_out; j++) {
				if (out_syms[j] == gensym("") && !output_empty_syms) 
					continue;
				
				atom_setsym(out_av + out_ac++, out_syms[j]);

				if (out_ac >= num_allocated_elem) {
					// resize
					num_allocated_elem += ALLOCATE_STEP_SIZE;
					out_av = (t_atom *)sysmem_resizeptr(out_av, num_allocated_elem * sizeof(t_atom));
				}
			}
			sysmem_freeptr(out_syms);
		} else {
			*(out_av + out_ac++) = *(stored_av + i);
			if (out_ac >= num_allocated_elem) {
				// resize
				num_allocated_elem += ALLOCATE_STEP_SIZE;
				out_av = (t_atom *)sysmem_resizeptr(out_av, num_allocated_elem * sizeof(t_atom));
			}
		}
	}

	syobj_atom_array_reparse_account_for_numout((t_sy_object *)x, out_ac, out_av);
    syobj_atom_array_reparse_account_for_listout((t_sy_object *)x, &out_ac, &out_av);

	if (out_ac > 0)
		sy_outlet(x->n_outlet, NULL, out_ac, out_av);
	
	sysmem_freeptr(stored_av);
	sysmem_freeptr(out_av);
}
