#ifndef SIPHASH_INCLUDED
#  define SIPHASH_INCLUDED

#include "ruby.h"

#ifndef LITTLE_ENDIAN
/* NO-OP for little-endian platforms */
#  if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__)
#    if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#      define LITTLE_ENDIAN 1
#    endif
/* if __BYTE_ORDER__ is not predefined (like FreeBSD), use arch */
#  elif defined(__i386)  || defined(__x86_64) ||  defined(__alpha) || defined(__vax)
#    define LITTLE_ENDIAN 1
#  endif
#endif

/* last resort (big-endian w/o __builtin_bswap64) */
#ifndef LITTLE_ENDIAN
#  define LITTLE_ENDIAN 0
#endif

#endif /* ifndef SIPHASH_INCLUDED */
