/**
 @file
 sy.rot.c
 
 @name 
 sy.rot
 
 @realname 
 sy.rot
 
 @type
 object
 
 @module
 sy
 
 @author
 Daniele Ghisi
 
 @digest 
 Rotate symbol characters
 
 @description
 Circularly rotates the characters of incoming symbols.
 
 @discussion
 
 @category
 sy
 
 @keywords
 rotate, shift, circular, character
 
 @seealso
 sy.rev
 
 @owner
 Daniele Ghisi
 */


#include "sy.commons.h"			// ext.h and ext_obex.h include are inside sy.commons.h


////////////////////////// object struct
typedef struct _rot 
{
	t_sy_object		n_ob;		// the object itself (must be first)
	long			shift;
	void			*n_outlet;
} t_rot;



///////////////////////// function prototypes
//// standard set
void *rot_new(t_symbol *s, long argc, t_atom *argv);
void rot_free(t_rot *x);
void rot_assist(t_rot *x, void *b, long m, long a, char *s);

void rot_int(t_rot *x, t_atom_long num);
void rot_float(t_rot *x, double num);
void rot_anything(t_rot *x, t_symbol *msg, long ac, t_atom *av);
void rot_bang(t_rot *x);



//////////////////////// global class pointer variable
void *rot_class;


int C74_EXPORT main(void)
{	
	// object initialization, NEW STYLE
	t_class *c;
	
	common_symbols_init();
	
	c = class_new("sy.rot", (method)rot_new, (method)rot_free, (long)sizeof(t_rot), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)rot_assist,			"assist",		A_CANT, 0);  
	
	// @method anything @digest Rotate symbols
	// @description If <m>global</m> is set to 1 (default), the characters of the whole input list are
	// circularly rotated of a certain amount, defined by the <m>shift</m> attribute.
	// If <m>global</m> is set to 0, each individual incoming symbol will have its characters rotated by 
	// the defined amount, but the global order of symbols will not be touched.
	// Finally, the result is output.
	class_addmethod(c, (method)rot_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)rot_float,		"float",		A_FLOAT,	0);
	class_addmethod(c, (method)rot_anything,		"list",			A_GIMME,	0);
	class_addmethod(c, (method)rot_anything,		"anything",		A_GIMME,	0);
	
	// @method bang @digest Rotate last input symbols
	// @description Perform the rotation on the most recently received input symbols.
	class_addmethod(c, (method)rot_bang,			"bang",			0);
	
	syobj_class_add_numin_attr(c);
	syobj_class_add_numout_attr(c);
	syobj_class_add_maxdecimals_attr(c);	
    syobj_class_add_listin_attr(c);
    syobj_class_add_listout_attr(c);

	CLASS_ATTR_LONG(c, "shift", 0, t_rot, shift); 
	CLASS_ATTR_STYLE_LABEL(c,"shift",0,"text","Shift");
    CLASS_ATTR_BASIC(c, "shift", 0);
	// @description Number of characters to rotate the incoming input of. Positive numbers rotate left, 
	// negative numbers rotate right.
	
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	rot_class = c;
	
	return 0;
}


void rot_assist(t_rot *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type anything @digest Incoming symbols
		sprintf(s, "anything: Incoming symbols");
	} 
	else {	// @out 0 @type anything @digest Rotated input 
		sprintf(s, "anything: Rotated input");
	}
}

void rot_free(t_rot *x)
{
	syobj_obj_free((t_sy_object *)x);
}


void *rot_new(t_symbol *s, long argc, t_atom *argv)
{
	t_rot *x = NULL;
    
	if ((x = (t_rot *)object_alloc(rot_class))) {
		x->shift = 0;
		
		// @arg 0 @name shift @optional 1 @type int @digest Shift
		// @description Sets the initial value for the <m>shift</m> attribute.
		if (argc && atom_gettype(argv) == A_LONG)
			x->shift = atom_getlong(argv);
		
        syobj_obj_setup((t_sy_object *)x, 1);

        attr_args_process(x, argc, argv);
		
		x->n_outlet = syout((t_object *)x);
	}
	return (x);
}

void rot_int(t_rot *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	rot_anything(x, _sym_list, 1, argv);
}

void rot_float(t_rot *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	rot_anything(x, _sym_list, 1, argv);
}

void rot_bang(t_rot *x)
{	
	rot_anything(x, _sym_bang, 0, NULL);
}

long substitute_with_rot_fn(t_sy_object *x, t_atom *atom_in, t_atom *atom_out, void *shift, void *dummy2, void *dummy3)
{
	char type_in = atom_gettype(atom_in); 
	
	if (type_in == A_SYM) {
		atom_setsym(atom_out, symbol_rotate(atom_getsym(atom_in), *((long *)shift)));
	} else if (type_in == A_LONG || type_in == A_FLOAT) {
		*atom_out = *atom_in;
	} else {
		return 0;
	}
	
	return 1;
}


void rot_anything(t_rot *x, t_symbol *msg, long ac, t_atom *av)
{
	long	stored_ac, out_ac;
	t_atom	*stored_av = NULL;
	t_atom	*out_av = NULL;
	long	shift = x->shift;
	
	if (msg != _sym_bang) 
		syobj_store_content((t_sy_object *) x, msg, ac, av, 0);
	
	stored_ac = syobj_get_store_contents((t_sy_object *) x, 0, SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_MODE, &stored_av);
	
	if (x->n_ob.l_listin_mode == SY_LISTIN_MODE_ELEMENTWISE)
		out_ac = iterate_on_gimme((t_sy_object *) x, NULL, stored_ac, stored_av, &out_av, (atom_modif_fn)substitute_with_rot_fn, &shift, NULL, NULL);
	else {
		// much more complicate
		
		// 0. we allocate ONE more symbol for the out_av array, since we might need to add a symbol at output while rotating
		out_av = (t_atom *)sysmem_newptr((stored_ac + 1) * sizeof(t_atom));
		out_ac = atom_array_duplicate(stored_ac, stored_av, &out_av, SY_NUMIN_MODE_LET_THROUGH, 0);

		if (out_ac) {
			
			// 1. calculate total input character length
			long i, total_len = 0;
			long *len = (long *)sysmem_newptr(out_ac * sizeof(long));
			for (i = 0; i < out_ac; i++) {
				long type = atom_gettype(out_av + i);
				switch (type) {
					case A_SYM:
						len[i] = symbol_get_num_codepoints(atom_getsym(out_av + i), true);
						total_len += len[i];
						break;
					case A_LONG:
					case A_FLOAT:
						len[i] = 1;
						total_len += 1; // considered as a single unit
						break;
					default:
						len[i] = 0;
						break;
				}
			}
			
			if (total_len > 0) {
				
				// 2. retouch shift
				while (shift < 0)
					shift += total_len;
				
				shift %= total_len;
				
				// 3. coarse rotation (rotate whole atoms)
				long cur = 0;
				while (shift >= len[cur]) {
					shift -= len[cur];
					cur++;
				}
				if (cur > 0)
					atom_array_rotate(out_ac, out_av, cur);
				
				// 4. fine rotation (rotate first element's characters)
				if (shift > 0) { 
					// by the way, this means that the atom is a symbol, otherwise we'd have already dealt with it
					if (atom_gettype(out_av) == A_SYM) {
						t_symbol *left = NULL, *right = NULL;
						symbol_slice_at_codepoint(atom_getsym(out_av), shift, &left, &right);
						atom_setsym(out_av, right);
						if (left) 
							atom_setsym(out_av + (out_ac++), left); // we fill the previously additionally allocated atom
					}
				}
			}
			
			sysmem_freeptr(len);
		}
	}
	
	syobj_atom_array_reparse_account_for_numout((t_sy_object *)x, out_ac, out_av);
    syobj_atom_array_reparse_account_for_listout((t_sy_object *)x, &out_ac, &out_av);

	if (out_ac > 0) 
		sy_outlet(x->n_outlet, NULL, out_ac, out_av);
	
	sysmem_freeptr(stored_av);
	sysmem_freeptr(out_av);
}
