/* xstdint.h - posix integer types definitions */
#ifndef LIBF_SL_XSTDINT_H
#define LIBF_SL_XSTDINT_H

#include "config.h"


/* @def: stdint
* int8 */
#undef int8
typedef signed char int8;

/* int8 size */
#undef INT8_MIN
#define INT8_MIN (-0x80)
#undef INT8_MAX
#define INT8_MAX 0x7f

/* uint8 */
#undef uint8
typedef unsigned char uint8;

/* uint8 size */
#undef UINT8_MAX
#define UINT8_MAX 0xff

/* int16 */
#undef int16
typedef signed short int16;

/* in16 size */
#undef INT16_MIN
#define INT16_MIN (-0x8000)
#undef INT16_MAX
#define INT16_MAX 0x7fff

/* uint16 */
#undef uint16
typedef unsigned short uint16;

/* uin16 size */
#undef UINT16_MAX
#define UINT16_MAX 0xffff

/* int32 */
#undef int32
typedef signed int int32;

/* int32 size */
#undef INT32_MIN
#define INT32_MIN (-0x80000000)
#undef INT32_MAX
#define INT32_MAX 0x7fffffff

/* uint32 */
#undef uint32
typedef unsigned int uint32;

/* uint32 size */
#undef UINT32_MAX
#define UINT32_MAX 0xffffffff

/* int64 */
#undef int64
typedef signed long int int64;

/* int64 size */
#undef INT64_MIN
#undef INT64_MAX
#ifdef LIBF_MARCH_BIT
#	if (LIBF_MARCH_BIT == LIBF_MARCH_BIT_32)
#		define INT64_MIN (-0x80000000)
#		define INT64_MAX 0x7fffffff
#	elif (LIBF_MARCH_BIT == LIBF_MARCH_BIT_64)
#		define INT64_MIN (-0x8000000000000000)
#		define INT64_MAX 0x7fffffffffffffff
#	else
#		error "!!!unknown LIBF_MARCH_BIT!!!"
#	endif
#else
#	error "!!!undefined LIBF_MARCH_BIT!!!"
#endif

/* uint64 */
#undef uint64
typedef unsigned long int uint64;

/* int64 size */
#undef UINT64_MAX
#ifdef LIBF_MARCH_BIT
#	if (LIBF_MARCH_BIT == LIBF_MARCH_BIT_32)
#		define UINT64_MAX 0xffffffff
#	elif (LIBF_MARCH_BIT == LIBF_MARCH_BIT_64)
#		define UINT64_MAX 0xffffffffffffffff
#	else
#		error "!!!unknown LIBF_MARCH_BIT!!!"
#	endif
#else
#	error "!!!undefined LIBF_MARCH_BIT!!!"
#endif

/* int64L */
#undef int64L
typedef signed long long int64L;

/* int64L size */
#undef INT64L_MIN
#define INT64L_MIN (-0x8000000000000000ULL)
#undef INT64L_MAX
#define INT64L_MAX 0x7fffffffffffffffULL

/* uint64L */
#undef uint64L
typedef unsigned long long uint64L;
#undef u64L
typedef uint64L u64L;

/* uint64L size */
#undef UINT64L_MAX
#define UINT64L_MAX 0xffffffffffffffffULL
/* end */


#endif
