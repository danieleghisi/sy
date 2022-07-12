/**
	@file
	sy.route.c
	
	@name 
	sy.route
	
	@realname 
	sy.route

	@type
	object
	
	@module
	sy

	@author
	Daniele Ghisi
	
	@digest 
	Route symbols according to starting or ending characters
	
	@description
	Routes the incoming symbols according to their starting or ending characters.
	
	@discussion
	
	@category
	sy

	@keywords
	route, key, select, start, character
	
	@seealso
	route, routepass, sy.find, sy.compare
	
	@owner
	Daniele Ghisi
*/


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h

////////////////////////// object struct
typedef struct _route 
{
	t_sy_object		n_ob;		// the object itself (must be first)

	t_symbol		*routers[SY_MAX_INLETS];		// split point
	long			num_routers;
	
	char			keep;
    char			use_end;
	char			multiple;
	
	long			num_proxies;
	void			**n_proxy;
	long			n_in;
	
	void			**n_outlet;
	long			num_outlets;
} t_route;



///////////////////////// function prototypes
//// standard set
void *route_new(t_symbol *s, long argc, t_atom *argv);
void route_free(t_route *x);
void route_assist(t_route *x, void *b, long m, long a, char *s);

void route_int(t_route *x, t_atom_long num);
void route_float(t_route *x, double num);
void route_anything(t_route *x, t_symbol *msg, long ac, t_atom *av);
void route_bang(t_route *x);
	

	
//////////////////////// global class pointer variable
void *route_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();

	c = class_new("sy.route", (method)route_new, (method)route_free, (long)sizeof(t_route), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)route_assist,			"assist",		A_CANT, 0);  

	// @method anything @digest Route input
	// @description If input comes from the first outlet, <o>sy.route</o> checks if the first characters of incoming input match the ones defined as arguments 
	// (or modified via the inlets from 2nd to last one).
	// If so, it outputs the input from the corresponding outlet (1st argument corresponds to 1st outlet and 2nd inlet; 2nd argument corresponds to 2nd outlet and 3rd inlet, and so on).
	// If no match is found, the input is simply re-output from the rightmost outlet. <br />
	// If input comes from any other inlet, see <m>symbol</m>.

	// @method symbol @digest Set router
	// @description A symbol in the N-th inlet, with N bigger than 1, sets the routing characters for the (N-1)-th router, corresponding to the (N-1)-th outlet.
	class_addmethod(c, (method)route_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)route_float,			"float",		A_FLOAT,	0);
	class_addmethod(c, (method)route_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)route_anything,		"anything",		A_GIMME,	0);

	// @method bang @digest Perform last operation
	// @description Routes the most recently received input data
	class_addmethod(c, (method)route_bang,			"bang",			0);

    syobj_class_add_listin_attr(c);

	CLASS_ATTR_CHAR(c, "keep", 0, t_route, keep);
	CLASS_ATTR_STYLE_LABEL(c,"keep",0,"onoff","Keep Routers");
	CLASS_ATTR_BASIC(c,"keep",0);
	// @description Toggles the ability to keep the routing symbols at output. By default it is off.

    CLASS_ATTR_CHAR(c, "end", 0, t_route, use_end);
    CLASS_ATTR_STYLE_LABEL(c,"end",0,"onoff","Match Symbols End");
    CLASS_ATTR_BASIC(c,"end",0);
    // @description Toggles the ability to route according to the end of the symbols, and not to their beginning.
    // This is useful in many circumstances, e.g. to route filenames according to their extension.

	CLASS_ATTR_CHAR(c, "multiple", 0, t_route, multiple); 
	CLASS_ATTR_STYLE_LABEL(c,"multiple",0,"onoff","Allow Multiple Matches");
	CLASS_ATTR_BASIC(c,"multiple",0);
	// @description Toggles the ability to allow finding multiple matches. By default it is on.
	
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	route_class = c;

	return 0;
}


void route_assist(t_route *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { 
		if (a == 0)	// @in 0 @type anything @digest Symbol or list to be routed
			sprintf(s, "anything: Symbol or list to be routed");
		else // @in 1 @loop 1 @type anything @digest Change specific router 
			sprintf(s, "Change Router for Match %s", x->routers[a-1]->s_name);
	} 
	else {	
		if (a < x->num_outlets - 1) // @in 0 @loop 1 @type anything @digest Outputs if input starts with corresponding router
            sprintf(s, "Outputs if Input %s with %s", x->use_end ?
                    "ends" : "starts", x->routers[a]->s_name);	// @description Input is output from each one of these outlets if its starting characters match the corresponding router
																			// If <m>keep</m> is set to 1, input is output untouched, otherwise the routing characters are stripped, and the remaining 
																			// part is output as a single symbol  
		else // @in 1 @type anything @digest Input if Input doesn't match
			sprintf(s, "Input if Input doesn't Match"); // @description Outputs the input data when no router has been matched. 			
	}
}

void route_free(t_route *x)
{
	long i;
	for (i = x->num_proxies - 1; i > 0; i--)
		object_free(x->n_proxy[i]);
	sysmem_freeptr(x->n_proxy);
	sysmem_freeptr(x->n_outlet);
	syobj_obj_free((t_sy_object *)x);
}


void *route_new(t_symbol *s, long argc, t_atom *argv)
{
	t_route *x = NULL;
	long true_ac = attr_args_offset(argc, argv);
    
	if ((x = (t_route *)object_alloc(route_class))) {
		
		syobj_obj_setup((t_sy_object *)x, 2);
		x->keep = 0;
		x->multiple = 1;

		// @arg 0 @name routers @optional 0 @type list @digest Routing symbols
		// @description Sets the routing symbols, i.e. the symbol whose characters have to be matched
		// at the beginning of the incoming symbols (or at the end, depending on the <m>end</m> attribute
		long i;
		x->num_routers = 0;
		for (i = 0; i < true_ac && x->num_routers < SY_MAX_INLETS; i++)  {
			if (atom_gettype(argv + i) == A_SYM) {
				x->routers[x->num_routers] = atom_getsym(argv + i);
				x->num_routers++;
			} else if (atom_gettype(argv + i) == A_LONG || atom_gettype(argv + i) == A_FLOAT) {
				x->routers[x->num_routers] = atom_to_symbol(argv + i, SY_DEFAULT_MAX_DECIMALS);
				x->num_routers++;
			}
		}

		attr_args_process(x, argc, argv);

		x->num_proxies = x->num_routers + 1;
		x->n_proxy = (void **) sysmem_newptr(x->num_proxies * sizeof (void *));
		for (i = x->num_proxies - 1; i > 0; i--)
			x->n_proxy[i] = proxy_new((t_object *) x, i, &x->n_in);
		
		x->num_outlets = x->num_proxies;
		x->n_outlet = (void **) sysmem_newptr(x->num_outlets * sizeof (void *));
		for (i = x->num_outlets - 1; i >= 0; i--)
			x->n_outlet[i] = syout((t_object *)x);
        
	}
	return (x);
}

void route_int(t_route *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	route_anything(x, _sym_list, 1, argv);
}

void route_float(t_route *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	route_anything(x, _sym_list, 1, argv);
}

void route_bang(t_route *x)
{	
	route_anything(x, _sym_bang, 0, NULL);
}

char router_sym_match(t_symbol *router, t_symbol *sym, char direction)
{
	if (!sym || !router)
		return 0;
	
	long len = strlen(router->s_name);
    long sym_len = strlen(sym->s_name);
	
	if (sym_len < len)
        return 0;
    
    if (direction == 1) { // from the end
        if (strncmp(router->s_name, sym->s_name + sym_len - len, len) == 0)
            return 1;
    } else {
        if (strncmp(router->s_name, sym->s_name, len) == 0)
            return 1;
    }
    
    return 0;
}

void route_anything(t_route *x, t_symbol *msg, long ac, t_atom *av)
{
	long	inlet = proxy_getinlet((t_object *) x);
	
	long	stored_ac = 0, stored_ac_as_single_sym = 0;
	t_atom	*stored_av = NULL, *stored_av_as_single_sym = NULL;
	long	i, keep = x->keep, multiple = x->multiple, num_routers = x->num_routers;
	t_symbol *routers[SY_MAX_INLETS];
    char    dir = x->use_end;
    long    listin = x->n_ob.l_listin_mode;
	
	if (inlet > 0) {
		// change router
		syobj_store_content((t_sy_object *)x, msg, ac, av, inlet);
		stored_ac = syobj_get_store_contents((t_sy_object *) x, inlet, SY_STORE_CLONE_AS_SINGLE_SYMBOL, &stored_av);
		if (stored_ac && stored_av) {
			x->routers[inlet - 1] = atom_getsym(stored_av);
			sysmem_freeptr(stored_av);
		}
		return;
	}

	if (msg != _sym_bang) 
		syobj_store_content((t_sy_object *) x, msg, ac, av, 0);

	stored_ac = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE, &stored_av);
	stored_ac_as_single_sym = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE_ALL_SYMBOLS_AND_ACCOUNT_FOR_LIST_MODE, &stored_av_as_single_sym);
 
	// copying symbols locally
	for (i = 0; i < num_routers; i++)
		routers[i] = x->routers[i];
	
    long *this_found = NULL;
    long this_found_count = 0;
    if (listin == SY_LISTIN_MODE_ELEMENTWISE)
        this_found = (long *)sysmem_newptr(stored_ac_as_single_sym * sizeof(long));
    
    char any_found = -1;
	if (stored_ac > 0) {
		// search for matches
        long c;
        for (c = 0; c < stored_ac_as_single_sym; c++) {
            long i;
            char found = -1;
            t_symbol *s = atom_getsym(stored_av_as_single_sym + c);
            long s_len = strlen(s->s_name);
            for (i = 0; i < num_routers; i++) {
                if (router_sym_match(routers[i], s, dir)) {
                    long len_routers_i = strlen(routers[i]->s_name);
                    
                    // found!
                    if (!keep) {
                        t_atom out_atom;
                        if (dir) {
                            char *temp = strdup(s->s_name);
                            if (s_len >= len_routers_i)
                                temp[s_len - len_routers_i] = 0;
                            t_symbol *out = gensym(temp);
                            atom_setsym(&out_atom, out);
                            sysmem_freeptr(temp);
                        } else {
                            t_symbol *out = gensym(s->s_name + len_routers_i);
                            atom_setsym(&out_atom, out);
                        }
                        sy_outlet(x->n_outlet[i], NULL, 1, &out_atom);
                    } else if (listin == SY_LISTIN_MODE_ELEMENTWISE) {
                        sy_outlet(x->n_outlet[i], NULL, 1, stored_av_as_single_sym + c);
                    } else
                        sy_outlet(x->n_outlet[i], NULL, stored_ac, stored_av);
                    
                    found = any_found = i;
                    
                    if (!multiple) {
                        if (listin == SY_LISTIN_MODE_GLOBALLY)
                            goto end;
                        else
                            break;
                    }
                }
            }
            
            if (listin == SY_LISTIN_MODE_ELEMENTWISE && found == -1)
                this_found[this_found_count++] = c;
        }
	}
    
end:
    
	if (listin == SY_LISTIN_MODE_GLOBALLY && any_found == -1) {
		// not found!
		sy_outlet(x->n_outlet[x->num_outlets - 1], NULL, stored_ac, stored_av);
    } else if (listin == SY_LISTIN_MODE_ELEMENTWISE && this_found_count > 0) {
        t_atom *unmatched_av = (t_atom *)sysmem_newptr(this_found_count * sizeof(t_atom));
        for (long h = 0; h < this_found_count; h++)
            *(unmatched_av + h) = stored_av[this_found[h]];
        sy_outlet(x->n_outlet[x->num_outlets - 1], NULL, this_found_count, unmatched_av);
        sysmem_freeptr(unmatched_av);
    }
    
    if (this_found)
        sysmem_freeptr(this_found);

	sysmem_freeptr(stored_av);
	sysmem_freeptr(stored_av_as_single_sym);
}
