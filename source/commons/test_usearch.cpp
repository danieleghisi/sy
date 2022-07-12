/*
 **********************************************************************
 *   Copyright (C) 2001-2014 IBM and others. All rights reserved.
 **********************************************************************
 *   Date        Name        Description
 *  07/02/2001   synwee      Creation.
 **********************************************************************
 */

#include "unicode/utypes.h"

#if !UCONFIG_NO_COLLATION && !UCONFIG_NO_BREAK_ITERATION

#include "unicode/usearch.h"
#include "unicode/usrchimp.h"
#include "unicode/ustring.h"
#include "unicode/uchar.h"
#include "unicode/utf16.h"
//#include "normalizer2impl.h"
//#include "usrchimp.h"
//#include "cmemory.h"
//#include "ucln_in.h"
//#include "uassert.h"
//#include "ustr_imp.h"

U_NAMESPACE_USE

// don't use Boyer-Moore
// (and if we decide to turn this on again there are several new TODOs that will need to be addressed)
#define BOYER_MOORE 0

#define LENGTHOF(array) (int32_t)(sizeof(array)/sizeof((array)[0]))

// internal definition ---------------------------------------------------

#define LAST_BYTE_MASK_          0xFF
#define SECOND_LAST_BYTE_SHIFT_  8
#define SUPPLEMENTARY_MIN_VALUE_ 0x10000


U_CAPI void U_EXPORT2 usearch_setAttribute(UStringSearch *strsrch,
                                 USearchAttribute attribute,
                                 USearchAttributeValue value,
                                 UErrorCode *status)
{
    if (U_SUCCESS(*status) && strsrch) {
        switch (attribute)
        {
        case USEARCH_OVERLAP :
            strsrch->search->isOverlap = (value == USEARCH_ON ? TRUE : FALSE);
            break;
        case USEARCH_CANONICAL_MATCH :
            strsrch->search->isCanonicalMatch = (value == USEARCH_ON ? TRUE : FALSE);
            break;
        case USEARCH_ELEMENT_COMPARISON :
            if (value == USEARCH_PATTERN_BASE_WEIGHT_IS_WILDCARD || value == USEARCH_ANY_BASE_WEIGHT_IS_WILDCARD) {
                strsrch->search->elementComparisonType = (int16_t)value;
            } else {
                strsrch->search->elementComparisonType = 0;
            }
            break;
        case USEARCH_ATTRIBUTE_COUNT :
        default:
            *status = U_ILLEGAL_ARGUMENT_ERROR;
        }
    }
    if (value == USEARCH_ATTRIBUTE_VALUE_COUNT) {
        *status = U_ILLEGAL_ARGUMENT_ERROR;
    }
}

#endif /* #if !UCONFIG_NO_COLLATION */
