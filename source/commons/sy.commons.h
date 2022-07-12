/**
	@file
	sy.commons.h
	Common utilities header for sy library
 
	by Daniele Ghisi
 */

#include "sy.object.h"
#include <stdio.h>
#include <wctype.h>
#include "unicode/uchar.h"
#include "unicode/ustring.h"
#include "unicode/utypes.h"
#include "unicode/ustdio.h"
#include "unicode/ucol.h"
#include "unicode/usearch.h"
#include "unicode/uregex.h"



/** Case conversions */
typedef enum _sy_case_modes {
	SY_CASE_MODE_DONT = 0,			///< Don't change case
	SY_CASE_MODE_UPPER = 1,			///< To Upper case
	SY_CASE_MODE_LOWER = 2,			///< To lower case
	SY_CASE_MODE_TITLE = 3,			///< To title case (= symbol_capitalize)
	SY_CASE_MODE_SWITCH = 4,		///< Switch case
	SY_CASE_MODE_FOLD = 5,			///< Fold case (e.g. for string comparisons) – NB: not always equivalent to upper-case.
} e_sy_case_modes;


/** Unicode encoding */
typedef enum _sy_utf_encoding {
	SY_UTF_8 = 0,			///< UTF-8 encoding
	SY_UTF_16 = 1,			///< UTF-16 encoding
	SY_UTF_32 = 2,			///< UTF-32 encoding
} e_sy_utf_encoding;


/** Padding modes */
typedef enum _sy_pad_mode {
    SY_PAD_REPEAT = 0,                                ///< Repeat first or last element, e.g. abccccccc...
    SY_PAD_LOOP = 1,                                  ///< Loop elements, e.g. abcabcabcabc...
    SY_PAD_LOOP_PALINDROME = 2,                       ///< Palindrome loop, e.g. abccbaabccbaabc...
    SY_PAD_LOOP_PALINDROME_NO_REPEAT = 3,             ///< Palindrome loop without repetitions: abcbabcbabcba...
} e_sy_pad_mode;


typedef struct sy_pad_params
{
    long output_length;
    char align;
    e_sy_pad_mode mode;
    long num_loop_elems;
    t_symbol *reservoir;
    char allow_trimming;
    char rounding_direction;
} t_sy_pad_params;



/** Function modifying a given atom, one by one.
	Returns 1 if #atom_out was filled, 0 if modification was dropped (e.g. because the incoming atom is a number
	and the t_sy_object::nummode is set to #SY_NUMMODE_DROP).
	@ingroup interface
 */
typedef long (*atom_modif_fn)(t_sy_object *x, t_atom *atom_in, t_atom *atom_out, void *data1, void *data2, void *data3);

long iterate_on_gimme(t_sy_object *x, t_symbol *msg, long ac, t_atom *av, t_atom **new_av, atom_modif_fn modif_fn, void *data1, void *data2, void *data3);
long change_case_fn(t_sy_object *x, t_atom *atom_in, t_atom *atom_out, void *change_case_mode, void *locale, void *non_separating_chars);
long normalize_fn(t_sy_object *x, t_atom *atom_in, t_atom *atom_out, void *change_case_mode, void *dummy, void *dummy2);
long convert_fn(t_sy_object *x, t_atom *atom_in, t_atom *atom_out, void *output_encoding, void *dummy, void *dummy2);
long transform_fn(t_sy_object *x, t_atom *atom_in, t_atom *atom_out, void *transformer, void *dummy1, void *dummy2);

int32_t symbol_get_num_codepoints(t_symbol *sym, char nonstandard);
int32_t symbol_get_num_codepoints_fast(t_symbol *sym);
char is_utf8_byte_leading(unsigned char ch);
char is_utf16_surrogate_leading(t_uint32 ch);

// UTF-8 (Max symbols), UTF-16 and UTF-32 conversions
UChar *symbol_to_uchar_array(t_symbol *sym, int32_t *out_size);
t_symbol *symbol_from_uchar_array(UChar *buffer, int32_t size);
UChar *uchar_array_from_uchar32_array(UChar32 *source, int32_t source_size, int32_t *output_size);
UChar32 *uchar_array_to_uchar32_array(UChar *source, int32_t source_size, int32_t *output_size);
UChar32 *symbol_to_uchar32_array(t_symbol *sym, int32_t *out_size);
t_symbol *symbol_from_uchar32_array(UChar32 *source, int32_t source_size);

long strength_attribute_to_ICU_flag(t_sy_object *x, long strength);

UChar32 symbol_nth_codepoint_as_uchar32(t_symbol *sym, long index);
t_symbol *symbol_nth_codepoint(t_symbol *in, long index);
char symbol_slice_at_codepoint(t_symbol *sym, long index, t_symbol **left_out, t_symbol **right_out);

t_symbol *symbol_to_upper_case(t_symbol *sym, const char *locale);
t_symbol *symbol_to_lower_case(t_symbol *sym, const char *locale);
t_symbol *symbol_to_title_case(t_symbol *sym, const char *locale);
t_symbol *symbol_fold_case(t_symbol *sym, const char *locale);
t_symbol *symbol_capitalize(t_symbol *sym, const char *locale, t_symbol *non_separating_chars);

t_symbol *symbol_normalize(t_symbol *sym, long mode);

char atoms_compare(UCollator *coll, t_atom *av1, t_atom *av2);

void warn_if_ac_greater_than_one(t_sy_object *x, long ac);
t_symbol *category_to_symbol(UCharCategory category);


t_symbol *symbol_rotate(t_symbol *sym, long shift);
void atom_array_rotate(long ac, t_atom *av, long shift);

t_symbol *symbol_reverse(t_symbol *sym);
void atom_array_reverse(long ac, t_atom *av);

t_symbol *symbol_pad(t_symbol *sym, long output_length, char align, e_sy_pad_mode mode, long num_loop_elems, t_symbol *reservoir, char allow_trimming, char rounding_direction);
long pad_fn(t_sy_object *x, t_atom *atom_in, t_atom *atom_out, void *params, void *dummy, void *dummy2);

t_symbol *symbol_insert(t_symbol *orig, long position, t_symbol *insertion, t_symbol *pad_elem, long *shift_positions, long num_shift_positions);
t_symbol *symbol_substitute(t_symbol *orig, long position, t_symbol *replacement, t_symbol *pad_elem, long input_segment_length, long *shift_positions, long num_shift_positions);

void atom_array_scramble(long ac, t_atom *av);
t_symbol *symbol_scramble(t_symbol *sym);

char symbol_permute(t_symbol *s, t_symbol ***out_symlist, long *sym_len, char only_unique);
t_symbol *symbol_join(t_symbol *sym1, t_symbol *sym2);
t_symbol *symbol_replace_regexp(t_symbol *s, t_symbol *search, t_symbol *replace);
t_symbol *symbol_replace_easy(t_symbol *s, t_symbol *search, t_symbol *replace);

t_symbol *symbol_from_gimme(long ac, t_atom *av);

long atom_array_join(long ac1, t_atom *av1, long ac2, t_atom *av2, t_atom **out_av);
long symbol_to_atom_array(t_symbol *s, t_atom **out_av);

void atom_convert_symbol_to_number(t_atom *av);
char symbol_is_numeric(t_symbol *sym);
void syobj_atom_array_reparse_account_for_numout(t_sy_object *x, long ac, t_atom *av);
void syobj_atom_array_reparse_account_for_listout(t_sy_object *x, long *ac, t_atom **av);
