/**
	@file
	sy.nth.c
	
	@name 
	sy.nth
	
	@realname 
	sy.nth

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	Return characters by indices
	
	@description
	Returns one or more specific characters, based on their indices.
	
	@discussion
	Of course, the function returns whole UTF-8 codepoints, not code units.
	
	@category
	sy

	@keywords
	index, return, character, codepoint, address, position
	
	@seealso
	sy.filterempty, sy.slice
	
	@owner
	Daniele Ghisi
*/


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h
#define SY_NTH_MAX_INDICES 256

////////////////////////// object struct
typedef struct _nth 
{
	t_sy_object		n_ob;		// the object itself (must be first)

	char			separate;
	
	long			n_in;   // space for the inlet number used by all the proxies
    void			*n_proxy1;
	void			*n_outlet;
} t_nth;



///////////////////////// function prototypes
//// standard set
void *nth_new(t_symbol *s, long argc, t_atom *argv);
void nth_free(t_nth *x);
void nth_assist(t_nth *x, void *b, long m, long a, char *s);
void nth_inletinfo(t_nth *x, void *b, long a, char *t);

void nth_int(t_nth *x, t_atom_long num);
void nth_float(t_nth *x, double num);
void nth_anything(t_nth *x, t_symbol *msg, long ac, t_atom *av);
void nth_bang(t_nth *x);
	

	
//////////////////////// global class pointer variable
void *nth_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();

	c = class_new("sy.nth", (method)nth_new, (method)nth_free, (long)sizeof(t_nth), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)nth_assist,			"assist",		A_CANT, 0);  
	class_addmethod(c, (method)nth_inletinfo,	"inletinfo",	A_CANT,		0);

	// @method anything @digest Return characters
	// @description Anything in the left inlet will trigger the output of a list containing the characters picked from the introduced elements,
    // (one character corresponding to each introduced index, see <m>list</m> method, except for the range syntax).
    // By default characters are joined in symbols; see <m>separate</m> attribute to output separate characters.
	// @copy SY_DOC_INDICES
	class_addmethod(c, (method)nth_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)nth_float,			"float",		A_FLOAT,	0);

	// @method list @digest Set indices
	// @description A list in the right inlet is the list of indices to be picked.
	// @copy SY_DOC_INDICES
	class_addmethod(c, (method)nth_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)nth_anything,		"anything",		A_GIMME,	0);


	// @method bang @digest Perform last operation
	// @description Returns the characters from the most recently received input symbol.
	class_addmethod(c, (method)nth_bang,			"bang",			0);

    syobj_class_add_listin_attr(c);
	syobj_class_add_numout_attr(c);
    syobj_class_add_listout_attr(c);
	
	CLASS_ATTR_LONG(c, "separate", 0, t_nth, separate); 
	CLASS_ATTR_STYLE_LABEL(c,"separate",0,"enumindex","Separate Output Characters");
    CLASS_ATTR_ENUMINDEX(c,"separate", 0, "Don't Keep Ranges Separate All");
	CLASS_ATTR_BASIC(c,"separate",0);
	// @description Toggles the ability to separate the output characters as different atoms. Defaults to 0 (Don't).
    // "Keep Ranges" (1) will separate characters, but keep the range syntax (see <m>anything</m> method).
    // "Separate All" (2) will separate all characters, including the ones in range syntax

	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	nth_class = c;

	return 0;
}


void nth_assist(t_nth *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type symbol @digest Incoming symbol
		sprintf(s, "Incoming symbol");
	} 
	else {	// @in 0 @type list @digest List of characters at indices
		sprintf(s, "List of characters at indices"); 			
	}
}

void nth_inletinfo(t_nth *x, void *b, long a, char *t)
{
	if (a)
		*t = 1;
}

void nth_free(t_nth *x)
{
	object_free(x->n_proxy1);
	syobj_obj_free((t_sy_object *)x);
}


void *nth_new(t_symbol *s, long argc, t_atom *argv)
{
	t_nth *x = NULL;
	long true_ac = attr_args_offset(argc, argv);
    
	if ((x = (t_nth *)object_alloc(nth_class))) {
		x->separate = 0;
		
		syobj_obj_setup((t_sy_object *)x, 2);

		// @arg 0 @name indices @optional 1 @type list @digest Indices
		// @description The list of indices at which characters should be retrived.
		// @copy SY_DOC_INDICES
		syobj_store_content((t_sy_object *) x, NULL, true_ac, argv, 1);
			

        attr_args_process(x, argc, argv);
		
		x->n_proxy1 = proxy_new((t_object *) x, 1, &x->n_in);
		x->n_outlet = syout((t_object *)x);
	}
	return (x);
}

void nth_int(t_nth *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	nth_anything(x, _sym_list, 1, argv);
}

void nth_float(t_nth *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	nth_anything(x, _sym_list, 1, argv);
}

void nth_bang(t_nth *x)
{	
	nth_anything(x, _sym_bang, 0, NULL);
}



void nth_anything(t_nth *x, t_symbol *msg, long ac, t_atom *av)
{
	long	stored_ac1, stored_ac2, out_ac = 0, i;
	t_atom	*stored_av1 = NULL, *stored_av2 = NULL;
	t_atom	*out_av = NULL;
	long inlet = proxy_getinlet((t_object *) x);
	char	separate = x->separate;
	
	if (msg != _sym_bang) 
		syobj_store_content((t_sy_object *) x, msg, ac, av, inlet);
	
	if (inlet == 0) {
		stored_ac1 = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE_ALL_SYMBOLS_AND_ACCOUNT_FOR_LIST_MODE, &stored_av1);
		stored_ac2 = syobj_get_store_contents((t_sy_object *) x, 1, SY_STORE_DONT_CLONE, &stored_av2);
		
        t_atom *curr; long curr_count;
		if (stored_ac1 > 0 && stored_ac2 > 0) {
            
            // estimating maximum total number of atoms needed
            long num_characters_cap = 0;
            long count_open_parenthesis = 0;
            for (i = 0; i < stored_ac2; i++)
                if (atom_gettype(stored_av2 + i) == A_SYM && atom_getsym(stored_av2 + i) == gensym("("))
                    count_open_parenthesis++;
            for (curr = stored_av1, curr_count = 0; curr_count < stored_ac1; curr_count++, curr++) {
                if (atom_gettype(stored_av1) == A_SYM) {
                    t_symbol *sym = atom_getsym(stored_av1);
                    long len = symbol_get_num_codepoints_fast(sym);
                    num_characters_cap += stored_ac2 + 1 + len * count_open_parenthesis;
                }
            }
            
            t_atom *cur_out_av;
            long num_atoms_cap = stored_ac1;
            if (separate == 1) {
                num_atoms_cap = stored_ac2 * stored_ac1;
            } else if (separate == 2) {
                num_atoms_cap = num_characters_cap;
            }
            
            num_atoms_cap++;
            num_characters_cap++;
            
            UChar32 *buf = (UChar32 *)sysmem_newptr(num_characters_cap * sizeof(UChar32)); // upper bound, most likely excessive
            out_av = (t_atom *)sysmem_newptr(num_atoms_cap * sizeof(t_atom)); // surely enough
            out_ac = 0;
            long buf_cur = 0;
            cur_out_av = out_av;

            for (curr = stored_av1, curr_count = 0; curr_count < stored_ac1; curr_count++, curr++) {
                buf_cur = 0;
                if (atom_gettype(curr) == A_SYM) {
                    t_symbol *sym = atom_getsym(curr);
                    for (i = 0; i < stored_ac2; ) {
                        char type = atom_gettype(stored_av2 + i);
                        if (type == A_LONG) {
                            long idx = atom_getlong(stored_av2 + i);
                            if (idx == 0) {
                                object_warn((t_object *)x, "Warning: zero index ignored.");
                            } else {
                                if (separate > 0) {
                                    atom_setsym(cur_out_av++, symbol_nth_codepoint(sym, idx));
                                    out_ac++;
                                } else
                                    buf[buf_cur++] = symbol_nth_codepoint_as_uchar32(sym, idx);
                            }
                            i++;
                            
                        } else if (type == A_SYM && atom_getsym(stored_av2 + i) == gensym("(")) {
                            // range syntax
                            i++;
                            
                            UChar32 *temp_buf = NULL;
                            long temp_buf_cur = 0;
                            if (separate == 1)
                                temp_buf = (UChar32 *)sysmem_newptr((symbol_get_num_codepoints_fast(sym) + 1) * sizeof(UChar32)); // upper bound

                            while (i < stored_ac2 && atom_gettype(stored_av2 + i) != A_LONG)
                                i++;
                            if (i < stored_ac2) {
                                long idx_start = atom_getlong(stored_av2 + i);
                                i++;
                                while (i < stored_ac2 && atom_gettype(stored_av2 + i) != A_LONG)
                                    i++;
                                if (i < stored_ac2) {
                                    long idx_end = atom_getlong(stored_av2 + i);
                                    long len = symbol_get_num_codepoints(sym, true);
                                    if (idx_start < 0)
                                        idx_start = len + idx_start + 1;
                                    if (idx_end < 0)
                                        idx_end = len + idx_end + 1;
                                    if (idx_end < idx_start) {
                                        long temp = idx_end;
                                        idx_end = idx_start;
                                        idx_start = temp;
                                    }
                                    
                                    long j;
                                    for (j = idx_start; j <= idx_end; j++) {
                                        if (j != 0) {
                                            if (separate == 2) {
                                                atom_setsym(cur_out_av++, symbol_nth_codepoint(sym, j));
                                                out_ac++;
                                            } else if (separate == 1) {
                                                temp_buf[temp_buf_cur++] = symbol_nth_codepoint_as_uchar32(sym, j);
                                            } else
                                                buf[buf_cur++] = symbol_nth_codepoint_as_uchar32(sym, j);
                                        } else
                                            object_warn((t_object *)x, "Warning: zero index ignored.");
                                    }
                                    i++;
                                    while (i < stored_ac2 && !(atom_gettype(stored_av2 + i) == A_SYM && atom_getsym(stored_av2 + i) == gensym(")")))
                                        i++;
                                    i++;
                                }
                            }
                            
                            if (temp_buf) {
                                atom_setsym(cur_out_av++, symbol_from_uchar32_array(temp_buf, temp_buf_cur));
                                out_ac++;
                                sysmem_freeptr(temp_buf);
                            }
                            
                        } else {
                            object_warn((t_object *)x, "Warning: non-integer index ignored.");
                            i++;
                        }
                    }
                    
                    
                    if (separate == 0) {
                        buf[buf_cur] = 0;
                        atom_setsym(cur_out_av++, symbol_from_uchar32_array(buf, buf_cur));
                        out_ac++;
                    }
                    
                } else {
                    // not a symbol... we copy it
                    *cur_out_av = *curr;
                    cur_out_av++;
                    out_ac++;
                }
            }
			
            sysmem_freeptr(buf);

            syobj_atom_array_reparse_account_for_numout((t_sy_object *)x, out_ac, out_av);
            syobj_atom_array_reparse_account_for_listout((t_sy_object *)x, &out_ac, &out_av);

			if (out_ac > 0)
				sy_outlet(x->n_outlet, NULL, out_ac, out_av);

			sysmem_freeptr(out_av);
		}
		sysmem_freeptr(stored_av1);
	}
}
