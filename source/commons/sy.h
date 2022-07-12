/**
	@file
	sy.h
	Header for the sy library
 
	by Daniele Ghisi
 */

#include "ext.h"							// standard Max include, always required
#include "ext_obex.h"						// required for new style Max object
#include "ext_atomic.h"						// atomic operations
#include "ext_proto.h"

#define U_DISABLE_RENAMING 1                // EXTREMELY IMPORTANT: for some reasons, renaming messes up things

#define dev_post(...) ((void) 0)

#ifdef CONFIGURATION_Development
	#undef dev_post
	#define dev_post(...) post(__VA_ARGS__)
#endif
