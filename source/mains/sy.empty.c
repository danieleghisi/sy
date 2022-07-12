/**
	@file
	sy.empty.c
	
	@name 
	sy.empty
	
	@realname 
	sy.empty

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	Empty symbol
	
	@description
	Outputs an empty symbol
	
	@discussion
	
	@category
	sy

	@keywords
	empty, null, none
	
	@seealso
	sy.subs
	
	@owner
	Daniele Ghisi
*/


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h


////////////////////////// object struct
typedef struct _empty 
{
	t_sy_object		n_ob;		// the object itself (must be first)

	void			*n_outlet;
} t_empty;



///////////////////////// function prototypes
//// standard set
void *empty_new(t_symbol *s, long argc, t_atom *argv);
void empty_free(t_empty *x);
void empty_assist(t_empty *x, void *b, long m, long a, char *s);

void empty_bang(t_empty *x);
	

	
//////////////////////// global class pointer variable
void *empty_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();

	c = class_new("sy.empty", (method)empty_new, (method)empty_free, (long)sizeof(t_empty), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)empty_assist,			"assist",		A_CANT, 0);  

	// @method bang @digest Output empty symbol
	// @description Outputs an empty symbol.
	class_addmethod(c, (method)empty_bang,			"bang",			0);

	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	empty_class = c;

	return 0;
}


void empty_assist(t_empty *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type bang @digest bang to output empty symbol
        sprintf(s, "bang to output empty symbol");
	}
	else {	// @out 0 @type anything @digest Empty symbol
		sprintf(s, "Empty symbol");
	}
}

void empty_free(t_empty *x)
{
	syobj_obj_free((t_sy_object *)x);
}


void *empty_new(t_symbol *s, long argc, t_atom *argv)
{
	t_empty *x = NULL;
    
	if ((x = (t_empty *)object_alloc(empty_class))) {
		
		syobj_obj_setup((t_sy_object *)x, 0);

        attr_args_process(x, argc, argv);
		
		x->n_outlet = syout((t_object *)x);
	}
	return (x);
}

void empty_bang(t_empty *x)
{
    t_atom av;
    atom_setsym(&av, gensym(""));
    sy_outlet(x->n_outlet, NULL, 1, &av);
}
