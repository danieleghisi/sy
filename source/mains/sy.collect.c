/**
	@file
	sy.collect.c
	
	@name 
	sy.collect
	
	@realname 
	sy.collect

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	Collect characters
	
	@description
	Appends input characters together.
 
	@discussion
	
	@category
	sy

	@keywords
	collect, append, join, merge, connect, combine
	
	@seealso
	sy.iter, zl.group
	
	@owner
	Daniele Ghisi
*/


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h
#define SY_COLLECT_ALLOCATION_STEP	1024

////////////////////////// object struct
typedef struct _collect 
{
	t_sy_object		n_ob;		// the object itself (must be first)
	
	long			num_lists;
	char			autoclear;
	
	char			*collecting[SY_MAX_INLETS];
	long			collection_size[SY_MAX_INLETS];
	long			allocated_size[SY_MAX_INLETS];
	
	long			num_proxies;
	void			**n_proxy;
	long			n_in;

	void			**n_outlet;
	long			num_outlets;
} t_collect;



///////////////////////// function prototypes
//// standard set
void *collect_new(t_symbol *s, long argc, t_atom *argv);
void collect_free(t_collect *x);
void collect_assist(t_collect *x, void *b, long m, long a, char *s);
void collect_inletinfo(t_collect *x, void *b, long a, char *t);

void collect_int(t_collect *x, t_atom_long num);
void collect_float(t_collect *x, double num);
void collect_anything(t_collect *x, t_symbol *msg, long ac, t_atom *av);
void collect_bang(t_collect *x);
	

	
//////////////////////// global class pointer variable
void *collect_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();

	c = class_new("sy.collect", (method)collect_new, (method)collect_free, (long)sizeof(t_collect), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)collect_assist,			"assist",		A_CANT, 0);  
	class_addmethod(c, (method)collect_inletinfo,	"inletinfo",	A_CANT,		0);

	// @method anything @digest Collect characters
	// @description Any message received in the <m>N+1</m>-th inlet will be collected in the <m>N</m>-th collector.
	class_addmethod(c, (method)collect_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)collect_float,			"float",		A_FLOAT,	0);
	class_addmethod(c, (method)collect_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)collect_anything,		"anything",		A_GIMME,	0);

	// @method bang @digest Output collections
	// @description Outputs each collection from the corresponding outlet.
	class_addmethod(c, (method)collect_bang,			"bang",			0);

    syobj_class_add_listout_attr(c);

    CLASS_ATTR_CHAR(c, "autoclear", 0, t_collect, autoclear);
	CLASS_ATTR_STYLE_LABEL(c,"autoclear",0,"onoff","Auto Clear");
	CLASS_ATTR_BASIC(c,"autoclear",0);
	// @description Clears the collections automatically after a <m>bang</m> is received.

	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	collect_class = c;

	return 0;
}


void collect_assist(t_collect *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { 
		if (a == 0) // @in 0 @type bang @digest Output all the collections 
			sprintf(s, "bang: Output Collections");
		else // @in 1 @loop 1 @type symbol/list @digest List or symbol whose character should be collectated 
			sprintf(s, "anything: Input %ld", a);
	} else {	
		sprintf(s, "symbol: Output %ld", a + 1);	// @out 0 @loop 1 @type symbol @digest Collected characters
	}
}


void collect_inletinfo(t_collect *x, void *b, long a, char *t)
{
	if (a)
		*t = 1;
}

void collect_free(t_collect *x)
{
	long i;
	for (i = 0; i < x->num_lists; i++)
		sysmem_freeptr(x->collecting[i]);
	for (i = x->num_proxies; i > 0; i--)
		object_free(x->n_proxy[i]);
	syobj_obj_free((t_sy_object *)x);
}


void *collect_new(t_symbol *s, long argc, t_atom *argv)
{
	t_collect *x = NULL;
	long true_ac = attr_args_offset(argc, argv);
	long i;
    
	if ((x = (t_collect *)object_alloc(collect_class))) {

		x->autoclear = 1;
		
		// @arg 0 @name count @optional 1 @type int @digest Number of collections
		// @description The number of collections to be performed in parallel.
		// Inlets and outlets are created accordingly.
		
  		x->num_lists = (true_ac && atom_gettype(argv) == A_LONG) ? MAX(1, atom_getlong(argv)) : 1; // one for each list (plus one standard input for ctl inlet)
		x->num_proxies = x->num_lists = MIN(x->num_lists, SY_MAX_INLETS);
		
        syobj_obj_setup((t_sy_object *)x, x->num_proxies + 1);

        attr_args_process(x, true_ac, argv);

		x->n_proxy = (void **) sysmem_newptr((x->num_proxies + 1) * sizeof (void *));
		for (i = x->num_proxies; i > 0; i--)
			x->n_proxy[i] = proxy_new((t_object *) x, i, &x->n_in);
		
		x->num_outlets = MIN(x->num_lists, SY_MAX_OUTLETS);
		x->n_outlet = (void **) sysmem_newptr(x->num_outlets * sizeof (void *));
		for (i = x->num_outlets - 1; i >= 0; i--)
			x->n_outlet[i] = syout((t_object *)x);

		for (i = 0; i < x->num_lists; i++) {
			x->collecting[i] = (char *)sysmem_newptr(SY_COLLECT_ALLOCATION_STEP * sizeof(char));
			x->allocated_size[i] = SY_COLLECT_ALLOCATION_STEP;
			x->collecting[i][0] = 0;
			x->collection_size[i] = 0;
		} 
	}
	return (x);
}

void collect_int(t_collect *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	collect_anything(x, _sym_list, 1, argv);
}

void collect_float(t_collect *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	collect_anything(x, _sym_list, 1, argv);
}

void collect_bang(t_collect *x)
{	
	collect_anything(x, _sym_bang, 0, NULL);
}

void collect_anything(t_collect *x, t_symbol *msg, long ac, t_atom *av)
{
	long i, inlet = proxy_getinlet((t_object *) x);
	
	if (msg == _sym_bang && inlet == 0) {
		// output data!
		for (i = x->num_lists - 1; i >= 0; i--) {
			t_atom *out_av = (t_atom *)sysmem_newptr(1 * sizeof(t_atom));
            long out_ac = 1;
            systhread_mutex_lock(x->n_ob.l_mutex);
			atom_setsym(out_av, gensym(x->collecting[i]));
			systhread_mutex_unlock(x->n_ob.l_mutex);
            syobj_atom_array_reparse_account_for_listout((t_sy_object *)x, &out_ac, &out_av);
			sy_outlet(x->n_outlet[i], NULL, out_ac, out_av);
            sysmem_freeptr(out_av);
		}
		
		systhread_mutex_lock(x->n_ob.l_mutex);
		if (x->autoclear) {
			for (i = x->num_lists; i >= 0; i--) {
				sysmem_freeptr(x->collecting[i]);
				x->collecting[i] = (char *)sysmem_newptr(SY_COLLECT_ALLOCATION_STEP * sizeof(char));
				x->allocated_size[i] = SY_COLLECT_ALLOCATION_STEP;
				x->collecting[i][0] = 0;
				x->collection_size[i] = 0;
			}
		}
		systhread_mutex_unlock(x->n_ob.l_mutex);
	} else if (inlet > 0) {
		char *buf = NULL;
		long textsize = 0;
		long work_ac = 0;
		t_atom *work_av = NULL;
		
		syobj_store_content((t_sy_object *)x, msg, ac, av, inlet);
		work_ac = syobj_get_store_contents((t_sy_object *)x, inlet, SY_STORE_DONT_CLONE, &work_av);
		atom_gettext(work_ac, work_av, &textsize, &buf, OBEX_UTIL_ATOM_GETTEXT_SYM_NO_QUOTE);
		textsize = strlen(buf); // atom_gettext's textsize return includes in the counting the final zero. We don't want that.
		i = inlet - 1;

		systhread_mutex_lock(x->n_ob.l_mutex);
		while (x->collection_size[i] + textsize + 1 > x->allocated_size[i]) { // + 1 is for the terminating null char
			x->allocated_size[i] += SY_COLLECT_ALLOCATION_STEP;
			x->collecting[i] = (char *) sysmem_resizeptr(x->collecting[i], x->allocated_size[i] * sizeof(char));
		}
		sysmem_copyptr(buf, x->collecting[i] + x->collection_size[i], textsize);
		x->collecting[i][x->collection_size[i] + textsize] = 0;
		x->collection_size[i] += textsize;
		systhread_mutex_unlock(x->n_ob.l_mutex);

		sysmem_freeptr(buf);
	}
}
