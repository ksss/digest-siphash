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

/* should be same type structure to digest/stringbuffer */
typedef struct {
	char* buffer;
	char* p;
	size_t memsize;
} buffer_t;

/*
 * from https://github.com/ruby/ruby/blob/trunk/ext/digest/digest.c
 * Copyright (C) 1995-2001 Yukihiro Matsumoto
 * Copyright (C) 2001-2006 Akinori MUSHA
 */
static VALUE
hexencode_str_new(VALUE str_digest)
{
	char *digest;
	size_t digest_len;
	size_t i;
	VALUE str;
	char *p;
	static const char hex[] = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'a', 'b', 'c', 'd', 'e', 'f'
	};

	StringValue(str_digest);
	digest = RSTRING_PTR(str_digest);
	digest_len = RSTRING_LEN(str_digest);

	if (LONG_MAX / 2 < digest_len) {
		rb_raise(rb_eRuntimeError, "digest string too long");
	}

	str = rb_usascii_str_new(0, digest_len * 2);

	for (i = 0, p = RSTRING_PTR(str); i < digest_len; i++) {
		unsigned char byte = digest[i];

		p[i + i]     = hex[byte >> 4];
		p[i + i + 1] = hex[byte & 0x0f];
	}

	return str;
}

#endif /* ifndef SIPHASH_INCLUDED */
