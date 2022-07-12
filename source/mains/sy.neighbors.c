/**
	@file
	sy.neighbors.c
	
	@name 
	sy.neighbors
	
	@realname 
	sy.neighbors

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	neighbors characters
	
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
 #include <stdlib.h>

////////////////////////// object struct
typedef struct _neighbors 
{
	t_sy_object		n_ob;		// the object itself (must be first)
	
    char            case_insensitive;
    char            re_mode;
    
    long            num_before;
    long            num_after;
    
	long			n_in;   // space for the inlet number used by all the proxies
    void			*n_proxy1;
	void			*n_outlet;
} t_neighbors;



///////////////////////// function prototypes
//// standard set
void *neighbors_new(t_symbol *s, long argc, t_atom *argv);
void neighbors_free(t_neighbors *x);
void neighbors_assist(t_neighbors *x, void *b, long m, long a, char *s);
void neighbors_inletinfo(t_neighbors *x, void *b, long a, char *t);

void neighbors_int(t_neighbors *x, t_atom_long num);
void neighbors_float(t_neighbors *x, double num);
void neighbors_anything(t_neighbors *x, t_symbol *msg, long ac, t_atom *av);
void neighbors_bang(t_neighbors *x);
	

	
//////////////////////// global class pointer variable
void *neighbors_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();

	c = class_new("sy.neighbors", (method)neighbors_new, (method)neighbors_free, (long)sizeof(t_neighbors), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)neighbors_assist,			"assist",		A_CANT, 0);  
	class_addmethod(c, (method)neighbors_inletinfo,	"inletinfo",	A_CANT,		0);

	// @method anything @digest Return characters
	// @description Anything in the left inlet will trigger the output of a list containing the characters picked from the introduced elements,
    // (one character corresponding to each introduced index, see <m>list</m> method, except for the range syntax).
    // By default characters are joined in symbols; see <m>separate</m> attribute to output separate characters.
	// @copy SY_DOC_INDICES
	class_addmethod(c, (method)neighbors_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)neighbors_float,			"float",		A_FLOAT,	0);

	// @method list @digest Set indices
	// @description A list in the right inlet is the list of indices to be picked.
	// @copy SY_DOC_INDICES
	class_addmethod(c, (method)neighbors_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)neighbors_anything,		"anything",		A_GIMME,	0);


	// @method bang @digest Perform last operation
	// @description Returns the characters from the most recently received input symbol.
	class_addmethod(c, (method)neighbors_bang,			"bang",			0);

//    syobj_class_add_listin_attr(c);
//	syobj_class_add_numout_attr(c);
//    syobj_class_add_listout_attr(c);
	
    
    CLASS_ATTR_CHAR(c, "ignorecase", 0, t_neighbors, case_insensitive);
    CLASS_ATTR_STYLE_LABEL(c,"ignorecase",0,"onoff","Case Insensitive Search");
    CLASS_ATTR_BASIC(c,"ignorecase",0);
    // @description Toggles the ability to ignore case in search.
    
    CLASS_ATTR_CHAR(c, "re", 0, t_neighbors, re_mode);
    CLASS_ATTR_STYLE_LABEL(c,"re",0,"onoff","Use Regular Expressions");
    CLASS_ATTR_BASIC(c,"re",0);
    // @description Toggles the ability to use regular expressions for searching (default: off).

    CLASS_ATTR_LONG(c, "before", 0, t_neighbors, num_before);
    CLASS_ATTR_STYLE_LABEL(c,"before",0,"text","Words Before Match");
    CLASS_ATTR_BASIC(c,"before",0);
    // @description Sets the number of words, before the matched pattern, to be output.

    CLASS_ATTR_LONG(c, "after", 0, t_neighbors, num_after);
    CLASS_ATTR_STYLE_LABEL(c,"after",0,"text","Words After Match");
    CLASS_ATTR_BASIC(c,"after",0);
    // @description Sets the number of words, after the matched pattern, to be output.

    
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	neighbors_class = c;

	return 0;
}


void neighbors_assist(t_neighbors *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type symbol @digest Pattern to be matched
        if (a == 0)
            sprintf(s, "symbol: Pattern to be matched");
        else  // @in 1 @type symbol @digest Directory containing the text files
            sprintf(s, "symbol: Directory containing the text file(s)");
	}
	else {	// @in 0 @type list @digest Matches
		sprintf(s, "Matches");
	}
}

void neighbors_inletinfo(t_neighbors *x, void *b, long a, char *t)
{
	if (a)
		*t = 1;
}

void neighbors_free(t_neighbors *x)
{
	object_free(x->n_proxy1);
	syobj_obj_free((t_sy_object *)x);
}


void *neighbors_new(t_symbol *s, long argc, t_atom *argv)
{
	t_neighbors *x = NULL;
	long true_ac = attr_args_offset(argc, argv);
    
	if ((x = (t_neighbors *)object_alloc(neighbors_class))) {
		
        x->num_before = 5;
        x->num_after = 5;
        
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

void neighbors_int(t_neighbors *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	neighbors_anything(x, _sym_list, 1, argv);
}

void neighbors_float(t_neighbors *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	neighbors_anything(x, _sym_list, 1, argv);
}

void neighbors_bang(t_neighbors *x)
{	
	neighbors_anything(x, _sym_bang, 0, NULL);
}



void neighbors_anything(t_neighbors *x, t_symbol *msg, long ac, t_atom *av)
{
	long	stored_ac1, stored_ac2;
	t_atom	*stored_av1 = NULL, *stored_av2 = NULL;
	long inlet = proxy_getinlet((t_object *) x);
	
	if (msg != _sym_bang) 
		syobj_store_content((t_sy_object *) x, msg, ac, av, inlet);
	
	if (inlet == 0) {
		stored_ac1 = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_DONT_CLONE, &stored_av1);
        t_symbol *path = syobj_get_store_contents_as_single_symbol((t_sy_object *) x, 1);
        
        if (!path) {
            object_error((t_object *)x, "No search path defined!");
            return;
        }
        
        // Retrieving search text
        char *text = NULL;
        long size = 0;
        atom_gettext(stored_ac1, stored_av1, &size, &text, OBEX_UTIL_ATOM_GETTEXT_SYM_NO_QUOTE);
        
        // Building shell command
        char system_command[2048];
        snprintf(system_command, 2047, "> /tmp/noti_tmp.txt && LC_ALL=C grep -B 1 -A 1 -hrw%s '%s' -e '%s' %s >> /tmp/noti_tmp.txt", x->case_insensitive ? "i" : "", path->s_name, text, x->re_mode ? "" : "--fixed-strings");
        object_post((t_object *)x, "Running %s...", system_command);
        system(system_command);
        object_post((t_object *)x, "Done!");
        
        
        /* assumes no word exceeds length of 2047 */

        // Splitting target string into tokens
        char target_words[32][2048];
        long num_target_words = 0;
        long w = 0;
        char *pch;
        pch = strtok(text," ");
        while (pch != NULL && w < 32)
        {
            snprintf_zero(target_words[w], 2048, "%s", pch);
            num_target_words++;
            w++;
            pch = strtok(NULL, " ");
        }
        
        
        
        //
        FILE *fp = fopen("/tmp/noti_tmp.txt", "r");
        char words[1024][2048];
        char single_word[2048];
        long count_separators = 0;
        long match_idx = -1;
        t_atom out_av[2048];
        long out_ac = 0;
        
        w = 0;
        while (fscanf(fp, " %2047s", single_word) == 1) {
            
            if (strcmp(single_word, "--") == 0)
                count_separators++;
            else
                count_separators = 0;
            
            if (count_separators == 2) { // new word
                if (match_idx >= 0) {
                    // output words
                    out_ac = 0;
                    for (long i = MAX(0, match_idx - x->num_before); i < match_idx + num_target_words + x->num_after && i < w; i++) {
                        atom_setsym(out_av + out_ac, gensym(words[i]));
                        out_ac++;
                    }
                    
                    syobj_atom_array_reparse_account_for_numout((t_sy_object *)x, out_ac, out_av);
                    sy_outlet(x->n_outlet, NULL, out_ac, out_av);
                }
                
                w = 0;
                match_idx = -1;
            }
            
            if (w < 1024) {
                
                snprintf_zero(words[w], 2048, "%s", single_word);
                
                // checking match;
                char is_match = true;
                long w_temp = w;
                for (long i = num_target_words - 1; i >= 0; i--, w_temp--) {
                    long len_target = strlen(target_words[i]);
                    if (w_temp < 0) {
                        is_match = false;
                        break;
                    } else if (x->case_insensitive) {
                        if (strncasecmp(words[w_temp], target_words[i], len_target) != 0 || isalnum(words[w_temp][len_target])) {
                            is_match = false;
                            break;
                        }
                    } else {
                        if (strncmp(words[w_temp], target_words[i], len_target) != 0 || isalnum(words[w_temp][len_target])) {
                            is_match = false;
                            break;
                        }
                    }
                }
                
                if (is_match)
                    match_idx = w - num_target_words + 1;
                
                w++;
            }
            
//            object_post((t_object *)x, single_word);
        }
        
        fclose(fp);
        
        
        if (text)
            sysmem_freeptr(text);
	}
}
