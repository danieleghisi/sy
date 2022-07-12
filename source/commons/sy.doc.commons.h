/**
	@file	sy_doc_commons.h
	@brief	Common documentation about some basic concepts of the sy library.
 
	by Daniele Ghisi
 */


#define SY_DOC_NUMBERS_ATTRIBUTE
//	Handles the way in which the functions should behave when a numerical value is received: <br />
//  0 = Let Through: numbers are left untouched and output as they were received; <br />
//  1 = Convert To Symbol (default): numbers are converted to symbol and then processed as such; <br />
//  2 = Drop: numbers are ignored and dropped from the output (if a single number was inserted, nothing is output). <br />
//  <br /> <br />


#define SY_DOC_COMPARISON_STRENGTH
// The strength of the comparison can be set to different levels. <br /> <br />
// - <b>Primary Level</b>: this denotes differences between base characters (for example, "a" &gt; "b"). 
// It is the strongest difference. For example, dictionaries are divided into different sections by base character. <br /> <br />
// - <b>Secondary Level</b>: accents in the characters are considered secondary differences (for example, "as" &gt; "às" &gt; "at"). 
// Other differences between letters can also be considered secondary differences, depending on the language. 
// A secondary difference is ignored when there is a primary difference anywhere in the strings. 
// Note: In some languages (such as Danish), certain accented letters are considered to be separate base characters. 
// In most languages, however, an accented letter only has a secondary difference from the unaccented version of that letter <br /> <br />
// - <b>Tertiary Level</b> (default): Upper and lower case differences in characters are distinguished at the tertiary level 
// (for example, "ao" &gt; "Ao" &gt; "aò"). In addition, a variant of a letter differs from the base form on the tertiary level. 
// Another example is the difference between large and small Kana. A tertiary difference is ignored when 
// there is a primary or secondary difference anywhere in the strings. <br /> <br />
// - <b>Quaternary Level</b>: when punctuation is ignored at level 1-3 (i.e. the <m>alternate</m> attribtue is set), 
// an additional level can be used to distinguish words 
// with and without punctuation (for example, "ab" &gt; "a-b" &gt; "aB"). This difference is ignored when there is a primary, secondary or 
// tertiary difference. The quaternary level should only be used if ignoring punctuation is required (i.e. the <m>alternate</m> attribtue is set) 
// or when processing Japanese text. <br /> <br />
// - <b>Identical Level</b>: when all other levels are equal, the identical level is used as a tiebreaker. 
// The Unicode code point values of the NFD form of each string are compared at this level, just in case there is no difference at levels 1-4. 
// For example, Hebrew cantillation marks are only distinguished at this level. 
// This level should be used sparingly, as only code point values differences between two strings is an extremely rare occurrence. 
// Using this level substantially decreases the performance for 
// both incremental comparison and sort key generation (as well as increasing the sort key length). <br /> <br />
// This distinction is completely inherited by the ICU collation standards: see http://userguide.icu-project.org/collation/concepts.

#define SY_DOC_INDICES
// In the sy library, indices are always 1-based (i.e. 1 is first character, 2 is second character, and so on).
// Negative numbers count backwards, starting from the end of the symbol (-1 is last character, -2 is one-but-last, and so on). <br />
// A range syntax is also available: to define ranges of indices, wrap them inside a level of parenthesis (leaving a space
// before and after each parenthesis). For instance, <b>1 2 ( 4 8 )</b> refers to the first and second element, and then to
// elements from 4th to 8th.