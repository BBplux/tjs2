/*---------------------------------------------------------------------------*/
/*
	TJS2 Script Engine
	Copyright (C) 2000 W.Dee <dee@kikyou.info> and contributors

	See details of license at "license.txt"
*/
/*---------------------------------------------------------------------------*/
/* "TJS2" type definitions                                                   */
/*---------------------------------------------------------------------------*/

#ifndef __TJSTYPES_H__
#define __TJSTYPES_H__

#include <stdint.h>

#ifdef HAVE_CONFIG_H
 #include "config.h"

 #ifndef HAVE_STRINGIZE
 # error "preprocessor stringize required."
 #endif

 #if SIZEOF_INT < 4
 # error "sizeof(int) must be larger than or equal to 4."
 #endif
#endif /* end of HAVE_CONFIG_H */



/* Functions that needs to be exported ( for non-class-member functions ) */
/* This should only be applyed for function declaration in headers ( not body ) */
#define TJS_EXP_FUNC_DEF(rettype, name, arg) extern rettype name arg


/* Functions that needs to be exported ( for class-member functions ) */
#define TJS_METHOD_DEF(rettype, name, arg) rettype name arg
#define TJS_CONST_METHOD_DEF(rettype, name, arg) rettype name arg const
#define TJS_STATIC_METHOD_DEF(rettype, name, arg) static rettype name arg
#define TJS_STATIC_CONST_METHOD_DEF(rettype, name, arg) static rettype name arg const
#define TJS_METHOD_RET_EMPTY
#define TJS_METHOD_RET(type)


/*[*/
typedef int8_t tjs_int8;
typedef uint8_t tjs_uint8;
typedef int16_t tjs_int16;
typedef uint16_t tjs_uint16;
typedef int32_t tjs_int32;
typedef uint32_t tjs_uint32;
typedef int64_t tjs_int64;
typedef uint64_t tjs_uint64;

typedef int tjs_int;
typedef unsigned int tjs_uint;

typedef intptr_t tjs_intptr_t;
typedef uintptr_t tjs_uintptr_t;

typedef wchar_t tjs_char;
typedef std::wstring tjs_string;
typedef char tjs_nchar;

typedef double tjs_real;

#define TJS_I64_VAL(x) ((tjs_int64)(x##LL))
#define TJS_UI64_VAL(x) ((tjs_uint64)(x##LL))

#define TJS_W(X) L##X
#define TJS_N(X) X


#if defined(_WIN32)  && !defined(__GNUC__)
/* VC++/BCC */

#define TJS_HOST_IS_BIG_ENDIAN 0
#define TJS_HOST_IS_LITTLE_ENDIAN 1

#ifdef _M_X64
#define TJS_64BIT_OS	/* 64bit windows */
#endif

#else
/* gcc ? */

#ifdef WORDS_BIGENDIAN
	#define TJS_HOST_IS_BIG_ENDIAN 1
	#define TJS_HOST_IS_LITTLE_ENDIAN 0
#else
	#define TJS_HOST_IS_BIG_ENDIAN 0
	#define TJS_HOST_IS_LITTLE_ENDIAN 1
#endif


#endif /* end of defined(_WIN32) && !defined(__GNUC__) */
/*]*/

/*[*/
typedef tjs_int32 tjs_error;

typedef tjs_int64 tTVInteger;
typedef tjs_real tTVReal;

typedef size_t tjs_size;
typedef ptrdiff_t tjs_offset;

/* IEEE double manipulation support
 (TJS requires IEEE double(64-bit float) native support on machine or C++ compiler) */

/*

63 62       52 51                         0
+-+-----------+---------------------------+
|s|    exp    |         significand       |
+-+-----------+---------------------------+

s = sign,  negative if this is 1, otherwise positive.



*/

/* double related constants */
#define TJS_IEEE_D_EXP_MAX 1023
#define TJS_IEEE_D_EXP_MIN -1022
#define TJS_IEEE_D_SIGNIFICAND_BITS 52

#define TJS_IEEE_D_EXP_BIAS 1023

/* component extraction */
#define TJS_IEEE_D_SIGN_MASK              (TJS_UI64_VAL(0x8000000000000000))
#define TJS_IEEE_D_EXP_MASK               (TJS_UI64_VAL(0x7ff0000000000000))
#define TJS_IEEE_D_SIGNIFICAND_MASK       (TJS_UI64_VAL(0x000fffffffffffff))
#define TJS_IEEE_D_SIGNIFICAND_MSB_MASK   (TJS_UI64_VAL(0x0008000000000000))

#define TJS_IEEE_D_GET_SIGN(x)   (0!=(x & TJS_IEEE_D_SIGN_MASK))
#define TJS_IEEE_D_GET_EXP(x)  ((tjs_int)(((x & TJS_IEEE_D_EXP_MASK) >> \
								TJS_IEEE_D_SIGNIFICAND_BITS) - TJS_IEEE_D_EXP_BIAS))
#define TJS_IEEE_D_GET_SIGNIFICAND(x) (x & TJS_IEEE_D_SIGNIFICAND_MASK)

/* component composition */
#define TJS_IEEE_D_MAKE_SIGN(x)  ((x)?TJS_UI64_VAL(0x8000000000000000):TJS_UI64_VAL(0))
#define TJS_IEEE_D_MAKE_EXP(x)   ((tjs_uint64)(x + TJS_IEEE_D_EXP_BIAS) << 52)
#define TJS_IEEE_D_MAKE_SIGNIFICAND(x) ((tjs_uint64)(x))

/* special expression */
 /* (quiet) NaN */
  #define TJS_IEEE_D_P_NaN (tjs_uint64)(TJS_IEEE_D_EXP_MASK|TJS_IEEE_D_SIGNIFICAND_MSB_MASK)
  #define TJS_IEEE_D_N_NaN (tjs_uint64)(TJS_IEEE_D_SIGN_MASK|TJS_IEEE_D_P_NaN)
 /* infinite */
  #define TJS_IEEE_D_P_INF (tjs_uint64)(TJS_IEEE_D_EXP_MASK)
  #define TJS_IEEE_D_N_INF (tjs_uint64)(TJS_IEEE_D_SIGN_MASK|TJS_IEEE_D_P_INF)

/* special expression check */
  #define TJS_IEEE_D_IS_NaN(x) ((TJS_IEEE_D_EXP_MASK & (x)) == TJS_IEEE_D_EXP_MASK) && \
				(((x) & TJS_IEEE_D_SIGNIFICAND_MSB_MASK) || \
				(!((x) & TJS_IEEE_D_SIGNIFICAND_MSB_MASK) && \
				((x) & (TJS_IEEE_D_SIGNIFICAND_MASK ^ TJS_IEEE_D_SIGNIFICAND_MSB_MASK))))
  #define TJS_IEEE_D_IS_INF(x) (((TJS_IEEE_D_EXP_MASK & (x)) == TJS_IEEE_D_EXP_MASK) && \
				(!((x) & TJS_IEEE_D_SIGNIFICAND_MASK)))

/*]*/

#endif
