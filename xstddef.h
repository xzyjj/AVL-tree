/* xstddef.h - posix standard type definitions */
#ifndef LIBF_SL_XSTDDEF_H
#define LIBF_SL_XSTDDEF_H

#include "config.h"


/* @def: stddef
* nil pointer */
#undef NULL
#define NULL ((void *)0)

/* struct member offset size */
#undef offsetof
#define offsetof(type, member) \
	((uint64)&(((type *)0)->member))

/* struct member and container offset size */
#undef container_of
#define container_of(ptr, type, member) \
	((type *)((void *)(ptr) - offsetof(type, member)))
/* end */


#endif
