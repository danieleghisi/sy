/**
	@file
	sy.filter.c
	
	@name 
	sy.filter
	
	@realname 
	sy.filter

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	Let only certain characters through

	@description
	Filters incoming characters, letting only specific categories through.
	
	@discussion
	
	@category
	sy

	@keywords
	filter, category, type, character, codepoint, let through, choose
	
	@seealso
	sy.is
	
	@owner
	Daniele Ghisi
*/


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h
#define SY_FILTER_MAX_CATEGORIES 100

////////////////////////// object struct
typedef struct _filter 
{
	t_sy_object		n_ob;		// the object itself (must be first)

	t_atom			categories[SY_FILTER_MAX_CATEGORIES];
	long			defined_categories;
	
	void			*n_outlet1;
	void			*n_outlet2;
} t_filter;



///////////////////////// function prototypes
//// standard set
void *filter_new(t_symbol *s, long argc, t_atom *argv);
void filter_free(t_filter *x);
void filter_assist(t_filter *x, void *b, long m, long a, char *s);

void filter_int(t_filter *x, t_atom_long num);
void filter_float(t_filter *x, double num);
void filter_anything(t_filter *x, t_symbol *msg, long ac, t_atom *av);
void filter_bang(t_filter *x);
	

	
//////////////////////// global class pointer variable
void *filter_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();

	c = class_new("sy.filter", (method)filter_new, (method)filter_free, (long)sizeof(t_filter), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)filter_assist,			"assist",		A_CANT, 0);  

	// @method anything @digest Filter character types
	// @description For each incoming symbols, only the accepted characters are output from the left outlet, all the rejected characters
	// are output from the right one. Acceptance depend whether characters belong or not to the defined categories, via the <m>types</m> attribute.
	class_addmethod(c, (method)filter_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)filter_float,		"float",		A_FLOAT,	0);
	class_addmethod(c, (method)filter_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)filter_anything,		"anything",		A_GIMME,	0);

	// @method bang @digest Filter most recently received list
	// @description Output the result of the filtering performed on the most recently received input data.
	class_addmethod(c, (method)filter_bang,			"bang",			0);

	syobj_class_add_numin_attr(c);
	syobj_class_add_numout_attr(c);
	syobj_class_add_maxdecimals_attr(c);	
    syobj_class_add_listin_attr(c);
    syobj_class_add_listout_attr(c);

	CLASS_ATTR_ATOM_VARSIZE(c, "types", 0, t_filter, categories, defined_categories, SY_FILTER_MAX_CATEGORIES); 
	CLASS_ATTR_STYLE_LABEL(c,"types",0,"text","Accepted Types");
	CLASS_ATTR_BASIC(c, "types", 0); 
	// @description Sets the accepted categories for the filtering. You can reverse the selection by setting a "-" (minus) as first element.
	// Categories can be defined either via their symbols (e.g. "Nd") or via their integer ID (e.g. 9). 
	
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	filter_class = c;

	return 0;
}


void filter_assist(t_filter *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {  // @in 0 @type symbol/list @digest Incoming symbol or list of symbols
		sprintf(s, "Symbol or list");
	} 
	else {
		if (a == 0)
			sprintf(s, "list: Accepted Characters"); // @out 0 @type list @digest List of integers representing character types
		else
			sprintf(s, "list: Rejected Characters"); // @out 1 @type list @digest List of symbols representing character types
	}
}

void filter_free(t_filter *x)
{
	syobj_obj_free((t_sy_object *)x);
}


void *filter_new(t_symbol *s, long argc, t_atom *argv)
{
	t_filter *x = NULL;
	long true_ac = attr_args_offset(argc, argv);
    
	if ((x = (t_filter *)object_alloc(filter_class))) {
		
		x->defined_categories = 0;
		
		// @arg 0 @name types @optional 1 @type list @digest Accepted Types
		// @description Sets the initial value for the accepted types list. See <m>types</m> attribute.
		if (true_ac) {
			long i;
			for (i = 0; i < true_ac; i++) 
				x->categories[i] = *(argv + i);
			x->defined_categories = true_ac;
		}
			
        syobj_obj_setup((t_sy_object *)x, 1);

        attr_args_process(x, argc, argv);
		
		x->n_outlet2 = syout((t_object *)x);
		x->n_outlet1 = syout((t_object *)x);
	}
	return (x);
}

void filter_int(t_filter *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	filter_anything(x, _sym_list, 1, argv);
}

void filter_float(t_filter *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	filter_anything(x, _sym_list, 1, argv);
}

void filter_bang(t_filter *x)
{	
	filter_anything(x, _sym_bang, 0, NULL);
}


long substitute_with_symbol_fn(t_sy_object *x, t_atom *atom_in, t_atom *atom_out, void *only_output_grouped_letters, void *dummy2, void *dummy3)
{
	char type_in = atom_gettype(atom_in); 
	
	if (type_in == A_LONG) {
		t_symbol *sym = category_to_symbol(atom_getlong(atom_in));
		if (*((char *)only_output_grouped_letters)) {
			char buf[2];
			buf[0] = sym->s_name[0];
			buf[1] = 0;
			sym = gensym(buf);
		}
		atom_setsym(atom_out, sym);
	} else if (type_in == A_LONG || type_in == A_FLOAT) {
		*atom_out = *atom_in;
	} else {
		return 0;
	}

	return 1;
}


char does_uchar32_belong_to_category(UChar32 ch, t_atom *category)
{
	UCharCategory ch_category = u_charType(ch);
	
	if (atom_gettype(category) == A_SYM) {
		t_symbol *sym = atom_getsym(category);
		t_symbol *ch_category_sym = category_to_symbol(ch_category);
		
		if (sym == gensym("LC")) {
			t_atom Ll, Lu, Lt;
			atom_setsym(&Ll, gensym("Ll"));
			atom_setsym(&Lu, gensym("Lu"));
			atom_setsym(&Lt, gensym("Lt"));
			return (does_uchar32_belong_to_category(ch, &Ll) || does_uchar32_belong_to_category(ch, &Lu) || does_uchar32_belong_to_category(ch, &Lt)); 
		} else if (sym == gensym("L"))
			return (ch_category_sym->s_name[0] == 'L');
		else if (sym == gensym("M"))
			return (ch_category_sym->s_name[0] == 'M');
		else if (sym == gensym("N"))
			return (ch_category_sym->s_name[0] == 'N');
		else if (sym == gensym("P"))
			return (ch_category_sym->s_name[0] == 'P');
		else if (sym == gensym("S"))
			return (ch_category_sym->s_name[0] == 'S');
		else if (sym == gensym("Z"))
			return (ch_category_sym->s_name[0] == 'Z');
		else if (sym == gensym("C"))
			return (ch_category_sym->s_name[0] == 'C');
		else
			return ch_category_sym == sym;
	} else if (atom_gettype(category) == A_LONG)
		return (atom_getlong(category) == ch_category);
	
	return 0;
}

char is_uchar32_accepted(UChar32 ch, t_atom *categories, long num_categories, char reverse)
{
	long i;
	for (i = 0; i < num_categories; i++)
		if (does_uchar32_belong_to_category(ch, categories+i))
			return reverse ? false : true;
	return reverse ? true : false;
}

void filter_symbol(t_symbol *sym, t_atom *categories, long num_categories, t_symbol **accepted_chars, t_symbol **rejected_chars)
{
	char reverse = (num_categories >= 1 && atom_gettype(categories) == A_SYM && atom_getsym(categories) == gensym("-"));
	
	if (num_categories == 0) {
		*accepted_chars = reverse ? NULL : sym;
		*rejected_chars = reverse ? sym : NULL;
		return;
	}
	
	int32_t size = 0;
	UChar32 *buf = symbol_to_uchar32_array(sym, &size);
	UChar32 *acc = (UChar32 *)sysmem_newptr((size + 1) * sizeof(UChar32));
	UChar32 *rej = (UChar32 *)sysmem_newptr((size + 1) * sizeof(UChar32));
	long i, cur_acc = 0, cur_rej = 0;
	
	for (i = 0; i < size; i++) {
		if (is_uchar32_accepted(buf[i], categories, num_categories, reverse))
			acc[cur_acc++] = buf[i];
		else
			rej[cur_rej++] = buf[i];
	}
	acc[cur_acc] = rej[cur_rej] = 0;
	
	*accepted_chars = symbol_from_uchar32_array(acc, cur_acc);
	*rejected_chars = symbol_from_uchar32_array(rej, cur_rej);
	
	sysmem_freeptr(buf);
	sysmem_freeptr(acc);
	sysmem_freeptr(rej);
}

void filter_anything(t_filter *x, t_symbol *msg, long ac, t_atom *av)
{
	long	stored_ac = 0;
	t_atom	*stored_av = NULL;
	long	i;
	
	if (msg != _sym_bang) 
		syobj_store_content((t_sy_object *) x, msg, ac, av, 0);
	
	stored_ac = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_MODE, &stored_av);
	
	t_atom  *accepted_av = (t_atom *)sysmem_newptr(stored_ac * sizeof(t_atom));
	t_atom  *rejected_av = (t_atom *)sysmem_newptr(stored_ac * sizeof(t_atom));
	long	accepted_ac = 0, rejected_ac = 0;
	
	systhread_mutex_lock(x->n_ob.l_mutex);
	for (i = 0; i < stored_ac; i++) {
		if (atom_gettype(stored_av + i) == A_SYM) {
			t_symbol *accept = NULL, *reject = NULL;
			filter_symbol(atom_getsym(stored_av+i), x->categories, x->defined_categories, &accept, &reject);
			
			if (accept != NULL && (accept != gensym("") || x->n_ob.l_listin_mode == SY_LISTIN_MODE_ELEMENTWISE))
				atom_setsym(accepted_av + accepted_ac++, accept);
			if (reject != NULL && (reject != gensym("") || x->n_ob.l_listin_mode == SY_LISTIN_MODE_ELEMENTWISE))
				atom_setsym(rejected_av + rejected_ac++, reject);
		} else {
			*(accepted_av + accepted_ac++) = *(stored_av + i);
		}
	}
	systhread_mutex_unlock(x->n_ob.l_mutex);
	
	syobj_atom_array_reparse_account_for_numout((t_sy_object *)x, rejected_ac, rejected_av);
	syobj_atom_array_reparse_account_for_numout((t_sy_object *)x, accepted_ac, accepted_av);
    syobj_atom_array_reparse_account_for_listout((t_sy_object *)x, &rejected_ac, &rejected_av);
    syobj_atom_array_reparse_account_for_listout((t_sy_object *)x, &accepted_ac, &accepted_av);

	if (rejected_ac > 0) 
		sy_outlet(x->n_outlet2, NULL, rejected_ac, rejected_av);
	if (accepted_ac > 0) 
		sy_outlet(x->n_outlet1, NULL, accepted_ac, accepted_av);

	sysmem_freeptr(stored_av);
	sysmem_freeptr(accepted_av);
	sysmem_freeptr(rejected_av);
}
