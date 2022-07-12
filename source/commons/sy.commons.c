/**
	@file
	sy.commons.c
	Common utilities for sy library

	by Daniele Ghisi
*/

#include "sy.commons.h"							// standard Max include, always required

// if *new_av is NULL it'll be automatically allocated.
long iterate_on_gimme(t_sy_object *x, t_symbol *msg, long ac, t_atom *av, t_atom **new_av, atom_modif_fn modif_fn, void *data1, void *data2, void *data3)
{
	long new_ac = ac;
	long cur = 0, i;
	
	if (msg && msg != gensym("") && msg != _sym_list) 
		new_ac += 1;
	
	if (new_ac == 0) 
		return 0;
	
	if (new_av && !*new_av) 
		*new_av = (t_atom *)sysmem_newptr(new_ac * sizeof(t_atom));
	
	if (msg && msg != gensym("") && msg != _sym_list) {
		t_atom temp;
		atom_setsym(&temp, msg);
		if ((modif_fn)(x, &temp, &((*new_av)[cur]), data1, data2, data3))
			cur++;
	}
	
	t_atom *cur_av = av;
	for (i = 0; i < ac; i++, cur_av++)
		if ((modif_fn)(x, cur_av, &((*new_av)[cur]), data1, data2, data3))
			cur++;

	if (cur < new_ac) {
		// something has been dropped, we resize the final pointer
		new_ac = cur;
		if (new_ac == 0) {
			sysmem_freeptr(*new_av);
			*new_av = NULL;
			return 0;
		}
		*new_av = (t_atom *) sysmem_resizeptr(*new_av, new_ac * sizeof(t_atom));
	}
	
	return new_ac;
}


UChar *symbol_to_uchar_array(t_symbol *sym, int32_t *out_size) {
	long len_sym = strlen(sym->s_name);
	//the number of UTF-16 code units is not larger than that of UTF-8 code
	//units, + 1 for the terminator, so this prealloc_size should ALWAYS suffice
	long prealloc_size = len_sym + 1;
	UErrorCode status = U_ZERO_ERROR;
	int32_t needed_size = 0;

	UChar *output_buffer = (UChar *) sysmem_newptrclear(sizeof (UChar) * prealloc_size); // so it's 0-terminated
	u_strFromUTF8WithSub(output_buffer, prealloc_size, &needed_size, sym->s_name, len_sym, 0xFFFD, NULL, &status);

    /* always allocate 1 character more than neccesary, this ensures that
     * u_strFromUTF8WithSub() will write a zero-terminated string. */
    if (++needed_size > prealloc_size) {
        sysmem_freeptr(output_buffer);
        output_buffer = (UChar *) sysmem_newptrclear(sizeof (UChar) * needed_size);
        status = U_ZERO_ERROR;
		u_strFromUTF8WithSub(output_buffer, needed_size, NULL, sym->s_name, len_sym, 0xFFFD, NULL, &status);
    }
	
    if (U_FAILURE(status)) {
        sysmem_freeptr(output_buffer);
		output_buffer = NULL;
    }	
	
	if (out_size)
		*out_size = needed_size - 1; // last one was the terminator
	
	return output_buffer;
}

t_symbol *concat_symbols(t_symbol *sym1, t_symbol *sym2)
{
	if (!sym1)
		return sym2;
	
	if (!sym2)
		return sym1;
	
	long len1 = strlen(sym1->s_name);
	long len2 = strlen(sym2->s_name);
	char *buf = (char *)sysmem_newptr((len1 + len2 + 1) * sizeof(char));
	t_symbol *out_sym;
	
	strncpy(buf, sym1->s_name, len1);
	strncpy(buf + len1, sym2->s_name, len2);
	buf[len1 + len2] = 0;
	
	out_sym = gensym(buf);
	sysmem_freeptr(buf);
	return out_sym;
}

t_symbol *symbol_from_uchar_array(UChar *buffer, int32_t size)
{
	
	if (size < 0)
		size = u_strlen(buffer);
		
	if (size == 0)
		return gensym("");
	
	//the number of UTF-8 code units is not larger than that of UTF-16 code
	//units * 3 + 1 for the terminator
	int32_t upper_bound_output_size = size * 3 + 1;
	int32_t actual_output_len;
	UErrorCode status = U_ZERO_ERROR;
	char *output_buffer = (char *) sysmem_newptr(upper_bound_output_size * sizeof (char));
	u_strToUTF8WithSub(output_buffer, upper_bound_output_size - 1, &actual_output_len, buffer, size, 0xFFFD, NULL, &status);
	
	output_buffer[upper_bound_output_size-1] = 0; // null terminated, always
    
	if (U_FAILURE(status)) {
        sysmem_freeptr(output_buffer);
        return gensym("");
    }	
	
	t_symbol *out_sym = gensym(output_buffer);
	sysmem_freeptr(output_buffer);
	return out_sym;
}

UChar *uchar_array_from_uchar32_array(UChar32 *source, int32_t source_size, int32_t *output_size)
{
	//the number of UTF-16 code units is not larger than that of UTF-32 code
	//units * 3 + 1 for the terminator (IS THIS TRUE?!?!?!?)
	int32_t upper_bound_output_size = source_size * 3 + 1;
	int32_t actual_output_len;
	UErrorCode status = U_ZERO_ERROR;
	UChar *output_buffer = (UChar *) sysmem_newptrclear(upper_bound_output_size * sizeof (UChar)); // so it's 0-terminated
	u_strFromUTF32(output_buffer, upper_bound_output_size - 1, &actual_output_len, source, source_size, &status);

	if (output_size)
		*output_size = actual_output_len;
	
    if (U_FAILURE(status)) {
        sysmem_freeptr(output_buffer);
        return NULL;
    }	
	return output_buffer;
}

UChar32 *uchar_array_to_uchar32_array(UChar *source, int32_t source_size, int32_t *output_size)
{
	int32_t upper_bound_output_size = source_size + 1; // for the terminator
	int32_t actual_output_len;
	UErrorCode status = U_ZERO_ERROR;
	UChar32 *output_buffer = (UChar32 *) sysmem_newptrclear(upper_bound_output_size * sizeof (UChar32)); // so it's 0-terminated
	u_strToUTF32(output_buffer, upper_bound_output_size - 1, &actual_output_len, source, source_size, &status);

	if (output_size)
		*output_size = actual_output_len;
	
    if (U_FAILURE(status)) {
        sysmem_freeptr(output_buffer);
        return NULL;
    }	
	return output_buffer;
}

UChar32 *symbol_to_uchar32_array(t_symbol *sym, int32_t *out_size) {
	int32_t size_temp, output_size;
	UChar *temp = symbol_to_uchar_array(sym, &size_temp);
	if (temp) {
		UChar32 *output = uchar_array_to_uchar32_array(temp, size_temp, &output_size);
		if (output && output_size && out_size)
			*out_size = output_size;
		sysmem_freeptr(temp);
		return output;
	}
	return NULL;
}


t_symbol *symbol_from_uchar32_array(UChar32 *source, int32_t source_size) {
	int32_t size_temp;
	UChar *temp = uchar_array_from_uchar32_array(source, source_size, &size_temp);
	if (temp) {
		t_symbol *output = symbol_from_uchar_array(temp, size_temp); 
		sysmem_freeptr(temp);
		return output;
	}
	return NULL;
}

t_symbol *symbol_to_upper_lower_title_or_fold_case(t_symbol *sym, const char *locale, e_sy_case_modes mode)
{
	if (!sym || !sym->s_name || !(strlen(sym->s_name)))
		return gensym("");
	
	UErrorCode errorCode = U_ZERO_ERROR;
	int32_t srcLength;
	UChar *buffer = symbol_to_uchar_array(sym, &srcLength);
	int32_t output_length;
	
	switch (mode) {
		case SY_CASE_MODE_LOWER:
			output_length = u_strToLower(buffer, srcLength, buffer, srcLength, locale, &errorCode);
			break;
		case SY_CASE_MODE_TITLE:
			output_length = u_strToTitle(buffer, srcLength, buffer, srcLength, NULL, locale, &errorCode);
			break;
		case SY_CASE_MODE_FOLD:
			output_length = u_strFoldCase(buffer, srcLength, buffer, srcLength, U_FOLD_CASE_DEFAULT, &errorCode);
			break;
		default:
			output_length = u_strToUpper(buffer, srcLength, buffer, srcLength, locale, &errorCode);
			break;
	}
	
	if (U_FAILURE(errorCode) || buffer[output_length]!=0) {
		dev_post("Conversion failed! Error: %s", u_errorName(errorCode));
	}
	
	t_symbol *res = symbol_from_uchar_array(buffer, output_length);
	sysmem_freeptr(buffer);
	return res;
}


t_symbol *symbol_to_upper_case(t_symbol *sym, const char *locale)
{
	return symbol_to_upper_lower_title_or_fold_case(sym, locale, SY_CASE_MODE_UPPER);
}

t_symbol *symbol_to_lower_case(t_symbol *sym, const char *locale)
{
	return symbol_to_upper_lower_title_or_fold_case(sym, locale, SY_CASE_MODE_LOWER);
}

t_symbol *symbol_to_title_case(t_symbol *sym, const char *locale)
{
	return symbol_to_upper_lower_title_or_fold_case(sym, locale, SY_CASE_MODE_TITLE);
}

t_symbol *symbol_fold_case(t_symbol *sym, const char *locale)
{
	return symbol_to_upper_lower_title_or_fold_case(sym, locale, SY_CASE_MODE_FOLD);
}


t_symbol *switch_case(t_symbol *sym)
{
	if (!sym || !sym->s_name || !(strlen(sym->s_name)))
		return gensym("");
	
	int32_t size, uchar_out_size;
	UChar *buffer = symbol_to_uchar_array(sym, &size);
	UChar32 *uchar32_res = (UChar32 *)sysmem_newptr(size * sizeof(UChar32));
	int32_t i;
	
	for (i = 0; i < size; i++) 
		uchar32_res[i] = u_islower(buffer[i]) ? u_toupper(buffer[i]) : u_tolower(buffer[i]);
	
	UChar *uchar_res = uchar_array_from_uchar32_array(uchar32_res, size, &uchar_out_size);
	t_symbol *res = symbol_from_uchar_array(uchar_res, uchar_out_size);
	sysmem_freeptr(buffer);
	sysmem_freeptr(uchar32_res);
	sysmem_freeptr(uchar_res);
	return res;
}


t_symbol *change_sym_case(t_symbol *sym, e_sy_case_modes mode, const char *locale, t_symbol *non_separating_chars)
{
	switch (mode) {
		case SY_CASE_MODE_UPPER:
			return symbol_to_upper_case(sym, locale);
		case SY_CASE_MODE_LOWER:
			return symbol_to_lower_case(sym, locale);
		case SY_CASE_MODE_TITLE:
			return symbol_to_title_case(sym, locale);
		case SY_CASE_MODE_SWITCH:
			return switch_case(sym);
		case SY_CASE_MODE_FOLD:
			return symbol_fold_case(sym, locale);
		default:
			return sym;
	}
	return sym;
}

long strength_attribute_to_ICU_flag(t_sy_object *x, long strength)
{
	switch (strength) {
		case 0: return UCOL_DEFAULT;
		case 1: return UCOL_PRIMARY;
		case 2: return UCOL_SECONDARY;
		case 3: return UCOL_TERTIARY;
		case 4: return UCOL_QUATERNARY;
		case 5: return UCOL_IDENTICAL;
		default: return UCOL_TERTIARY;
	}
}



long change_case_fn(t_sy_object *x, t_atom *atom_in, t_atom *atom_out, void *change_case_mode, void *locale, void *non_separating_chars)
{
	char type_in = atom_gettype(atom_in); 

	if (type_in == A_SYM) {
		atom_setsym(atom_out, change_sym_case(atom_getsym(atom_in), (e_sy_case_modes) *((long *)change_case_mode), *((char **)locale), *((t_symbol **)non_separating_chars)));
	} else if (type_in == A_LONG || type_in == A_FLOAT) {
		*atom_out = *atom_in;
	} else {
		return 0;
	}

	return 1;
}

t_symbol *symbol_normalize(t_symbol *sym, long mode)
{
	if (!sym || !sym->s_name || !(strlen(sym->s_name)))
		return gensym("");
	
	UNormalizationMode umode = UNORM_NONE;
	UErrorCode errcode = U_ZERO_ERROR;
	int32_t srcLength;
	UChar *buffer = symbol_to_uchar_array(sym, &srcLength);
	UChar *result = (UChar *)sysmem_newptr(srcLength * 6 * sizeof(UChar)); // should always be enough.
	int32_t output_length;
	
	switch (mode) {
		case 1: umode = UNORM_NFD; break;
		case 2: umode = UNORM_NFKD; break;
		case 3: umode = UNORM_NFC; break;
		case 4: umode = UNORM_NFKC; break;
		case 5: umode = UNORM_FCD; break;
		default: break;
	}

	output_length = unorm_normalize(buffer, srcLength, umode, 0, result, srcLength * 6 - 1, &errcode);
	
	if (U_FAILURE(errcode) || buffer[output_length]!=0) {
		dev_post("Normalization failed! Error: %s", u_errorName(errcode));
	}
	
	t_symbol *res = symbol_from_uchar_array(result, output_length);
	sysmem_freeptr(buffer);
	sysmem_freeptr(result);
	return res;
}

long normalize_fn(t_sy_object *x, t_atom *atom_in, t_atom *atom_out, void *change_case_mode, void *dummy, void *dummy2)
{
	char type_in = atom_gettype(atom_in); 
	
	if (type_in == A_SYM) {
		atom_setsym(atom_out, symbol_normalize(atom_getsym(atom_in), *((long *)change_case_mode)));
	} else if (type_in == A_LONG || type_in == A_FLOAT) {
		*atom_out = *atom_in;
	} else {
		return 0;
	}
	
	return 1;
}



t_symbol *convert_sym(t_symbol *sym, UConverter *conv, long direction)
{
    if (!sym || !sym->s_name || !(strlen(sym->s_name)))
        return gensym("");
    
    UErrorCode errorCode = U_ZERO_ERROR;
    
    // Converting to ASCII, or whatever your terminal supports.
    int32_t srcLength;
    t_symbol *converted_sym = sym;
    

    // Pass the actual target buffer size, not some arbitrary number.
    if (direction > 0) { // from unicode to something else
        // Compute target capacity as recommended in the ICU reference.
        // Alternatively, you could pre-flight the conversion to get the
        // actual buffer size needed.
        UChar *buffer = symbol_to_uchar_array(sym, &srcLength);
        int32_t targetCap = UCNV_GET_MAX_BYTES_FOR_STRING(srcLength, ucnv_getMaxCharSize(conv));
        char *target = (char *)sysmem_newptr(targetCap * sizeof(char));
        
        ucnv_fromUChars(conv, target, targetCap, buffer, srcLength, &errorCode);
        
        if (errorCode != U_ZERO_ERROR) {
            error("Error during conversion: %s", u_errorName(errorCode));
        } else
            converted_sym = gensym(target);
        sysmem_freeptr(target);
    } else { // from something else to unicode
        int32_t targetCap = strlen(sym->s_name) * 6 + 1;
        UChar *target = (UChar *)sysmem_newptr(targetCap * sizeof(UChar));
        ucnv_toUChars(conv, target, targetCap, sym->s_name, strlen(sym->s_name), &errorCode);
        converted_sym = symbol_from_uchar_array(target, u_strlen(target));
    }
    
    
    
    return converted_sym;
    
}



long convert_fn(t_sy_object *x, t_atom *atom_in, t_atom *atom_out, void *converter, void *direction, void *dummy2)
{
    char type_in = atom_gettype(atom_in);
    long dir = *((long *)direction);
    
    if (type_in == A_SYM) {
        atom_setsym(atom_out, convert_sym(atom_getsym(atom_in), (UConverter *)converter, dir));
    } else if (type_in == A_LONG || type_in == A_FLOAT) {
        *atom_out = *atom_in;
    } else {
        return 0;
    }
    
    return 1;
}



t_symbol *transform_sym(t_symbol *sym, UTransliterator *trans)
{
    if (!sym || !sym->s_name || !(strlen(sym->s_name)))
        return gensym("");
    
    UErrorCode errorCode = U_ZERO_ERROR;
    
    int32_t srcLength;
    UChar *buffer = symbol_to_uchar_array(sym, &srcLength);
    UChar *buffer_orig = symbol_to_uchar_array(sym, &srcLength);
    int32_t srcLength_orig = srcLength;
    t_symbol *converted_sym = sym;
    
    
    int32_t targetCap = srcLength * 6 + 1; // NOT SURE IF THIS WILL ALWAYS BE ENOUGH
    buffer = (UChar *)sysmem_resizeptr(buffer, targetCap * sizeof(UChar));
    
    int32_t limit = srcLength;
    utrans_transUChars(trans, buffer, &srcLength, targetCap, 0, &limit, &errorCode);
    
    while ((errorCode == U_BUFFER_OVERFLOW_ERROR || errorCode == U_STRING_NOT_TERMINATED_WARNING) && limit >= targetCap) {
        targetCap = limit+1;
        buffer = (UChar *)sysmem_resizeptr(buffer, targetCap * sizeof(UChar));
        sysmem_copyptr(buffer_orig, buffer, srcLength_orig * sizeof(UChar));
        buffer[srcLength_orig] = 0;
        srcLength = srcLength_orig;
        limit = srcLength;
        errorCode = U_ZERO_ERROR;
        utrans_transUChars(trans, buffer, &srcLength, targetCap, 0, &limit, &errorCode);
    }
    
    if (errorCode != U_ZERO_ERROR) {
        error("Error during processing: %s", u_errorName(errorCode));
    } else
        converted_sym = symbol_from_uchar_array(buffer, -1);
    
    sysmem_freeptr(buffer);
    
    return converted_sym;
    
}



long transform_fn(t_sy_object *x, t_atom *atom_in, t_atom *atom_out, void *transformer, void *dummy1, void *dummy2)
{
    char type_in = atom_gettype(atom_in);
    
    if (type_in == A_SYM) {
        atom_setsym(atom_out, transform_sym(atom_getsym(atom_in), (UTransliterator *)transformer));
    } else if (type_in == A_LONG || type_in == A_FLOAT) {
        *atom_out = *atom_in;
    } else {
        return 0;
    }
    
    return 1;
}










char is_utf8_byte_leading(unsigned char ch)
{
	// if our byte starts with (10)_2, it is a trailing byte for UTF-8
	return ((ch >> 6) != 2);
}

char is_utf16_surrogate_leading(t_uint32 ch)
{
	// if our byte starts with (110111)_2, it is a trailing surrogate for UTF-16
	return ((ch >> 10) != 0x37);
}

int32_t symbol_get_num_codepoints_fast(t_symbol *sym)
{
	if (!sym)
		return 0;

	long count = 0;
	long i, len = strlen(sym->s_name);
	char *cur = sym->s_name;
	for (i = 0; i < len; i++, cur++)
		if (is_utf8_byte_leading(*cur))
			count++;

	return count;
}

int32_t symbol_get_num_codepoints(t_symbol *sym, char also_count_nonstandard)
{
	if (!sym)
		return 0;
	
	// converting to UTF-16....
	UErrorCode status = U_ZERO_ERROR;
	long len = strlen(sym->s_name);
	UChar *symstr16 = (UChar *) sysmem_newptrclear((len + 1) * sizeof(UChar));
	UChar32 *symstr32 = (UChar32 *) sysmem_newptrclear((len + 1) * sizeof(UChar32));
	int32_t actual_len_16, actual_len_32;

	u_strFromUTF8(symstr16, len+1, &actual_len_16, sym->s_name, -1, &status); 

    if (U_FAILURE(status)) {
        sysmem_freeptr(symstr16);
        sysmem_freeptr(symstr32);
		return 0;
    }
	
	// ...then to UTF-32
	u_strToUTF32(symstr32, len+1, &actual_len_32, symstr16, actual_len_16, &status);

    if (!also_count_nonstandard) {
        int32_t i, count = 0;
        UChar32 *temp = symstr32;
        for (i = 0; i < actual_len_32; i++, temp++) {
            int8_t type = u_charType(*temp);
            switch (type) {
                case U_UNASSIGNED:
                case U_NON_SPACING_MARK:
                case U_ENCLOSING_MARK:
                case U_COMBINING_SPACING_MARK:
                case U_LINE_SEPARATOR:
                case U_PARAGRAPH_SEPARATOR:
                case U_CONTROL_CHAR:
                case U_FORMAT_CHAR:
                case U_PRIVATE_USE_CHAR:
                case U_SURROGATE:
                case U_MODIFIER_SYMBOL:
                case U_MODIFIER_LETTER:
                    break;
                    
                case U_SPACE_SEPARATOR:
                case U_UPPERCASE_LETTER:
                case U_LOWERCASE_LETTER:
                case U_TITLECASE_LETTER:
                case U_OTHER_LETTER:
                case U_DECIMAL_DIGIT_NUMBER:
                case U_LETTER_NUMBER:
                case U_OTHER_NUMBER:
                case U_DASH_PUNCTUATION:
                case U_START_PUNCTUATION:
                case U_END_PUNCTUATION:
                case U_CONNECTOR_PUNCTUATION:
                case U_OTHER_PUNCTUATION:
                case U_MATH_SYMBOL:
                case U_CURRENCY_SYMBOL:
                case U_OTHER_SYMBOL:
                case U_INITIAL_PUNCTUATION:
                case U_FINAL_PUNCTUATION:
                    count++;
                    break;
            }
            
        }
        actual_len_32 = count;
    }
	
	sysmem_freeptr(symstr16);
	sysmem_freeptr(symstr32);

	return actual_len_32;
}

// index is 1-based
t_symbol *symbol_nth_codepoint(t_symbol *sym, long index) 
{
	if (!sym || index == 0)
		return NULL;

	long num_codepoints = symbol_get_num_codepoints_fast(sym);
	
	// parsing negative indices (= "reading backward")
	if (index < 0)
		index += num_codepoints + 1;
	
	if (index <= 0 || index > num_codepoints)
		return NULL;
	
	char *res = sysmem_newptr(7 * sizeof(char)); // up to 6 bytes are needed, then a zero terminator
	t_symbol *output = NULL;
	long count_codepoints = 0, count_bytes = 0;
	long i, len = strlen(sym->s_name);
	char *cur = sym->s_name;
	for (i = 0; i < len; i++, cur++) {
		if (is_utf8_byte_leading(*cur)) {
			
			if (count_bytes > 0)
				break;
			
			count_codepoints++;
			if (count_codepoints == index) 
				res[count_bytes++] = *cur;
		} else if (count_bytes > 0 && count_bytes < 6) {
			res[count_bytes++] = *cur;
		}
	}
	res[count_bytes] = 0;
	output = gensym(res);
	sysmem_freeptr(res);

	return output;
}


UChar32 symbol_nth_codepoint_as_uchar32(t_symbol *sym, long index) 
{
	if (!sym)
		return 0;

	long num_codepoints = symbol_get_num_codepoints_fast(sym);
	
	// parsing negative indices (= "reading backward")
	if (index < 0)
		index += num_codepoints + 1;
	
	if (index <= 0 || index > num_codepoints)
		return 0;

	UChar32 *buf = symbol_to_uchar32_array(sym, NULL);
	UChar32 res = buf[index - 1];
	sysmem_freeptr(buf);
	return res;
}

// returns 0 if error, 1 otherwise
char symbol_slice_at_codepoint(t_symbol *sym, long index, t_symbol **left_out, t_symbol **right_out) 
{
	if (!sym) { 
		*left_out = *right_out = NULL;
		return 0;
	}
	
	long num_codepoints = symbol_get_num_codepoints_fast(sym);
	
	// parsing negative indices (= "reading backward")
	if (index < 0)
		index += num_codepoints;
	
	long i, len = strlen(sym->s_name);
	
	if (len == 0) {
		*left_out = *right_out = NULL;
		return 0;
	}
	
	char *left = sysmem_newptr((len + 1) * sizeof(char));
	char *right = sysmem_newptr((len + 1) * sizeof(char));
	long count_codepoints = 0;
	char *cur = sym->s_name;
	char we_are_in_left_part = true;
	char count_left = 0, count_right = 0;
	char *cur_left = left, *cur_right = right;
	
	*cur_left = *cur_right = 0;
	
	for (i = 0; i < len; i++, cur++) {
		if (is_utf8_byte_leading(*cur))
			count_codepoints++;
		
		if (we_are_in_left_part && count_codepoints > index)
			we_are_in_left_part = false;
		
		if (we_are_in_left_part) {
			*cur_left++ = *cur;
			count_left++;
		} else {
			*cur_right++ = *cur;
			count_right++;
		}
	}
	*cur_left = 0;
	*cur_right = 0;
	
	*left_out = gensym(left);
	*right_out = gensym(right);
	
	sysmem_freeptr(left);
	sysmem_freeptr(right);
	
	return 1;
}

void warn_if_ac_greater_than_one(t_sy_object *x, long ac)
{
	if (ac > 1)
		object_warn((t_object *)x, "Warning: list elements after the first one are ignored.");
}

t_symbol *category_to_symbol(UCharCategory category)
{
	switch (category) {
		/** Cn "Other, Not Assigned (no characters in [UnicodeData.txt] have this property)" (same as U_UNASSIGNED!) @stable ICU 2.0 */
		case U_GENERAL_OTHER_TYPES:	return gensym("Cn");
		/** Lu @stable ICU 2.0 */
		case U_UPPERCASE_LETTER: return gensym("Lu");
		/** Ll @stable ICU 2.0 */
		case U_LOWERCASE_LETTER: return gensym("Ll");
		/** Lt @stable ICU 2.0 */
		case U_TITLECASE_LETTER: return gensym("Lt");
		/** Lm @stable ICU 2.0 */
		case U_MODIFIER_LETTER: return gensym("Lm");
		/** Lo @stable ICU 2.0 */
		case U_OTHER_LETTER: return gensym("Lo");
		/** Mn @stable ICU 2.0 */
		case U_NON_SPACING_MARK: return gensym("Mn");
		/** Me @stable ICU 2.0 */
		case U_ENCLOSING_MARK: return gensym("Me");
		/** Mc @stable ICU 2.0 */
		case U_COMBINING_SPACING_MARK: return gensym("Mc");
		/** Nd @stable ICU 2.0 */
		case U_DECIMAL_DIGIT_NUMBER: return gensym("Nd");
		/** Nl @stable ICU 2.0 */
		case U_LETTER_NUMBER: return gensym("Nl");
		/** No @stable ICU 2.0 */
		case U_OTHER_NUMBER: return gensym("No");
		/** Zs @stable ICU 2.0 */
		case U_SPACE_SEPARATOR: return gensym("Zs");
		/** Zl @stable ICU 2.0 */
		case U_LINE_SEPARATOR: return gensym("Zl");
		/** Zp @stable ICU 2.0 */
		case U_PARAGRAPH_SEPARATOR: return gensym("Zp");
		/** Cc @stable ICU 2.0 */
		case U_CONTROL_CHAR: return gensym("Cc");
		/** Cf @stable ICU 2.0 */
		case U_FORMAT_CHAR: return gensym("Cf");
		/** Co @stable ICU 2.0 */
		case U_PRIVATE_USE_CHAR: return gensym("Co");
		/** Cs @stable ICU 2.0 */
		case U_SURROGATE: return gensym("Cs");
		/** Pd @stable ICU 2.0 */
		case U_DASH_PUNCTUATION: return gensym("Pd");
		/** Ps @stable ICU 2.0 */
		case U_START_PUNCTUATION: return gensym("Ps");
		/** Pe @stable ICU 2.0 */
		case U_END_PUNCTUATION: return gensym("Pe");
		/** Pc @stable ICU 2.0 */
		case U_CONNECTOR_PUNCTUATION: return gensym("Pc");
		/** Po @stable ICU 2.0 */
		case U_OTHER_PUNCTUATION: return gensym("Po");
		/** Sm @stable ICU 2.0 */
		case U_MATH_SYMBOL: return gensym("Sm");
		/** Sc @stable ICU 2.0 */
		case U_CURRENCY_SYMBOL: return gensym("Sc");
		/** Sk @stable ICU 2.0 */
		case U_MODIFIER_SYMBOL: return gensym("Sk");
		/** So @stable ICU 2.0 */
		case U_OTHER_SYMBOL: return gensym("So");
		/** Pi @stable ICU 2.0 */
		case U_INITIAL_PUNCTUATION: return gensym("Pi");
		/** Pf @stable ICU 2.0 */
		case U_FINAL_PUNCTUATION: return gensym("Pf");
		default: return gensym("Cn");
	}
}

char atoms_compare(UCollator *coll, t_atom *av1, t_atom *av2)
{			
	long type1 = atom_gettype(av1), type2 = atom_gettype(av2);
	
	char res = UCOL_EQUAL;
	if (type1 == A_SYM && type2 == A_SYM) { 
		// comparing two symbols
		if (ucol_getStrength(coll) > 0) {
			UChar *buf1 = symbol_to_uchar_array(atom_getsym(av1), NULL);
			UChar *buf2 = symbol_to_uchar_array(atom_getsym(av2), NULL);
			res = ucol_strcoll(coll, buf1, -1, buf2, -1);
			sysmem_freeptr(buf1);
			sysmem_freeptr(buf2);
		}
		
	} else if (type1 == A_SYM) {
		res = UCOL_GREATER; // symbols are by default greater than numbers
	} else if (type2 == A_SYM) {
		res = UCOL_LESS; // symbols are by default greater than numbers
	} else {
		// comparing two numbers
		t_atom_float fl1 = atom_getfloat(av1);
		t_atom_float fl2 = atom_getfloat(av2);
		res = (fl1 < fl2 ? UCOL_LESS : (fl1 > fl2 ? UCOL_GREATER : UCOL_EQUAL));
	}
	return res;
}

t_symbol *symbol_reverse(t_symbol *sym)
{
	t_symbol *out_sym = NULL;
	long i;
	int32_t out_size = 0;
	UChar32 *buf = symbol_to_uchar32_array(sym, &out_size);
	UChar32 temp;
	long limit = out_size/2;
	for (i = 0; i < limit; i++) {
		temp = buf[out_size - i - 1];
		buf[out_size - i - 1] = buf[i];
		buf[i] = temp;
	}
	out_sym = symbol_from_uchar32_array(buf, out_size);
	sysmem_freeptr(buf);
	return out_sym;
}

void atom_array_reverse(long ac, t_atom *av)
{
	if (ac == 0)
		return;

	long i;
	t_atom temp;
	long limit = ac/2;
	for (i = 0; i < limit; i++) {
		temp = av[ac - i - 1];
		av[ac - i - 1] = av[i];
		av[i] = temp;
	}
}

t_symbol *symbol_rotate(t_symbol *sym, long shift)
{
	t_symbol *out_sym = sym;
	int32_t out_size = 0;
	UChar32 *buf = symbol_to_uchar32_array(sym, &out_size);
	
	if (out_size == 0)
		return out_sym;
	
	while (shift < 0)
		shift += out_size;

	shift %= out_size;
	
	if (shift > 0) {
		UChar32 *temp = (UChar32 *)sysmem_newptr(shift * sizeof(UChar32)); // not null terminated, but who cares
		sysmem_copyptr(buf, temp, shift * sizeof(UChar32));
		sysmem_copyptr(buf + shift, buf, (out_size - shift) * sizeof(UChar32));
		sysmem_copyptr(temp, buf + out_size - shift, shift * sizeof(UChar32));
		out_sym = symbol_from_uchar32_array(buf, out_size);
		sysmem_freeptr(temp);
	}
	sysmem_freeptr(buf);
	return out_sym;
}

void atom_array_rotate(long ac, t_atom *av, long shift)
{
	if (ac == 0)
		return;
	
	while (shift < 0) 
		shift += ac;
	shift %= ac;

	if (shift > 0) {
		t_atom *temp = (t_atom *)sysmem_newptr(shift * sizeof(t_atom));
		sysmem_copyptr(av, temp, shift * sizeof(t_atom));
		sysmem_copyptr(av + shift, av, (ac - shift) * sizeof(t_atom));
		sysmem_copyptr(temp, av + ac - shift, shift * sizeof(t_atom));
		sysmem_freeptr(temp);
	}
}


t_symbol *symbol_insert(t_symbol *orig, long position, t_symbol *insertion, t_symbol *pad_elem, long *shift_positions, long num_shift_positions)
{
    if (!orig)
        return NULL;
    
    t_symbol *out_sym = orig;
    int32_t orig_buf_size = 0, insertion_buf_size = 0, pad_elem_buf_size = 0;

    UChar32 *insertion_buf = symbol_to_uchar32_array(insertion, &insertion_buf_size);

    if (insertion_buf_size == 0) {
        sysmem_freeptr(insertion_buf);
        return orig;
    }

    UChar32 *orig_buf = symbol_to_uchar32_array(orig, &orig_buf_size);
    UChar32 *padelem_buf = pad_elem ? symbol_to_uchar32_array(pad_elem, &pad_elem_buf_size) : NULL;
    long i, j, s;
    

    long left_diff = 0, right_diff = 0;
    right_diff = (position - orig_buf_size - 1);
    if (right_diff < 0)
        right_diff = 0;
    
    if (position <= 0) {
        left_diff = -position + 1;
        if (left_diff < 0)
            left_diff = 0;
    }
    
    if (left_diff + right_diff > 0) {
        if (padelem_buf && pad_elem_buf_size > 0) {
            orig_buf = (UChar32 *)sysmem_resizeptr(orig_buf, (orig_buf_size + left_diff + right_diff) * sizeof(UChar32));
            if (left_diff > 0) {
                for (i = orig_buf_size - 1; i >= 0; i--)
                    orig_buf[i + left_diff] = orig_buf[i];
                for (i = 0; i < left_diff; i++)
                    orig_buf[i] = padelem_buf[0];
                orig_buf_size += left_diff;
                for (s = 0; s < num_shift_positions; s++)
                    shift_positions[s] += left_diff;
            }
            if (right_diff > 0) {
                for (i = orig_buf_size; i < orig_buf_size + right_diff; i++)
                    orig_buf[i] = padelem_buf[0];
                orig_buf_size += right_diff;
            }
        } else {
            position = position > 0 ? orig_buf_size + 1 : 1;
        }
    }
    
    

    // update shift_positions
    for (s = 0; s < num_shift_positions; s++)
        if (shift_positions[s] > position)
            shift_positions[s] += insertion_buf_size;

    position += left_diff;
    

    long out_buf_size = orig_buf_size += insertion_buf_size;
    UChar32 *out_buf = (UChar32 *)sysmem_newptr(out_buf_size * sizeof(UChar32));
    for (i = 0; i < position - 1; i++)
        out_buf[i] = orig_buf[i];
    for (; i < position - 1 + insertion_buf_size; i++)
        out_buf[i] = insertion_buf[i - (position - 1)];
    for (j = position - 1; i < out_buf_size && j < orig_buf_size; i++, j++)
        out_buf[i] = orig_buf[j];
    
    out_sym = symbol_from_uchar32_array(out_buf, out_buf_size);
    sysmem_freeptr(orig_buf);
    sysmem_freeptr(insertion_buf);
    sysmem_freeptr(out_buf);
    if (padelem_buf)
        sysmem_freeptr(padelem_buf);
    return out_sym;
}


t_symbol *symbol_substitute(t_symbol *orig, long position, t_symbol *replacement, t_symbol *pad_elem, long input_segment_length, long *shift_positions, long num_shift_positions)
{
    if (!orig)
        return NULL;

    t_symbol *out_sym = orig;
    int32_t orig_buf_size = 0, replacement_buf_size = 0, pad_elem_buf_size = 0;
    UChar32 *orig_buf = symbol_to_uchar32_array(orig, &orig_buf_size);
    UChar32 *replacement_buf = symbol_to_uchar32_array(replacement, &replacement_buf_size);
    UChar32 *padelem_buf = pad_elem ? symbol_to_uchar32_array(pad_elem, &pad_elem_buf_size) : NULL;
    long i, j, s;
    
    if (input_segment_length <= 0)
        input_segment_length = replacement_buf_size;
    
    long left_diff = 0, right_diff = 0;
    right_diff = (position + input_segment_length - orig_buf_size - 1);
    if (right_diff < 0)
        right_diff = 0;
    if (position <= 0) {
        left_diff = -position + 1;
        if (left_diff < 0)
            left_diff = 0;
    }
    
    
    if (left_diff + right_diff > 0) {
        if (padelem_buf && pad_elem_buf_size > 0) {
            orig_buf = (UChar32 *)sysmem_resizeptr(orig_buf, (orig_buf_size + left_diff + right_diff) * sizeof(UChar32));
            if (left_diff > 0) {
                for (i = orig_buf_size - 1; i >= 0; i--)
                    orig_buf[i + left_diff] = orig_buf[i];
                for (i = 0; i < left_diff; i++)
                    orig_buf[i] = padelem_buf[0];
                orig_buf_size += left_diff;
                for (s = 0; s < num_shift_positions; s++)
                    shift_positions[s] += left_diff;
            }
            if (right_diff > 0) {
                for (i = orig_buf_size; i < orig_buf_size + right_diff; i++)
                    orig_buf[i] = padelem_buf[0];
                orig_buf_size += right_diff;
            }
        } else {
            position = position > 0 ? orig_buf_size + 1 : 1;
        }
    }
    
    
    // update shift_positions
    for (s = 0; s < num_shift_positions; s++)
        if (shift_positions[s] > position)
            shift_positions[s] += (replacement_buf_size - input_segment_length);
    
    position += left_diff;

    long delta_chars = replacement_buf_size - input_segment_length;

    long out_buf_size = orig_buf_size + delta_chars;
    UChar32 *out_buf = (UChar32 *)sysmem_newptr(out_buf_size * sizeof(UChar32));
    for (i = 0; i < position - 1; i++)
        out_buf[i] = orig_buf[i];
    for (j = 0; i < out_buf_size && j < replacement_buf_size; i++, j++)
        out_buf[i] = replacement_buf[j];
    for (j = position - 1 + input_segment_length; i < out_buf_size && j < orig_buf_size; i++, j++)
        out_buf[i] = orig_buf[j];
    
    out_sym = symbol_from_uchar32_array(out_buf, out_buf_size);
    sysmem_freeptr(orig_buf);
    sysmem_freeptr(replacement_buf);
    sysmem_freeptr(out_buf);
    if (padelem_buf)
        sysmem_freeptr(padelem_buf);
    return out_sym;
}



/*

t_symbol *symbol_insert(t_symbol *orig, long position, t_symbol *insertion, t_symbol *pad_elem, long *shift_positions, long num_shift_positions)
{
    if (!orig)
        return NULL;
    
    t_symbol *out_sym = orig;
    int32_t orig_buf_size = 0, insertion_buf_size = 0, pad_elem_buf_size = 0;
    
    UChar32 *insertion_buf = symbol_to_uchar32_array(insertion, &insertion_buf_size);
    
    if (insertion_buf_size == 0 || position == 0) {
        sysmem_freeptr(insertion_buf);
        return orig;
    }
    
    UChar32 *orig_buf = symbol_to_uchar32_array(orig, &orig_buf_size);
    UChar32 *padelem_buf = pad_elem ? symbol_to_uchar32_array(pad_elem, &pad_elem_buf_size) : NULL;
    long i, j, s;
    
    
    long diff = (labs(position) - orig_buf_size - 1);
    if (diff > 0) {
        if (padelem_buf && pad_elem_buf_size > 0) {
            orig_buf = (UChar32 *)sysmem_resizeptr(orig_buf, (orig_buf_size + diff) * sizeof(UChar32));
            if (position > 0) {
                for (i = orig_buf_size; i < orig_buf_size + diff; i++)
                    orig_buf[i] = padelem_buf[0];
                for (s = 0; s < num_shift_positions; s++)
                    if (shift_positions[s] < 0)
                        shift_positions[s] -= diff;
            } else if (position < 0) {
                for (i = orig_buf_size - 1; i >= 0; i--)
                    orig_buf[i+diff] = orig_buf[i];
                for (i = 0; i < diff; i++)
                    orig_buf[i] = padelem_buf[0];
                for (s = 0; s < num_shift_positions; s++)
                    if (shift_positions[s] > 0)
                        shift_positions[s] += diff;
            }
            orig_buf_size += diff;
        } else {
            position = position > 0 ? orig_buf_size + 1 : 1;
        }
    }
    
    // update shift_positions
    if (position > 0) {
        for (s = 0; s < num_shift_positions; s++)
            if (shift_positions[s] > position)
                shift_positions[s] += insertion_buf_size;
    } else if (position < 0) {
        for (s = 0; s < num_shift_positions; s++)
            if (shift_positions[s] < position)
                shift_positions[s] -= insertion_buf_size;
    }
    
    if (position < 0)
        position = orig_buf_size + position + 2;
    
    
    long out_buf_size = orig_buf_size += insertion_buf_size;
    UChar32 *out_buf = (UChar32 *)sysmem_newptr(out_buf_size * sizeof(UChar32));
    for (i = 0; i < position - 1; i++)
        out_buf[i] = orig_buf[i];
    for (; i < position - 1 + insertion_buf_size; i++)
        out_buf[i] = insertion_buf[i - (position - 1)];
    for (j = position - 1; i < out_buf_size && j < orig_buf_size; i++, j++)
        out_buf[i] = orig_buf[j];
    
    out_sym = symbol_from_uchar32_array(out_buf, out_buf_size);
    sysmem_freeptr(orig_buf);
    sysmem_freeptr(insertion_buf);
    sysmem_freeptr(out_buf);
    if (padelem_buf)
        sysmem_freeptr(padelem_buf);
    return out_sym;
}


t_symbol *symbol_substitute(t_symbol *orig, long position, t_symbol *replacement, t_symbol *pad_elem, long input_segment_length, long *shift_positions, long num_shift_positions)
{
    if (!orig)
        return NULL;
    
    if (position == 0)
        return orig;
    
    t_symbol *out_sym = orig;
    int32_t orig_buf_size = 0, replacement_buf_size = 0, pad_elem_buf_size = 0;
    UChar32 *orig_buf = symbol_to_uchar32_array(orig, &orig_buf_size);
    UChar32 *replacement_buf = symbol_to_uchar32_array(replacement, &replacement_buf_size);
    UChar32 *padelem_buf = pad_elem ? symbol_to_uchar32_array(pad_elem, &pad_elem_buf_size) : NULL;
    long i, j, s;
    
    if (input_segment_length <= 0)
        input_segment_length = replacement_buf_size;
    
    
    long left_diff = 0, right_diff = 0;
    if (position > 0) {
        right_diff = (position + input_segment_length - orig_buf_size - 1);
        if (right_diff < 0)
            right_diff = 0;
    } else if (position < 0) {
        left_diff = ((-position) - orig_buf_size);
        if (left_diff < 0)
            left_diff = 0;
        if (labs(position) < input_segment_length)
            right_diff = input_segment_length - labs(position);
    }
    if (left_diff + right_diff > 0) {
        if (padelem_buf && pad_elem_buf_size > 0) {
            orig_buf = (UChar32 *)sysmem_resizeptr(orig_buf, (orig_buf_size + left_diff + right_diff) * sizeof(UChar32));
            if (left_diff > 0) {
                for (i = orig_buf_size - 1; i >= 0; i--)
                    orig_buf[i + left_diff] = orig_buf[i];
                for (i = 0; i < left_diff; i++)
                    orig_buf[i] = padelem_buf[0];
                orig_buf_size += left_diff;
                for (s = 0; s < num_shift_positions; s++)
                    if (shift_positions[s] > 0)
                        shift_positions[s] += left_diff;
            }
            if (right_diff > 0) {
                for (i = orig_buf_size; i < orig_buf_size + right_diff; i++)
                    orig_buf[i] = padelem_buf[0];
                orig_buf_size += right_diff;
                for (s = 0; s < num_shift_positions; s++)
                    if (shift_positions[s] < 0)
                        shift_positions[s] -= right_diff;
            }
        } else {
            position = position > 0 ? orig_buf_size + 1 : 1;
        }
    }
    
    
    // update shift_positions
    if (position > 0) {
        for (s = 0; s < num_shift_positions; s++)
            if (shift_positions[s] > position)
                shift_positions[s] += (replacement_buf_size - input_segment_length);
    } else if (position < 0) {
        for (s = 0; s < num_shift_positions; s++)
            if (shift_positions[s] < position)
                shift_positions[s] -= (replacement_buf_size - input_segment_length);
    }
    
    
    if (position < 0)
        position = (orig_buf_size - right_diff) + position + 1;
    
    long delta_chars = replacement_buf_size - input_segment_length;
    
    
    long out_buf_size = orig_buf_size + delta_chars;
    UChar32 *out_buf = (UChar32 *)sysmem_newptr(out_buf_size * sizeof(UChar32));
    for (i = 0; i < position - 1; i++)
        out_buf[i] = orig_buf[i];
    for (j = 0; i < out_buf_size && j < replacement_buf_size; i++, j++)
        out_buf[i] = replacement_buf[j];
    for (j = position - 1 + input_segment_length; i < out_buf_size && j < orig_buf_size; i++, j++)
        out_buf[i] = orig_buf[j];
    
    out_sym = symbol_from_uchar32_array(out_buf, out_buf_size);
    sysmem_freeptr(orig_buf);
    sysmem_freeptr(replacement_buf);
    sysmem_freeptr(out_buf);
    if (padelem_buf)
        sysmem_freeptr(padelem_buf);
    return out_sym;
}



*/



/* arrange the N elements of ARRAY in random order.
 * Only effective if N is much smaller than RAND_MAX;
 * if this may not be the case, use a better random
 * number generator. */
void shuffle_uchar32(UChar32 *array, long n)
{
    if (n > 1) 
    {
        long i;
        for (i = 0; i < n - 1; i++) 
        {
			long j = i + rand() / (RAND_MAX / (n - i) + 1);
			UChar32 t = array[j];
			array[j] = array[i];
			array[i] = t;
        }
    }
}

void shuffle_atoms(t_atom *array, long n)
{
    if (n > 1) 
    {
        long i;
        for (i = 0; i < n - 1; i++) 
        {
			long j = i + rand() / (RAND_MAX / (n - i) + 1);
			t_atom t = array[j];
			array[j] = array[i];
			array[i] = t;
        }
    }
}

t_symbol *symbol_scramble(t_symbol *sym)
{
	t_symbol *out_sym = sym;
	int32_t out_size = 0;
	UChar32 *buf = symbol_to_uchar32_array(sym, &out_size);
	
	if (out_size > 0) {
		shuffle_uchar32(buf, out_size);
		out_sym = symbol_from_uchar32_array(buf, out_size);
	}
	
	sysmem_freeptr(buf);
	
	return out_sym;
}

void atom_array_scramble(long ac, t_atom *av)
{
	if (ac == 0)
		return;

	shuffle_atoms(av, ac);
}



/* Function to swap values at two pointers */
void swap_uchar32(UChar32 *x, UChar32 *y)
{
    UChar32 temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

long fact(long n)
{
	long i, res = 1;
	for (i = 2; i <= n; i++)
		res *= i;
	return res;
}



char match(UChar32* Str,int i,int j)
{
    if(i == j) 
		return false;
	else
		for(;i<j;i++)
			if(Str[i]==Str[j])
				return true;
	return false;
	
}

/* Function to print permutations of string
 This function takes three parameters:
 1. String
 2. Starting index of the string
 3. Ending index of the string. */
void do_permute(UChar32 *a, int i, int n, t_symbol **out_symlist, long *sym_len, int32_t num_chars, long allocated_size, char only_unique) 
{
	int j; 
	if (i == n && *sym_len < allocated_size)
		out_symlist[(*sym_len)++] = symbol_from_uchar32_array(a, num_chars);
	else
	{
        for (j = i; j <= n; j++)
		{
			if (!only_unique || !match(a, i, j)) {
				swap_uchar32((a+i), (a+j));
				do_permute(a, i+1, n, out_symlist, sym_len, num_chars, allocated_size, only_unique);
				swap_uchar32((a+i), (a+j)); //backtrack
			}
		}
	}
} 

// returns 1 if error, 0 otherwise
char symbol_permute(t_symbol *s, t_symbol ***out_symlist, long *sym_len, char only_unique)
{
	int32_t out_size = 0;
	UChar32 *buf = symbol_to_uchar32_array(s, &out_size);
	long allocated_size = fact(out_size);
	*out_symlist = (t_symbol **)sysmem_newptr(allocated_size * sizeof(t_symbol *));

	if (!*out_symlist) {
		sysmem_freeptr(buf);
		return 1; // error
	}
	
    *sym_len = 0;
	do_permute(buf, 0, out_size - 1, *out_symlist, sym_len, out_size, allocated_size, only_unique);

	sysmem_freeptr(buf);
	return 0;
}


void atom_convert_symbol_to_number(t_atom *av)
{
	t_symbol *sym = atom_getsym(av);
	if (strstr(sym->s_name, ".")) {
		double val = atof(sym->s_name);
		atom_setfloat(av, val);
	} else {
		long val = atol(sym->s_name);
		atom_setlong(av, val);
	}
}

char symbol_is_numeric(t_symbol *sym)
{
    if (!sym)
        return 0;
    
	char *s = sym->s_name;
	if (s == NULL || *s == '\0' || isspace(*s))
		return 0;
    
	char * p;
	strtod (s, &p);
	return *p == '\0';
}


void textbuf_to_multiple_symbols_atom_array(char *textbuf, long *ac, t_atom **av)
{
    
}


void syobj_atom_array_reparse_account_for_listout(t_sy_object *x, long *ac, t_atom **av)
{
    char mode = x->l_listout_mode;
    
    switch (mode) {
        case SY_LISTOUT_MODE_SINGLE_SYMBOL:
            if (*ac > 1 || (*ac == 1 && atom_gettype(*av) != A_SYM)) {
                t_symbol *singlesymbol = symbol_from_gimme(*ac, *av);
                atom_setsym(*av, singlesymbol);
                *ac = 1;
            }
            break;
            
        case SY_LISTOUT_MODE_ALWAYS_SEPARATE:
        {
            long c;
            t_atom *new_av = NULL;
            long new_ac = 0;
            const long STEPSIZE = 128;
            long new_av_size = STEPSIZE;
            
            // allocate some memory for newav
            new_av = (t_atom *)sysmem_newptr(STEPSIZE * sizeof(t_atom));
            for (c = 0; c < *ac; c++) {
                t_symbol *s = NULL;
                if (atom_gettype(*av + c) == A_SYM && (s = atom_getsym(*av + c))) {
                    // deparse
                    long temp_ac = 0;
                    t_atom *temp_av = NULL;
                    atom_setparse(&temp_ac, &temp_av, s->s_name);
                    if (temp_av && temp_ac) {
                        
                        // check if STEPSIZE is enough
                        while (new_ac + temp_ac >= new_av_size - 1) {
                            new_av = (t_atom *)sysmem_resizeptr(new_av, (new_av_size + STEPSIZE) * sizeof(t_atom));
                            new_av_size += STEPSIZE;
                        }

                        for (long h = 0; h < temp_ac; h++)
                            new_av[new_ac++] = *(temp_av + h);
                        
                        sysmem_freeptr(temp_av);
                    }

                } else {
                    // check if STEPSIZE is enough
                    if (new_ac >= new_av_size - 1) {
                        new_av = (t_atom *)sysmem_resizeptr(new_av, (new_av_size + STEPSIZE) * sizeof(t_atom));
                        new_av_size += STEPSIZE;
                    }
                    
                    // just copy
                    new_av[new_ac++] = *(*av + c);
                }
            }
            
            sysmem_freeptr(*av);
            *av = new_av;
            *ac = new_ac;
            
        }
            break;
        default:
            return; // nothing to do
            break;
    }
}

void syobj_atom_array_reparse_account_for_numout(t_sy_object *x, long ac, t_atom *av)
{
	long i;
	char mode = x->l_numout_mode;

	switch (mode) {
		case SY_NUMOUT_MODE_FROM_ANY_SYMBOL:
			for (i = 0; i < ac; i++) 
				if (atom_gettype(av + i) == A_SYM) 
					atom_convert_symbol_to_number(av + i);
			break;
		case SY_NUMOUT_MODE_FROM_NUMERIC_SYMBOL:
			for (i = 0; i < ac; i++) 
				if (atom_gettype(av + i) == A_SYM && symbol_is_numeric(atom_getsym(av + i)))
					atom_convert_symbol_to_number(av + i);
			break;
		default:
			return; // nothing to do
			break;
	}
}


long symbol_to_atom_array(t_symbol *s, t_atom **out_av)
{
    if (!s) {
        if (out_av)
            *out_av = NULL;
        return 0;
    }
    
    if (out_av && !*out_av)
        *out_av = (t_atom *) sysmem_newptr(sizeof(t_atom));
    atom_setsym(*out_av, s);
    return 1;
}


long atom_array_join(long ac1, t_atom *av1, long ac2, t_atom *av2, t_atom **out_av)
{
	long out_ac = ac1 + ac2;
	if (out_av && !*out_av)
		*out_av = (t_atom *) sysmem_newptr(out_ac * sizeof(t_atom));
	sysmem_copyptr(av1, *out_av, ac1 * sizeof(t_atom));
	sysmem_copyptr(av2, *out_av + ac1, ac2 * sizeof(t_atom));
	return out_ac;
}



t_symbol *symbol_join(t_symbol *sym1, t_symbol *sym2)
{
	if (!sym1)
		return sym2;
	
	if (!sym2)
		return sym1;

	t_symbol *out = NULL;
	long len1 = strlen(sym1->s_name), len2 = strlen(sym2->s_name);
	char *buf = (char *)sysmem_newptr((len1 + len2 + 1) * sizeof(char));
	
	sysmem_copyptr(sym1->s_name, buf, len1 * sizeof(char));
	sysmem_copyptr(sym2->s_name, buf + len1, len2 * sizeof(char));
	buf[len1 + len2] = 0;
	
	out = gensym(buf);
	
	sysmem_freeptr(buf);
	return out;
}



t_symbol *symbol_replace_regexp(t_symbol *s, t_symbol *search, t_symbol *replace)
{
    UChar		*textToChange = symbol_to_uchar_array(s, NULL);
    UChar		*searchText = symbol_to_uchar_array(search, NULL);
    UChar		*replaceText = symbol_to_uchar_array(replace, NULL);
    long		allocated_size = u_strlen(textToChange) + 1; // null terminator
    UChar		*result = (UChar *)sysmem_newptrclear(allocated_size * sizeof(UChar));
    t_symbol	*out_sym = NULL;
    
    UErrorCode  status = U_ZERO_ERROR;
    
    URegularExpression *re = uregex_open(searchText, -1, 0, NULL, &status);
    
    if (U_SUCCESS(status)) {
        uregex_setText(re, textToChange, -1, &status); // simple replace
        int32_t needed_size = uregex_replaceAll(re, replaceText, -1, result, allocated_size - 1, &status);
        if (needed_size + 1 > allocated_size) {
            sysmem_freeptr(result);
            result = (UChar *)sysmem_newptrclear((needed_size + 1) * sizeof(UChar));
            status = U_ZERO_ERROR;
            uregex_replaceAll(re, replaceText, -1, result, needed_size, &status);
        }
        
        if (U_SUCCESS(status))
            out_sym = symbol_from_uchar_array(result, -1);
        
        uregex_close(re);
    }
    
    sysmem_freeptr(result);
    sysmem_freeptr(textToChange);
    sysmem_freeptr(searchText);
    sysmem_freeptr(replaceText);
    
    
    return out_sym;
}



t_symbol *symbol_replace_easy(t_symbol *s, t_symbol *search, t_symbol *replace)
{
    if (!search || strlen(search->s_name) == 0)
        return search;
    
    int32_t s_buf_size = 0, search_buf_size = 0, replace_buf_size = 0;
    UChar32 *s_buf = symbol_to_uchar32_array(s, &s_buf_size);
    UChar32 *search_buf = symbol_to_uchar32_array(search, &search_buf_size);
    UChar32 *replace_buf = symbol_to_uchar32_array(replace, &replace_buf_size);

    // 1. counting how many times "search_buf" is found in "replace_buf"
    long i, j, k;
    long matches[s_buf_size];
    long num_matches = 0;
    for (i = 0; i < s_buf_size - MAX(1, search_buf_size) + 1; i++) {
        long found = true;
        for (j = 0; j < search_buf_size; j++) {
            if (search_buf[j] != s_buf[i+j]) {
                found = false;
                break;
            }
        }
        matches[i] = found;
        if (found)
            num_matches++;
    }
    for (; i < s_buf_size; i++)
        matches[i] = 0;
    
    
    long out_buf_size = s_buf_size + num_matches * (replace_buf_size - search_buf_size);
    UChar32 *out_buf = (UChar32 *)sysmem_newptr(out_buf_size * sizeof(UChar32));
    t_symbol *out_sym = NULL;
    
    for (i = 0, j = 0; i < s_buf_size && j < out_buf_size; ) {
        if (matches[i]) {
            for (k = 0; k < replace_buf_size && j < out_buf_size; k++)
                out_buf[j++] = replace_buf[k];
            i += search_buf_size;
        } else {
            out_buf[j++] = s_buf[i++];
        }
    }
    
    out_sym = symbol_from_uchar32_array(out_buf, out_buf_size);
    sysmem_freeptr(s_buf);
    sysmem_freeptr(search_buf);
    sysmem_freeptr(replace_buf);
    return out_sym;

}



t_symbol *symbol_from_gimme(long ac, t_atom *av)
{
    char *buf = NULL;
    t_symbol *out = _sym_nothing;
    long textsize = 0;
    atom_gettext(ac, av, &textsize, &buf, OBEX_UTIL_ATOM_GETTEXT_SYM_NO_QUOTE);
    
    if (buf) {
        out = gensym(buf);
        sysmem_freeptr(buf);
    }
    
    return out;
}






// pads the incoming <sym> depending on the <mode> (= 0: repeat last element,
// = 1: loop, = 2: mirror back'n'forth loop) with <num_loopelems> elements taken from the
// <reservoir>, according to the <align> attribute (0 = align left, 1 = align center, 2 = align right).
// <rounding_direction> is ONLY used for centering align, when non-integer sized elements should be put at left or right
// 0 = round to left (= put one more element at right), 1 = round to right (= put one more element at left)
t_symbol *symbol_pad(t_symbol *sym, long output_length, char align, e_sy_pad_mode mode, long num_loop_elems, t_symbol *reservoir, char allow_trimming, char rounding_direction)
{
    
    if (!sym)
        return NULL;

    t_symbol *sym_out = sym;
    int32_t size;
    UChar32 *sym_buf = symbol_to_uchar32_array(sym, &size);
    UChar32 *elem;
    long i, count;
    long num_left = 0, num_right = 0;
    
    if (size == output_length)
        goto end;
    
    if (size > output_length) {
        if (!allow_trimming)
            goto end;
        
        long num_to_delete = size - output_length;
        switch (align) {
            case 2: // align right
                num_left = num_to_delete;
                num_right = 0;
                break;
            case 1: // align center
                if (rounding_direction == 0) {
                    num_right = num_to_delete/2;
                    num_left = num_to_delete - num_right;
                } else {
                    num_left = num_to_delete/2;
                    num_right = num_to_delete - num_left;
                }
                break;
            default: // align left
                num_left = 0;
                num_right = num_to_delete;
                break;
        }
        
        long size_out = size - num_left - num_right;
        UChar32 *sym_buf_out = (UChar32 *)sysmem_newptr((size_out + 1) * sizeof(UChar32));
        sysmem_copyptr(sym_buf + num_left, sym_buf_out, size_out * sizeof(UChar32));
        sym_buf_out[size_out] = 0;

        sym_out = symbol_from_uchar32_array(sym_buf_out, size_out);
        sysmem_freeptr(sym_buf_out);
        
    } else {
        int32_t reservoir_size = 0;
        UChar32 *reservoir_buf = reservoir && strlen(reservoir->s_name) > 0 ? symbol_to_uchar32_array(reservoir, &reservoir_size) : NULL;
        
        long num_to_add =  output_length - size;
        switch (align) {
            case 2: // align right
                num_left = num_to_add;
                num_right = 0;
                break;
            case 1: // align center
                if (rounding_direction == 0) {
                    num_left = num_to_add/2;
                    num_right = num_to_add - num_left;
                } else {
                    num_right = num_to_add/2;
                    num_left = num_to_add - num_right;
                }
                break;
            default: // align left
                num_left = 0;
                num_right = num_to_add;
                break;
        }
        
        // we keep them, since these might change later on when we pad
        UChar32 *head = reservoir_buf ? reservoir_buf : sym_buf;
        UChar32 *tail = reservoir_buf ? reservoir_buf + reservoir_size - 1 : sym_buf + size - 1;
        if (num_loop_elems == 0) num_loop_elems = num_to_add + 10; // doesn't matter, we'll never get there
        long curr_dir = -1, next_curr_dir = 0;
        
        long size_out = size + num_left + num_right;
        UChar32 *sym_buf_out = (UChar32 *)sysmem_newptr((size_out + 1) * sizeof(UChar32));
        sysmem_copyptr(sym_buf, sym_buf_out + num_left, size * sizeof(UChar32));
        sym_buf_out[size_out] = 0;
        
        // padding at left
        switch (mode) {
            case SY_PAD_REPEAT: elem = head; count = 0; break;
            case SY_PAD_LOOP_PALINDROME: elem = head; count = 0; curr_dir = 1; break;
            case SY_PAD_LOOP_PALINDROME_NO_REPEAT: elem = (head != tail && num_loop_elems > 1 ? head + 1 : head); count = 1; curr_dir = 1; break;
            default: elem = tail; count = 0; break;
        }
        for (i = 0; i < num_left; i++) {
            sym_buf_out[num_left - i - 1] = *elem;
            count++;
            
            if (mode == SY_PAD_LOOP_PALINDROME || mode == SY_PAD_LOOP_PALINDROME_NO_REPEAT) {
                if (count >= num_loop_elems || ((curr_dir < 0 && elem == head) || (curr_dir > 0 && elem == tail))) {
                    count = (mode == SY_PAD_LOOP_PALINDROME_NO_REPEAT ? 1 : 0);
                    if (mode == SY_PAD_LOOP_PALINDROME_NO_REPEAT)
                        curr_dir *= -1;
                    else {
                        next_curr_dir = curr_dir * -1;
                        curr_dir = 0;
                    }
                }
                elem = (curr_dir > 0 ? elem + 1 : (curr_dir < 0 ? elem - 1 : elem));
                if (curr_dir == 0) curr_dir = next_curr_dir;
            } else if (mode == SY_PAD_LOOP) {
                if (count >= num_loop_elems || elem == head || !elem) {
                    count = 0;
                    elem = tail;
                } else
                    elem = elem - 1;
            }
        }
        
        // padding at right
        switch (mode) {
            case SY_PAD_REPEAT: elem = tail; count = 0; break;
            case SY_PAD_LOOP_PALINDROME: elem = tail; count = 0; curr_dir = -1; break;
            case SY_PAD_LOOP_PALINDROME_NO_REPEAT: elem = (tail != head && num_loop_elems > 1 ? tail - 1 : tail); count = 1; curr_dir = -1; break;
            default: elem = head; count = 0; break;
        }
        for (i = 0; i < num_right; i++) {
            sym_buf_out[num_left + size + i] = *elem;
            count++;
            
            if (mode == SY_PAD_LOOP_PALINDROME || mode == SY_PAD_LOOP_PALINDROME_NO_REPEAT) {
                if (count >= num_loop_elems || ((curr_dir < 0 && elem == head) || (curr_dir > 0 && elem == tail))) {
                    count = (mode == SY_PAD_LOOP_PALINDROME_NO_REPEAT ? 1 : 0);
                    if (mode == SY_PAD_LOOP_PALINDROME_NO_REPEAT)
                        curr_dir *= -1;
                    else {
                        next_curr_dir = curr_dir * -1;
                        curr_dir = 0;
                    }
                }
                elem = (curr_dir > 0 ? elem + 1 : (curr_dir < 0 ? elem - 1 : elem));
                if (curr_dir == 0) curr_dir = next_curr_dir;
            } else if (mode == SY_PAD_LOOP) {
                if (count >= num_loop_elems || elem == tail || !elem) {
                    count = 0;
                    elem = head;
                } else
                    elem = elem + 1;
            }
        }
        
        sym_out = symbol_from_uchar32_array(sym_buf_out, size_out);
        sysmem_freeptr(sym_buf_out);

        if (reservoir_buf)
            sysmem_freeptr(reservoir_buf);
    }
    
end:
    sysmem_freeptr(sym_buf);
    return sym_out;
}

long pad_fn(t_sy_object *x, t_atom *atom_in, t_atom *atom_out, void *params, void *dummy, void *dummy2)
{
    char type_in = atom_gettype(atom_in);
    t_sy_pad_params *padparams = (t_sy_pad_params *)params;
    
    if (type_in == A_SYM) {
        atom_setsym(atom_out, symbol_pad(atom_getsym(atom_in), padparams->output_length, padparams->align, padparams->mode, padparams->num_loop_elems, padparams->reservoir, padparams->allow_trimming, padparams->rounding_direction));
    } else if (type_in == A_LONG || type_in == A_FLOAT) {
        *atom_out = *atom_in;
    } else {
        return 0;
    }
    
    return 1;
}

