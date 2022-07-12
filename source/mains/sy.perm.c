/**
 @file
 sy.perm.c
 
 @name 
 sy.perm
 
 @realname 
 sy.perm
 
 @type
 object
 
 @module
 sy
 
 @author
 Daniele Ghisi
 
 @digest 
 Find character permutations
 
 @description
 Find all character permutations of input symbols.
 
 @discussion
 It takes all the input and convert it into a single symbol (if it was not a symbol already)
 
 @category
 sy
 
 @keywords
 perm, permute, characters
 
 @seealso
 sy.scramble
 
 @owner
 Daniele Ghisi
 */


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h


////////////////////////// object struct
typedef struct _perm 
{
	t_sy_object		n_ob;		// the object itself (must be first)
	char			only_unique; // only output unique permutations
	char			autoiter;
	void			*n_outlet;
} t_perm;



///////////////////////// function ppermotypes
//// standard set
void *perm_new(t_symbol *s, long argc, t_atom *argv);
void perm_free(t_perm *x);
void perm_assist(t_perm *x, void *b, long m, long a, char *s);

void perm_int(t_perm *x, t_atom_long num);
void perm_float(t_perm *x, double num);
void perm_anything(t_perm *x, t_symbol *msg, long ac, t_atom *av);
void perm_bang(t_perm *x);



//////////////////////// global class pointer variable
void *perm_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();
	
	c = class_new("sy.perm", (method)perm_new, (method)perm_free, (long)sizeof(t_perm), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)perm_assist,			"assist",		A_CANT, 0);  
	
	// @method anything @digest Compute and output character permutations
	// @description Any output is converted to a single symbol, and all the character permutations of such symbol are the output, 
	// either one by one or in list form (depending on the <m>autoiter</m> attribute), from the outlet.
	class_addmethod(c, (method)perm_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)perm_float,		"float",		A_FLOAT,	0);
	class_addmethod(c, (method)perm_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)perm_anything,		"anything",		A_GIMME,	0);
	
	// @method bang @digest Output permutations
	// @description Output the permations computed on the most recently received input symbols.
	class_addmethod(c, (method)perm_bang,			"bang",			0);
	
	CLASS_ATTR_CHAR(c, "unique", 0, t_perm, only_unique); 
	CLASS_ATTR_STYLE_LABEL(c,"unique",0,"onoff","Strip Duplicates");
	CLASS_ATTR_BASIC(c,"unique",0);
	// @description Toggles the ability to only output repeated permutations once. Defaults to 1.

	CLASS_ATTR_CHAR(c, "autoiter", 0, t_perm, autoiter); 
	CLASS_ATTR_STYLE_LABEL(c,"autoiter",0,"onoff","Iterate Output Automatically");
	CLASS_ATTR_BASIC(c,"autoiter",0);
	// @description Toggles the ability to spit permutations one by one, instead of listing them. Defaults to 1.
	
    syobj_class_add_listin_attr(c);

	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	perm_class = c;
	
	return 0;
}


void perm_assist(t_perm *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type anything @digest Original symbol
		sprintf(s, "anything: Original symbol"); // @description A list will be converted into a single symbol
	} 
	else {	// @out 0 @type anything @digest All the character permutations 
		sprintf(s, "anything: All permutations");
	}
}

void perm_free(t_perm *x)
{
	syobj_obj_free((t_sy_object *)x);
}


void *perm_new(t_symbol *s, long argc, t_atom *argv)
{
	t_perm *x = NULL;
    
	if ((x = (t_perm *)object_alloc(perm_class))) {
		x->only_unique = true;
		x->autoiter = true;
		
        syobj_obj_setup((t_sy_object *)x, 1);

        attr_args_process(x, argc, argv);
		
		x->n_outlet = syout((t_object *)x);
	}
	return (x);
}

void perm_int(t_perm *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	perm_anything(x, _sym_list, 1, argv);
}

void perm_float(t_perm *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	perm_anything(x, _sym_list, 1, argv);
}

void perm_bang(t_perm *x)
{	
	perm_anything(x, _sym_bang, 0, NULL);
}


void perm_anything(t_perm *x, t_symbol *msg, long ac, t_atom *av)
{
	long	i, stored_ac = 0, out_ac = 0;
	t_atom	*stored_av = NULL, *out_av = NULL;
	t_symbol **result = NULL;
	char only_unique = x->only_unique;
	char autoiter = x->autoiter;
    long c;
    
	if (msg != _sym_bang) 
		syobj_store_content((t_sy_object *) x, msg, ac, av, 0);
	
	stored_ac = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE_ALL_SYMBOLS_AND_ACCOUNT_FOR_LIST_MODE, &stored_av);
    for (c = 0; c < stored_ac; c++) {
        if (atom_gettype(stored_av + c) == A_SYM) {
            t_symbol *this_sym = atom_getsym(stored_av + c);
            result = NULL;
            if (!symbol_permute(this_sym, &result, &out_ac, only_unique)) {
                if (out_ac > 0) {
                    out_av = (t_atom *)sysmem_newptr(out_ac * sizeof(t_atom));
                    for (i = 0; i < out_ac; i++)
                        atom_setsym(out_av + i, result[i]);

                    if (autoiter) {
                        for (i = 0; i < out_ac; i++)
                            sy_outlet(x->n_outlet, NULL, 1, out_av + i);
                    } else
                        sy_outlet(x->n_outlet, NULL, out_ac, out_av);
                }
                sysmem_freeptr(result);
            } else  {
                object_error((t_object *)x, "Too many characters to compute all permutations.");
                object_error((t_object *)x, "    You might want to use sy.scramble instead.");
            }
            
        }
    }
	
	sysmem_freeptr(stored_av);
	sysmem_freeptr(out_av);
}
