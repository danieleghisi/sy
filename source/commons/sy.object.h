/**
 @file
 sy.object.h
 Header for the definition of a sy object
 
 by Daniele Ghisi
 */

#include "sy.h"

#define	SY_DEFAULT_MAX_DECIMALS 6

#define SY_MAX_INLETS	256
#define SY_MAX_OUTLETS	256






// This line below should always be UNcommented, otherwise things don't work so great in Max environment
#define SY_REPARSE_FOR_MESSAGE_SELECTOR


#ifdef SY_REPARSE_FOR_MESSAGE_SELECTOR
#define syout(...) outlet_new(__VA_ARGS__, NULL)
#else
#define syout(...) listout(__VA_ARGS__)
#endif




#ifdef MAC_VERSION

/** increment an atomic int value
 @ingroup threading
 return value of ATOMIC_INCREMENT and ATOMIC_DECREMENT is the *new* value after performing the operation
 */

#define ATOMIC_INCREMENT_32(atomicptr) OSAtomicIncrement32((int32_t *)atomicptr)

/** increment an atomic int value with a memory barrier
 @ingroup threading
 return value of ATOMIC_INCREMENT and ATOMIC_DECREMENT is the *new* value after performing the operation
 */
#define ATOMIC_INCREMENT_BARRIER_32(atomicptr) OSAtomicIncrement32Barrier((int32_t *)atomicptr)

/** decrement an atomic int value
 @ingroup threading
 return value of ATOMIC_INCREMENT and ATOMIC_DECREMENT is the *new* value after performing the operation
 */
#define ATOMIC_DECREMENT_32(atomicptr) OSAtomicDecrement32((int32_t *)atomicptr)

/** decrement an atomic int value with a memory barrier
 @ingroup threading
 return value of ATOMIC_INCREMENT and ATOMIC_DECREMENT is the *new* value after performing the operation
 */
#define ATOMIC_DECREMENT_BARRIER_32(atomicptr) OSAtomicDecrement32Barrier((int32_t *)atomicptr)

/** increment an atomic int value
 @ingroup threading
 return value of ATOMIC_INCREMENT and ATOMIC_DECREMENT is the *new* value after performing the operation
 */

#define ATOMIC_INCREMENT_64(atomicptr) OSAtomicIncrement64((int64_t *)atomicptr)

/** increment an atomic int value with a memory barrier
 @ingroup threading
 return value of ATOMIC_INCREMENT and ATOMIC_DECREMENT is the *new* value after performing the operation
 */
#define ATOMIC_INCREMENT_BARRIER_64(atomicptr) OSAtomicIncrement64Barrier((int64_t *)atomicptr)

/** decrement an atomic int value
 @ingroup threading
 return value of ATOMIC_INCREMENT and ATOMIC_DECREMENT is the *new* value after performing the operation
 */
#define ATOMIC_DECREMENT_64(atomicptr) OSAtomicDecrement64((int64_t *)atomicptr)

/** decrement an atomic int value with a memory barrier
 @ingroup threading
 return value of ATOMIC_INCREMENT and ATOMIC_DECREMENT is the *new* value after performing the operation
 */
#define ATOMIC_DECREMENT_BARRIER_64(atomicptr) OSAtomicDecrement64Barrier((int64_t *)atomicptr)

/*
 #define ATOMIC_COMPARE_SWAP32(oldvalue, newvalue, atomicptr) (OSAtomicCompareAndSwap32Barrier(oldvalue, newvalue, atomicptr))
 #define ATOMIC_COMPARE_SWAP64(oldvalue, newvalue, atomicptr) (OSAtomicCompareAndSwap64Barrier(oldvalue, newvalue, atomicptr))
 */


#else // WIN_VERSION

BEGIN_USING_C_LINKAGE
LONGLONG  __cdecl _InterlockedIncrement64(LONGLONG volatile *Addend);
LONGLONG  __cdecl _InterlockedDecrement64(LONGLONG volatile *Addend);
END_USING_C_LINKAGE

#pragma intrinsic (_InterlockedIncrement64)
#pragma intrinsic (_InterlockedDecrement64)

/**	Use this routine for incrementing a global counter using a threadsafe and multiprocessor safe method.
 @ingroup			threading
 @param	atomicptr	pointer to the (int) counter.
 */

// on windows I don't think there are non-barrier atomic increment / decrement functions
// perhaps could be done with inline assembly?


#define ATOMIC_INCREMENT_32(atomicptr)			(_InterlockedIncrement(atomicptr))
#define ATOMIC_INCREMENT_BARRIER_32(atomicptr)	(_InterlockedIncrement(atomicptr))


/**	Use this routine for decrementing a global counter using a threadsafe and multiprocessor safe method.
 @ingroup	threading
 @param	atomicptr	pointer to the (int) counter.
 */
#define ATOMIC_DECREMENT_32(atomicptr)			(_InterlockedDecrement(atomicptr))
#define ATOMIC_DECREMENT_BARRIER_32(atomicptr)	(_InterlockedDecrement(atomicptr))

#define ATOMIC_INCREMENT_64(atomicptr)			(_InterlockedIncrement64(atomicptr))
#define ATOMIC_INCREMENT_BARRIER_64(atomicptr)	(_InterlockedIncrement64(atomicptr))


/**	Use this routine for decrementing a global counter using a threadsafe and multiprocessor safe method.
 @ingroup	threading
 @param	atomicptr	pointer to the (int) counter.
 */
#define ATOMIC_DECREMENT_64(atomicptr)			(_InterlockedDecrement64(atomicptr))
#define ATOMIC_DECREMENT_BARRIER_64(atomicptr)	(_InterlockedDecrement64(atomicptr))

#endif // WIN_VERSION

#ifdef C74_x64
#define t_atom_long_atomic t_int64_atomic
#define ATOMIC_INCREMENT_ATOM(atomicptr)  ATOMIC_INCREMENT_64(atomicptr)
#define ATOMIC_INCREMENT_BARRIER_ATOM(atomicptr)  ATOMIC_INCREMENT_BARRIER_64(atomicptr)
#define ATOMIC_DECREMENT_ATOM(atomicptr)  ATOMIC_DECREMENT_64(atomicptr)
#define ATOMIC_DECREMENT_BARRIER_ATOM(atomicptr)  ATOMIC_DECREMENT_BARRIER_64(atomicptr)
#else
#define t_atom_long_atomic t_int32_atomic
#define ATOMIC_INCREMENT_ATOM(atomicptr)  ATOMIC_INCREMENT_32(atomicptr)
#define ATOMIC_INCREMENT_BARRIER_ATOM(atomicptr)  ATOMIC_INCREMENT_BARRIER_32(atomicptr)
#define ATOMIC_DECREMENT_ATOM(atomicptr)  ATOMIC_DECREMENT_32(atomicptr)
#define ATOMIC_DECREMENT_BARRIER_ATOM(atomicptr)  ATOMIC_DECREMENT_BARRIER_32(atomicptr)
#endif

#define t_sy_atomic_lock t_int32_atomic




/** Modes to deal with number input */
typedef enum _sy_numin_modes {
	SY_NUMIN_MODE_LET_THROUGH = 0,		///< Let numbers through, unmodified
	SY_NUMIN_MODE_CONVERT = 1,			///< Convert all numbers to symbols
	SY_NUMIN_MODE_DROP = 2,			///< Drop all numbers from output (e.g. strip all numbers from the input list)
} e_sy_numin_modes;

/** Modes to deal with number output */
typedef enum _sy_numout_modes {
	SY_NUMOUT_MODE_ONLY_FROM_NUMBER = 0,		///< Only keep the numbers if they are already numbers (= don't change output)
	SY_NUMOUT_MODE_FROM_NUMERIC_SYMBOL = 1,		///< Convert all numeric symbols to numbers
	SY_NUMOUT_MODE_FROM_ANY_SYMBOL = 2,			///< Convert all symbols to numbers
} e_sy_numout_modes;


/** Modes to deal with list input */
typedef enum _sy_listin_modes {
    SY_LISTIN_MODE_GLOBALLY = 0,            ///< Process list globally
    SY_LISTIN_MODE_ELEMENTWISE = 1,			///< Process each element of the list separately
} e_sy_listin_modes;

/** Modes to deal with list output */
typedef enum _sy_listout_modes {
    SY_LISTOUT_MODE_SINGLE_SYMBOL   = 0,    ///< Output everything as a single symbol, always
    SY_LISTOUT_MODE_ADAPT = 1,              ///< Adapt to input type (roughly: output lists when lists are received)
    SY_LISTOUT_MODE_ALWAYS_SEPARATE = 2,	///< Force deparsing of output symbols, always subdivied into atoms as much as possible.
                                            ///  This is roughly equivalent to having a [fromsymbol] module connected to the outlet.
} e_sy_listout_modes;





/** Inlet store cloning options */
typedef enum _sy_store_clone_options {
	SY_STORE_DONT_CLONE = 0,							///< Don't clone array; just returns pointer to the stored array (don't free memory!)
	SY_STORE_CLONE = 1,									///< Clone array (you need to free memory)
	SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_MODE = 2,		///< Clone array, and account for the object "number" attribute to possibly convert numbers
	SY_STORE_CLONE_AS_SINGLE_SYMBOL = 3,				///< Clone all the input as a single symbol; output array will have just 1 symbol at output 
    SY_STORE_CLONE_AND_ACCOUNT_FOR_NUMBER_AND_LIST_MODE = 4,		///< Clone array, and account for the object "number" attribute to possibly convert numbers
    SY_STORE_CLONE_ALL_SYMBOLS_AND_ACCOUNT_FOR_LIST_MODE = 5,		///< Clone array, and account for the object "number" attribute to possibly convert numbers
} e_sy_store_clone_options;



/** A thread-safe storage cache for lists, in GIMME signature form */
typedef struct _syobj_store
{
	long				ac;
	t_atom				*av;
	t_sy_atomic_lock	s_lock;
} t_syobj_store;


/** The structure for a generic vanilla object in the sy library */
typedef struct sy_object
{
	t_object				l_ob;			///< The t_object from which we inherit
	
	long					l_numin_mode;		///< Attribute setting how we deal with numbers at input. 
	long					l_numout_mode;		///< Attribute setting how we deal with numbers at output.

    long					l_listin_mode;		///< Attribute setting how we deal with numbers at output.
    long					l_listout_mode;		///< Attribute setting how we deal with numbers at output.

	long					l_maxdecimals;	///< Maximum number of decimals when converting floats to symbols
	t_symbol				*l_locale;		///< Attribute setting the locale, for language-specific encoding 
	///  See http://userguide.icu-project.org/locale
    	
	t_systhread_mutex		l_mutex;		///< Generic mutex for the object
	
	t_uint32				l_numstores;	///< How many stores we have
	t_syobj_store			*l_incache;		///< The stores
} t_sy_object;

void sy_atomic_lock(t_sy_atomic_lock *lock);
void sy_atomic_unlock(t_sy_atomic_lock *lock);

t_symbol *atom_to_symbol(t_atom *av, long max_decimals_for_conversion);

// *out_av is allocated ONLY if it was NULL
long atom_array_duplicate(long ac, t_atom *av, t_atom **out_av, e_sy_numin_modes number_handling, long max_decimals_for_conversion);
// *out_av is allocated ONLY if it was NULL
long atom_array_duplicate_with_sym(t_symbol *sym, long ac, t_atom *av, t_atom **out_av, e_sy_numin_modes number_handling, long max_decimals_for_conversion);

t_syobj_store *syobj_get_incache(t_sy_object *x);
void syobj_store_content(t_sy_object *x, t_symbol *msg, long ac, t_atom *av, long store_num);

// *out_av is allocated ONLY if it was NULL
long syobj_get_store_contents(t_sy_object *x, long num, e_sy_store_clone_options clone, t_atom **out_av);
t_symbol *syobj_get_store_contents_as_single_symbol(t_sy_object *x, long num);
void syobj_obj_setup(t_sy_object *x, long stores);
void syobj_obj_free(t_sy_object *x);


// Generic outlet routine handling the message selector
void *sy_outlet(void *o, t_symbol *s, short ac, t_atom *av);


void syobj_class_add_numin_attr(t_class *c);
void syobj_class_add_numout_attr(t_class *c);
void syobj_class_add_maxdecimals_attr(t_class *c);
void syobj_class_add_locale_attr(t_class *c);
void syobj_class_add_listin_attr(t_class *c);
void syobj_class_add_listout_attr(t_class *c);
t_max_err syobj_setattr_numbers(t_sy_object *x, t_object *attr, long ac, t_atom *av);


