/**
	@file	sy_doc_substitutions.h
	@brief	Substitutions file for the sy library documentation
 
	by Daniele Ghisi
 */

#define syobj_class_add_numin_attr
CLASS_ATTR_LONG(c, "numin", 0, t_sy_object, l_numin_mode);
CLASS_ATTR_STYLE_LABEL(c,"numin",0,"enumindex","When Numbers Are Received");
CLASS_ATTR_ENUMINDEX(c,"numin", 0, "Let Through Convert To Symbol Drop"); 
CLASS_ATTR_ACCESSORS(c, "numin", (method)NULL, (method)syobj_setattr_numbers);
CLASS_ATTR_CATEGORY(c, "numin", 0, "Behavior");
// @description Sets the way in which numbers should be handled when received:
// - Let Through: numbers should be simply copied to the output; <br />
// - Convert To Symbol (default): numbers should be converted to symbols and handled as such; <br />
// - Drop: drop numbers from the outlet. <br />

#define syobj_class_add_numout_attr
CLASS_ATTR_LONG(c, "numout", 0, t_sy_object, l_numin_mode);
CLASS_ATTR_STYLE_LABEL(c,"numout",0,"enumindex","Output Numbers");
CLASS_ATTR_ENUMINDEX(c,"numout", 0, "Only With Numeric Original Convert From Numeric Symbols Convert From All Symbols"); 
CLASS_ATTR_ACCESSORS(c, "numout", (method)NULL, (method)syobj_setattr_numout);
CLASS_ATTR_CATEGORY(c, "numout", 0, "Behavior");
// @description Sets the way in which numbers should be handled when output:
// - Only With Numeric Original: keep as numbers only the incoming numbers (beware: if you choose "Convert To Symbol"
// as <m>numin</m> attribute, the numbers will be converted to symbols, and thus will be output as such, in this case); <br />
// - Convert From Numeric Symbols (default): symbol which completely represent a number are converted into the number; <br />
// - Convert From All Symbols: all symbols are converted into numbers. <br />


#define syobj_class_add_maxdecimals_attr
CLASS_ATTR_LONG(c, "maxdecimals", 0, t_sy_object, l_maxdecimals);
CLASS_ATTR_STYLE_LABEL(c,"maxdecimals",0,"text","Maximum Decimal Digits For Number Conversion");
CLASS_ATTR_CATEGORY(c, "maxdecimals", 0, "Behavior");
// @description Sets the maximum number of decimals to be used for the conversion from number
// to symbol, in case the <m>numbers</m> attribute is set to "Convert To Symbol".

#define syobj_class_add_listin_attr
CLASS_ATTR_LONG(c, "listin", 0, t_sy_object, l_listin_mode);
CLASS_ATTR_STYLE_LABEL(c,"listin",0,"enumindex","When Lists Are Input");
CLASS_ATTR_ENUMINDEX(c,"listin", 0, "Process Globally Process Element-Wise");
CLASS_ATTR_CATEGORY(c, "listin", 0, "Behavior");
// @description Sets the way in which lists should be handled when received:
// - Process Globally (default): lists are treated as a single symbol (each couple of atoms is interpreted as being joined via a whitespace character); <br />
// - Process Element-Wise: each atom is processed separately. <br />

#define syobj_class_add_listout_attr
CLASS_ATTR_LONG(c, "listout", 0, t_sy_object, l_listout_mode);
CLASS_ATTR_STYLE_LABEL(c,"listout",0,"enumindex","Output Elements");
CLASS_ATTR_ENUMINDEX(c,"listout", 0, "Always As Single Symbol Adapt To Input Always Separate");
CLASS_ATTR_CATEGORY(c, "listout", 0, "Behavior");
// @description Sets the way in which elements should be arranged in lists at output.
// - Always As Single Symbol: atoms are never separated into lists, and a single symbol is always output; <br />
// - Adapt To Input (default): lists are output only if in accordance with the fact that lists had been input; <br />
// - Always Separate: lists are split into atoms whenever possible. This is roughly equivalent as having a <o>fromsymbol</o> object connected to sy object's outlet <br />



#define syobj_class_add_locale_attr
CLASS_ATTR_SYM(c, "locale", 0, t_sy_object, l_locale);
CLASS_ATTR_STYLE_LABEL(c,"locale",0,"text","Locale");
CLASS_ATTR_CATEGORY(c, "locale", 0, "Behavior");
// @exclude all
// @description The <m>locale</m> attribute is a symbol setting the locale. 
// A locale identifies a specific user community - a group of users who have similar culture 
// and language expectations for human-computer interaction (and the kinds of data they process). <br />
// The languages are specified using a two- or three-letter lowercase code for a particular language. 
// For example, Spanish is "es", English is "en" and French is "fr". The two-letter language code uses the ISO-639 standard. <br />
// The optional four-letter script code follows the language code. If specified, it should be a valid script code as 
// listed on the Unicode ISO 15924 Registry. <br />
// There are often different language conventions within the same language. For example, Spanish is spoken in many countries in Central 
// and South America but the currencies are different in each country. To allow for these differences among specific geographical, 
// political, or cultural regions, locales are specified by two-letter, uppercase codes. For example, "ES" represents Spain and "MX" 
// represents Mexico. The two letter country code uses the ISO-3166 standard. <br />
// The locale is a concept fully inherited by the ICU, please refer to
// http://userguide.icu-project.org/locale for more information.


