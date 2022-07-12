/**
	@file
	sy.iter.c
	
	@name 
	sy.iter
	
	@realname 
	sy.iter

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	Iterate on characters
	
	@description
	Outputs characters in chunks.
	
	@discussion
	
	@category
	sy

	@keywords
	iter, output, character, single, chunk
	
	@seealso
	sy.collect, sy.utoi, combine, spell, zl.iter, iter
	
	@owner
	Daniele Ghisi
*/


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h


////////////////////////// object struct
typedef struct _iter 
{
	t_sy_object		n_ob;		// the object itself (must be first)
	
	long			num_lists;
	long			chunk_size;
	long			iteration_mode;
	t_symbol		*pad;
	
	char			must_stop;
	
	long			num_proxies;
	void			**n_proxy;
	long			n_in;

	void			**n_outlet;
	long			num_outlets;
} t_iter;



///////////////////////// function prototypes
//// standard set
void *iter_new(t_symbol *s, long argc, t_atom *argv);
void iter_free(t_iter *x);
void iter_assist(t_iter *x, void *b, long m, long a, char *s);
void iter_inletinfo(t_iter *x, void *b, long a, char *t);

void iter_int(t_iter *x, t_atom_long num);
void iter_float(t_iter *x, double num);
void iter_anything(t_iter *x, t_symbol *msg, long ac, t_atom *av);
void iter_bang(t_iter *x);
	
t_max_err syobj_setattr_pad(t_iter *x, t_object *attr, long ac, t_atom *av);

	
//////////////////////// global class pointer variable
void *iter_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();

	c = class_new("sy.iter", (method)iter_new, (method)iter_free, (long)sizeof(t_iter), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)iter_assist,			"assist",		A_CANT, 0);  
	class_addmethod(c, (method)iter_inletinfo,	"inletinfo",	A_CANT,		0);

	// @method anything @digest Iterate on characters
	// @description Iterates on the whole input list, outputting the characters <m>N</m> by <m>N</m> from the outlet,
	// where <m>N</m> is the chunk size, set by the <m>size</m> attribute (by default: 1).
	// Atoms are not iterated individually, and are joined by the standard space character.
	// If an argument is given, to iterate more inputs in parallel, all the input lists are iterated at the same time,
	// and chunks are output right-to–left from the outlets (also according to <m>iterationmode</m> attribute).
	class_addmethod(c, (method)iter_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)iter_float,			"float",		A_FLOAT,	0);
	class_addmethod(c, (method)iter_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)iter_anything,		"anything",		A_GIMME,	0);

	// @method bang @digest Iterate on last received lists
	// @description Iterate on the most recently received input list.
	class_addmethod(c, (method)iter_bang,			"bang",			0);

	CLASS_ATTR_LONG(c, "size", 0, t_iter, chunk_size); 
	CLASS_ATTR_STYLE_LABEL(c,"size",0,"text","Chunk Length");
	CLASS_ATTR_BASIC(c,"size",0);
	// @description Sets the length of the chunks of characters to be output. By default it is 1 (single characters).

	CLASS_ATTR_LONG(c, "iterationmode",	0,	t_iter, iteration_mode);
	CLASS_ATTR_STYLE_LABEL(c, "iterationmode", 0, "enumindex", "Iteration Mode");
	CLASS_ATTR_ENUMINDEX(c, "iterationmode", 0, "Shortest Longest Pad");
	CLASS_ATTR_FILTER_CLIP(c, "iterationmode", 0, 2);
	// @description sets the behavior of the object when inputs of different length are iterated against each other. 
	// If set to 0, operation will stop at the end of the shortest input. If set to 1, operation will stop at the end of the 
	// longest input. If set to 2, operation will stop at the end of the longest input, and missing element from the shortest 
	// ones will be replaced by a padding character, defined by the <m>pad</m> attribute.

	CLASS_ATTR_SYM(c, "pad", 0, t_iter, pad);
	CLASS_ATTR_LABEL(c, "pad", 0, "Padding Character");
	CLASS_ATTR_ACCESSORS(c, "pad", (method)NULL, (method)syobj_setattr_pad);
	// @description Sets the padding character for the <m>iterationmode</m> 2.
	
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	iter_class = c;

	return 0;
}

t_max_err syobj_setattr_pad(t_iter *x, t_object *attr, long ac, t_atom *av){
	if (ac && av) {
		if (atom_gettype(av) == A_SYM) {
			t_symbol *s = symbol_nth_codepoint(atom_getsym(av),1);
			x->pad = s;
		}
	}
	return MAX_ERR_NONE;
}


void iter_assist(t_iter *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { 
		if (a < x->num_lists) // @in 0 @loop 1 @type symbol/list @digest List or symbol whose character should be iterated 
			sprintf(s, "Input %ld", a + 1);
		else	// @in 1 @type bang/stop @digest bang/stop to stop iteration
				// @description A <m>bang</m> or <m>stop</m> message stops the iteration.
			sprintf(s, "bang/stop: Stop");
	} else {	
		switch (a % 2) {
			case 0: sprintf(s, "Input %ld: Characters", a / 2 + 1);	break;	// @out 0 @loop 1 @type symbol @digest Current chunk
			case 1: sprintf(s, "Input %ld: Indices", a / 2 + 1);	break;	// @out 1 @loop 2 @type int/list @digest Current chunk's indices
																			// @description Along with each chunks of characters, the list of indices of such 
																			// characters is output (indices refer to the position of the characters
																			// in the input symbol or list, 1 being the first one, 2 the second one, and so one...)
		}
	}
}


void iter_inletinfo(t_iter *x, void *b, long a, char *t)
{
	if (a)
		*t = 1;
}

void iter_free(t_iter *x)
{
	long i;
	for (i = x->num_proxies; i > 0; i--)
		object_free(x->n_proxy[i]);
	sysmem_freeptr(x->n_proxy);
	sysmem_freeptr(x->n_outlet);
	syobj_obj_free((t_sy_object *)x);
}


void *iter_new(t_symbol *s, long argc, t_atom *argv)
{
	t_iter *x = NULL;
	long true_ac = attr_args_offset(argc, argv);
	long i;
    
	if ((x = (t_iter *)object_alloc(iter_class))) {

		x->pad = gensym(" ");
		x->chunk_size = 1;
		
		// @arg 0 @name count @optional 1 @type int @digest Number of parallel inputs
		// @description The number of inputs to be iterated in parallel.
		// Inlets and outlets are created accordingly.
		
  		x->num_lists = (true_ac && atom_gettype(argv) == A_LONG) ? MAX(1, atom_getlong(argv)) : 1; // one for each list (plus one standard input for ctl inlet)
		x->num_lists = MIN(x->num_lists, SY_MAX_INLETS);
		x->num_proxies = x->num_lists;

        syobj_obj_setup((t_sy_object *)x, x->num_lists);

        attr_args_process(x, true_ac, argv);

		x->n_proxy = (void **) sysmem_newptr((x->num_proxies + 1) * sizeof (void *));
		for (i = x->num_proxies; i > 0; i--)
			x->n_proxy[i] = proxy_new((t_object *) x, i, &x->n_in);
		
		x->num_outlets = MIN(2 * x->num_proxies, SY_MAX_OUTLETS);
		x->n_outlet = (void **) sysmem_newptr(x->num_outlets * sizeof (void *));
		for (i = x->num_outlets - 1; i >= 0; i--)
			x->n_outlet[i] = syout((t_object *)x);
	}
	return (x);
}

void iter_int(t_iter *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	iter_anything(x, _sym_list, 1, argv);
}

void iter_float(t_iter *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	iter_anything(x, _sym_list, 1, argv);
}

void iter_bang(t_iter *x)
{	
	iter_anything(x, _sym_bang, 0, NULL);
}

void iter_anything(t_iter *x, t_symbol *msg, long ac, t_atom *av)
{
	long	inlet = proxy_getinlet((t_object *) x);
	
	if (inlet == x->num_lists && (msg == _sym_bang || msg == _sym_stop)) {
		x->must_stop = true;
		return;
	}
		
	if (msg != _sym_bang) 
		syobj_store_content((t_sy_object *) x, msg, ac, av, inlet);
	
	if (inlet == 0) {
		long		stored_ac[SY_MAX_INLETS];
		t_atom		*stored_av[SY_MAX_INLETS];
		t_symbol	*input_sym[SY_MAX_INLETS];
		UChar32		*input_char32[SY_MAX_INLETS];
		int32_t		input_char32_size[SY_MAX_INLETS];
		long		max_input_char32_size = -1, min_input_char32_size = -1;
		UChar32		*output_cur[SY_MAX_INLETS];
		UChar32		*pad = symbol_to_uchar32_array(x->pad, NULL);
		long		cur, i, k, num_lists = x->num_lists, chunk_size = MAX(1, x->chunk_size);
		long		iterationmode = x->iteration_mode;
		
		
		// converting inputs to single symbols
		for (i = 0; i < num_lists; i++) {
			char *buf = NULL;
			long textsize = 0;
			stored_av[i] = NULL; // needed by syobj_get_store_contents in order to properly allocate memory
			stored_ac[i] = syobj_get_store_contents((t_sy_object *) x, i, SY_STORE_DONT_CLONE, &(stored_av[i]));
			atom_gettext(stored_ac[i], stored_av[i], &textsize, &buf, OBEX_UTIL_ATOM_GETTEXT_SYM_NO_QUOTE);
			input_sym[i] = gensym(buf);
			input_char32[i] = symbol_to_uchar32_array(input_sym[i], &(input_char32_size[i]));
			if (i == 0 || (input_char32_size[i] > max_input_char32_size))
				max_input_char32_size = input_char32_size[i];
			if (i == 0 || (input_char32_size[i] < min_input_char32_size))
				min_input_char32_size = input_char32_size[i];
			sysmem_freeptr(buf);
		}
		
		x->must_stop = false;
		
		UChar32 *temp = (UChar32 *)sysmem_newptr((chunk_size + 1) * sizeof(UChar32));
		t_symbol *temp_sym = NULL;
		t_atom temp_atom;
		t_atom *index_atoms = (t_atom *)sysmem_newptr(chunk_size * sizeof(t_atom));
		
		// iterating single symbols
		for (i = 0; i < num_lists; i++)
			output_cur[i] = input_char32[i];
		for (cur = 0; ; cur += chunk_size) {
			long this_chunk_size = chunk_size;
			char last_one = false;
			
			if (x->must_stop) 
				break;
			
			if (iterationmode == 0) {
				if (cur > min_input_char32_size)
					break; // iteration is over
				else if (cur + chunk_size > min_input_char32_size) {
					this_chunk_size = min_input_char32_size - cur;
					last_one = true;
				}
			} else {
				if (cur > max_input_char32_size)
					break; // iteration is over
				else if (cur + chunk_size > max_input_char32_size)  {
					this_chunk_size = max_input_char32_size - cur;
					last_one = true;
				}
			}
			
			// extracting chunks
			for (i = 0; i < num_lists; i++) {
				long this_chunk_size_modif = this_chunk_size;
				if ((cur + this_chunk_size) <= input_char32_size[i])
					sysmem_copyptr(output_cur[i], temp, this_chunk_size * sizeof(UChar32));
				else {
					long num_alloc = MAX(input_char32_size[i] - cur, 0);
					long num_non_alloc = this_chunk_size - num_alloc;
					if (num_alloc > 0)
						sysmem_copyptr(output_cur[i], temp, num_alloc * sizeof(UChar32));
					if (iterationmode == 2) {  // padding
						for (k = 0; k < num_non_alloc; k++)
							temp[num_alloc + k] = pad[0] ? pad[0] : ' ';
					} else { // don't pad, just trim
						this_chunk_size_modif = num_alloc;
					}
				}
				
				temp[this_chunk_size_modif] = 0;
				temp_sym = symbol_from_uchar32_array(temp, this_chunk_size_modif);
				atom_setsym(&temp_atom, temp_sym);
				
				for (k = cur; k < cur + this_chunk_size_modif; k++) 
					atom_setlong(index_atoms + (k - cur), k + 1);
				
				if (this_chunk_size_modif > 0) {
					sy_outlet(x->n_outlet[2*i + 1], NULL, this_chunk_size_modif, index_atoms);
					sy_outlet(x->n_outlet[2*i], NULL, 1, &temp_atom);
				}
			}
			
			if (last_one)
				break;
			
			for (i = 0; i < num_lists; i++) 
				for (k = 0; k < chunk_size; k++)
					if (*(output_cur[i]))
						output_cur[i]++;
		}
		
		sysmem_freeptr(temp);
		sysmem_freeptr(index_atoms);
	}
}
