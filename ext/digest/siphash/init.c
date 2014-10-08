#include "siphash24.h"
#include "siphash.h"

#define siphash crypto_auth

VALUE cDigest_SipHash;
ID id_DEFAULT_SEED;
ID iv_seed;
ID iv_buffer;

static void
_siphash_s_digest(uint8_t* digest, int argc, VALUE *argv)
{
	VALUE str;
	const unsigned char *seed;

	if (argc < 1)
		rb_raise(rb_eArgError, "no data given");

	str = argv[0];
	StringValue(str);

	if (1 < argc) {
		StringValue(argv[1]);
		if (RSTRING_LEN(argv[1]) != 16) {
			rb_raise(rb_eArgError, "seed string should 128 bit chars");
		}
		seed = (const unsigned char*) RSTRING_PTR(argv[1]);
	} else {
		seed = (const unsigned char*) RSTRING_PTR(
				rb_const_get(cDigest_SipHash, id_DEFAULT_SEED));
	}

	siphash(digest, (const unsigned char*) RSTRING_PTR(str), RSTRING_LEN(str), seed);
}

static inline void
_siphash_finish(uint8_t *digest, VALUE self)
{
	const unsigned char *seed;
	VALUE buffer;

	buffer = rb_ivar_get(self, iv_buffer);
	seed = (const unsigned char *) RSTRING_PTR(rb_ivar_get(self, iv_seed));
	siphash(digest, (const unsigned char *) RSTRING_PTR(buffer), RSTRING_LEN(buffer), seed);
}

static VALUE
siphash_finish(VALUE self)
{
	uint8_t digest[8];
#if LITTLE_ENDIAN
	uint8_t roll[8];
	int i;
#endif
	_siphash_finish(digest, self);
#if LITTLE_ENDIAN
	for (i = 0; i < 8; i++) {
		roll[i] = digest[7 - i];
	}
	memcpy(digest, roll, 8);
#endif
	return rb_str_new((const char*) digest, 8);
}

static VALUE
siphash_s_digest(int argc, VALUE *argv, VALUE klass)
{
	uint8_t digest[8];
#if LITTLE_ENDIAN
	uint8_t roll[8];
	int i;
#endif
	_siphash_s_digest(digest, argc, argv);
#if LITTLE_ENDIAN
	for (i = 0; i < 8; i++) {
		roll[i] = digest[7 - i];
	}
	memcpy(digest, roll, 8);
#endif
	return rb_str_new((const char*) digest, 8);
}

static VALUE
siphash_s_rawdigest(int argc, VALUE *argv, VALUE klass)
{
	uint8_t digest[8];
#if LITTLE_ENDIAN
	uint8_t roll[8];
	int i;
#endif
	_siphash_s_digest(digest, argc, argv);
#if LITTLE_ENDIAN
	for (i = 0; i < 8; i++) {
		roll[i] = digest[7 - i];
	}
	memcpy(digest, roll, 8);
#endif
	return ULL2NUM(*(uint64_t *) digest);
}

void
Init_siphash(void)
{
	id_DEFAULT_SEED = rb_intern("DEFAULT_SEED");
	iv_buffer = rb_intern("@buffer");
	iv_seed = rb_intern("@seed");

	cDigest_SipHash = rb_path2class("Digest::SipHash");
	rb_define_private_method(cDigest_SipHash, "finish", siphash_finish, 0);
	rb_define_singleton_method(cDigest_SipHash, "digest", siphash_s_digest, -1);
	rb_define_singleton_method(cDigest_SipHash, "rawdigest", siphash_s_rawdigest, -1);
}
