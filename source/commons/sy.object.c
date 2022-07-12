/**
	@file
	sy.object.c
	Function to handle a sy object

	by Daniele Ghisi
*/


#include "sy.object.h"

void sy_atomic_lock(t_sy_atomic_lock *lock)
{
	while (ATOMIC_INCREMENT_32(lock) > 1)
		ATOMIC_DECREMENT_BARRIER_32(lock);
}

void sy_atomic_unlock(t_sy_atomic_lock *lock)
{
	ATOMIC_DECREMENT_BARRIER(lock);
}

char is_atom_number(t_atom *av)
{
	return (atom_gettype(av) == A_LONG || atom_gettype(av) == A_FLOAT);
}

t_symbol *atom_to_symbol(t_atom *av, long max_decimals_for_conversion)
{
	long type = atom_gettype(av);
	switch (type) {
		case A_LONG:
		case A_FLOAT:
		{
			char buf[100];
			if (type == A_LONG)
				snprintf_zero(buf, 100, "%ld", atom_getlong(av));
			else
				snprintf_zero(buf, 100, "%.*f", max_decimals_for_conversion, atom_getfloat(av));
			return gensym(buf);
		}
			break;
		case A_SYM:	
			return atom_getsym(av);
		case A_COMMA:	
			return gensym(",");
		case A_SEMI:	
			return gensym(";");
		case A_DOLLAR:	
		case A_DOLLSYM:	
			return gensym("$");
		default:
			return gensym("");
			break;
	}
}

long atom_array_duplicate(long ac, t_atom *av, t_atom **out_av, e_sy_numin_modes number_handling, long max_decimals_for_conversion)
{
	if (!ac) 
		return 0;
	
	if (out_av && !*out_av) //if it is NULL!
		*out_av = (t_atom *)sysmem_newptr(ac * sizeof(t_atom));
	
	long i;
	t_atom *temp1 = *out_av;
	t_atom *temp2 = av;
	switch (number_handling) {
		case SY_NUMIN_MODE_CONVERT:
			for (i = 0; i < ac; i++, temp1++, temp2++) {
				if (atom_gettype(temp2) == A_SYM)
					*temp1 = *temp2;
				else if (is_atom_number(temp2))
					atom_setsym(temp1, atom_to_symbol(temp2, max_decimals_for_conversion));
                else
                    *temp1 = *temp2;
			}
			break;
		case SY_NUMIN_MODE_DROP:
			for (i = 0; i < ac; )
				if (is_atom_number(temp2)) {
					ac--;
					temp2++;
				} else {
					*temp1 = *temp2;
					i++;
					temp1++;
					temp2++;
				}
			break;
		default:
			for (i = 0; i < ac; i++, temp1++, temp2++)
				*temp1 = *temp2;
			break;
	}
	return ac;
}

long atom_array_duplicate_with_sym(t_symbol *sym, long ac, t_atom *av, t_atom **out_av, e_sy_numin_modes number_handling, long max_decimals_for_conversion)
{
	if (!sym || sym == _sym_list) // || sym == gensym(""))
		return atom_array_duplicate(ac, av, out_av, number_handling, max_decimals_for_conversion);
		
	if (out_av && !*out_av)
		*out_av = (t_atom *)sysmem_newptr((ac + 1) * sizeof(t_atom));

	long i;
	t_atom *temp1 = *out_av;
	t_atom *temp2 = av;

	atom_setsym(temp1, sym);
	temp1++;
	
	switch (number_handling) {
		case SY_NUMIN_MODE_CONVERT:
			for (i = 0; i < ac; i++, temp1++, temp2++) {
				if (atom_gettype(temp2) == A_SYM)
					*temp1 = *temp2;
				else
					atom_setsym(temp1, atom_to_symbol(temp2, max_decimals_for_conversion));
			}
			break;
		case SY_NUMIN_MODE_DROP:
			for (i = 0; i < ac; )
				if (is_atom_number(temp2)) {
					ac--;
					temp2++;
				} else {
					*temp1 = *temp2;
					i++;
					temp1++;
					temp2++;
				}
			break;
		default:
			for (i = 0; i < ac; i++, temp1++, temp2++)
				*temp1 = *temp2;
			break;
	}
	return ac + 1;
}

t_syobj_store *syobj_get_incache(t_sy_object *x)
{
	return ((t_sy_object *) x)->l_incache;
}


void syobj_store_content(t_sy_object *x, t_symbol *msg, long ac, t_atom *av, long store_num)
{
	t_syobj_store *store = syobj_get_incache(x) + store_num;
	t_atom *kill_me;
	sy_atomic_lock(&store->s_lock);
	kill_me = store->av;
	store->av = NULL; // needed by atom_array_duplicate_with_sym, in order for it to allocate memory
	store->ac = atom_array_duplicate_with_sym(msg, ac, av, &store->av, SY_NUMIN_MODE_LET_THROUGH, x->l_maxdecimals);
	sy_atomic_unlock(&store->s_lock);
	sysmem_freeptr(kill_me);
}


long syobj_get_store_contents(t_sy_object *x, long num, e_sy_store_clone_options clone, t_atom **out_av)
{
	t_syobj_store *store = ((t_sy_object *) x)->l_incache + num;
	long out_ac = 0;
    
    if (clone == SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_AND_LIST_MODE) {
        if (x->l_listin_mode == SY_LISTIN_MODE_GLOBALLY)
            clone = SY_STORE_CLONE_AS_SINGLE_SYMBOL;
        else
            clone = SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_MODE;
    } else if (clone == SY_STORE_CLONE_ALL_SYMBOLS_AND_ACCOUNT_FOR_LIST_MODE) {
        if (x->l_listin_mode == SY_LISTIN_MODE_GLOBALLY)
            clone = SY_STORE_CLONE_AS_SINGLE_SYMBOL;
    }
    
	sy_atomic_lock(&store->s_lock);
	switch (clone) {
		case SY_STORE_CLONE:
		case SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_MODE:
        case SY_STORE_CLONE_ALL_SYMBOLS_AND_ACCOUNT_FOR_LIST_MODE:
            out_ac = atom_array_duplicate(store->ac, store->av, out_av, (e_sy_numin_modes)(clone == SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_MODE ? x->l_numin_mode : (clone == SY_STORE_CLONE_ALL_SYMBOLS_AND_ACCOUNT_FOR_LIST_MODE ? SY_NUMIN_MODE_CONVERT : SY_NUMIN_MODE_LET_THROUGH)), x->l_maxdecimals);
			break;
		case SY_STORE_CLONE_AS_SINGLE_SYMBOL: 
		{
			char *buf = NULL;
			long textsize = 0;
			atom_gettext(store->ac, store->av, &textsize, &buf, OBEX_UTIL_ATOM_GETTEXT_SYM_NO_QUOTE);
			if (out_av && !*out_av)
				*out_av = (t_atom *)sysmem_newptr(sizeof(t_atom));
			out_ac = 1;
			atom_setsym(*out_av, gensym(buf));
			sysmem_freeptr(buf);
		}
			break;
		case SY_STORE_DONT_CLONE:
		default:
			*out_av = store->av;
			out_ac = store->ac;
			break;
	}
	sy_atomic_unlock(&store->s_lock);
	return out_ac;
}

t_symbol *syobj_get_store_contents_as_single_symbol(t_sy_object *x, long num)
{
    t_syobj_store *store = ((t_sy_object *) x)->l_incache + num;
    sy_atomic_lock(&store->s_lock);
    
    char *buf = NULL;
    t_symbol *out = _sym_nothing;
    long textsize = 0;
    atom_gettext(store->ac, store->av, &textsize, &buf, OBEX_UTIL_ATOM_GETTEXT_SYM_NO_QUOTE);
    if (buf) {
        out = gensym(buf);
        sysmem_freeptr(buf);
    }
    
    sy_atomic_unlock(&store->s_lock);
    
    return out;
}

void syobj_obj_setup(t_sy_object *x, long stores)
{
	x->l_numin_mode = SY_NUMIN_MODE_CONVERT;
	x->l_numout_mode = SY_NUMOUT_MODE_FROM_NUMERIC_SYMBOL; 
	x->l_maxdecimals = SY_DEFAULT_MAX_DECIMALS;
    x->l_listin_mode = SY_LISTIN_MODE_GLOBALLY;
    x->l_listout_mode = SY_LISTOUT_MODE_ADAPT;
	x->l_locale = _sym_nothing;
	systhread_mutex_new(&x->l_mutex, SYSTHREAD_MUTEX_NORMAL);
	if (stores) {
		x->l_numstores = stores;
		x->l_incache = (t_syobj_store *) sysmem_newptrclear(stores * sizeof(t_syobj_store));
	}
}

void syobj_obj_free(t_sy_object *x)
{
	long numstores = x->l_numstores;
	t_syobj_store *this_store = x->l_incache;
	systhread_mutex_free(x->l_mutex);
	if (this_store) {
		long i;
		for (i = 0; i < numstores; i++, this_store++) 
			sysmem_freeptr(this_store->av);
	}
	if (x->l_incache)
		sysmem_freeptr(x->l_incache);
}




t_max_err syobj_setattr_numin(t_sy_object *x, t_object *attr, long ac, t_atom *av){
	if (ac && av) {
		x->l_numin_mode = (e_sy_numin_modes)CLAMP(atom_getlong(av), 0, 2);
		object_attr_setdisabled((t_object *)x, gensym("maxdecimals"), x->l_numin_mode != SY_NUMIN_MODE_CONVERT);
	}
	return MAX_ERR_NONE;
}

t_max_err syobj_setattr_numout(t_sy_object *x, t_object *attr, long ac, t_atom *av){
	if (ac && av) 
		x->l_numout_mode = (e_sy_numout_modes)CLAMP(atom_getlong(av), 0, 2);
	return MAX_ERR_NONE;
}


void *sy_outlet(void *o, t_symbol *s, short ac, t_atom *av)
{
#ifdef SY_REPARSE_FOR_MESSAGE_SELECTOR
    if (s)
        return outlet_anything(o, s, ac, av);
    else if (ac > 0 && atom_gettype(av) == A_SYM)
        return outlet_anything(o, atom_getsym(av), ac - 1, ac > 1 ? av + 1 : NULL);
    else if (ac == 1 && atom_gettype(av) == A_LONG)
        return outlet_anything(o, _sym_int, ac, av);
    else if (ac == 1 && atom_gettype(av) == A_FLOAT)
        return outlet_anything(o, _sym_float, ac, av);
    else
        return outlet_anything(o, _sym_list, ac, av);
#else 
    return outlet_list(x->n_outlet, s, ac, av);
#endif
}


void syobj_class_add_numin_attr(t_class *c)
{
	CLASS_ATTR_LONG(c, "numin", 0, t_sy_object, l_numin_mode);
	CLASS_ATTR_STYLE_LABEL(c,"numin",0,"enumindex","When Numbers Are Input");
	CLASS_ATTR_ENUMINDEX(c,"numin", 0, "Let Through Convert To Symbol Drop"); 
	CLASS_ATTR_ACCESSORS(c, "numin", (method)NULL, (method)syobj_setattr_numin);
	CLASS_ATTR_CATEGORY(c, "numin", 0, "Behavior");
}

void syobj_class_add_numout_attr(t_class *c) 
{
	CLASS_ATTR_LONG(c, "numout", 0, t_sy_object, l_numout_mode);
	CLASS_ATTR_STYLE_LABEL(c,"numout",0,"enumindex","Output Numbers");
	CLASS_ATTR_ENUMINDEX(c,"numout", 0, "Only With Numeric Original Convert From Numeric Symbols Convert From All Symbols"); 
	CLASS_ATTR_ACCESSORS(c, "numout", (method)NULL, (method)syobj_setattr_numout);
	CLASS_ATTR_CATEGORY(c, "numout", 0, "Behavior");
}


void syobj_class_add_maxdecimals_attr(t_class *c) 
{
	CLASS_ATTR_LONG(c, "maxdecimals", 0, t_sy_object, l_maxdecimals);
	CLASS_ATTR_STYLE_LABEL(c,"maxdecimals",0,"text","Maximum Decimal Digits For Number Conversion");
	CLASS_ATTR_CATEGORY(c, "maxdecimals", 0, "Behavior");
}

void syobj_class_add_listin_attr(t_class *c)
{
    CLASS_ATTR_LONG(c, "listin", 0, t_sy_object, l_listin_mode);
    CLASS_ATTR_STYLE_LABEL(c,"listin",0,"enumindex","When Lists Are Input");
    CLASS_ATTR_ENUMINDEX(c,"listin", 0, "Process Globally Process Element-Wise");
    CLASS_ATTR_CATEGORY(c, "listin", 0, "Behavior");
}

void syobj_class_add_listout_attr(t_class *c)
{
    CLASS_ATTR_LONG(c, "listout", 0, t_sy_object, l_listout_mode);
    CLASS_ATTR_STYLE_LABEL(c,"listout",0,"enumindex","Output Elements");
    CLASS_ATTR_ENUMINDEX(c,"listout", 0, "Always As Single Symbol Adapt To Input Always Separate");
    CLASS_ATTR_CATEGORY(c, "listout", 0, "Behavior");
}


void syobj_class_add_locale_attr(t_class *c) 
{
	CLASS_ATTR_SYM(c, "locale", 0, t_sy_object, l_locale);
	CLASS_ATTR_STYLE_LABEL(c,"locale",0,"text","Locale");
	CLASS_ATTR_CATEGORY(c, "locale", 0, "Behavior");
}



