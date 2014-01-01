#include "siphash24.h"
#include "siphash.h"

#define siphash crypto_auth
#define DEFAULT_SEED "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"

VALUE cDigest_SipHash;
ID id_DEFAULT_SEED;
ID id_seed;

static VALUE
siphash_seed_get(VALUE self)
{
	if (!rb_ivar_defined(self, id_seed)) {
		rb_ivar_set(self, id_seed, rb_str_new(DEFAULT_SEED, 16));
	}
	return rb_ivar_get(self, id_seed);
}

static VALUE
siphash_seed_set(VALUE self, VALUE obj)
{
	StringValue(obj);
	if (RSTRING_LEN(obj) != 16) {
		rb_raise(rb_eArgError, "seed string should 128 bit chars");
	}
	return rb_ivar_set(self, id_seed, obj);
}

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
	buffer_t *ptr;

	Data_Get_Struct(self, buffer_t, ptr);
	seed = (const unsigned char *) RSTRING_PTR(siphash_seed_get(self));
	siphash(digest, (const unsigned char *) ptr->buffer, ptr->p - ptr->buffer, seed);
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
siphash_to_i(VALUE self)
{
	uint8_t digest[8];
	_siphash_finish(digest, self);
	return ULL2NUM(*(uint64_t *) digest);
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
siphash_s_hexdigest(int argc, VALUE *argv, VALUE klass)
{
	return hexencode_str_new(siphash_s_digest(argc, argv, klass));
}

static VALUE
siphash_s_rawdigest(int argc, VALUE *argv, VALUE klass)
{
	uint8_t digest[8];
	_siphash_s_digest(digest, argc, argv);
	return ULL2NUM(*(uint64_t *) digest);
}

void
Init_siphash(void)
{
	VALUE mDigest, cDigest_StringBuffer;

	id_DEFAULT_SEED = rb_intern("DEFAULT_SEED");
	id_seed = rb_intern("seed");

	/* Digest::SipHash is require that Digest::StringBuffer */
	mDigest = rb_path2class("Digest");
	cDigest_StringBuffer = rb_path2class("Digest::StringBuffer");

	/* class Digest::SipHash < Digest::StringBuffer */
	cDigest_SipHash = rb_define_class_under(mDigest, "SipHash", cDigest_StringBuffer);
	rb_define_private_method(cDigest_SipHash, "finish", siphash_finish, 0);
	rb_define_method(cDigest_SipHash, "to_i", siphash_to_i, 0);
	rb_define_singleton_method(cDigest_SipHash, "digest", siphash_s_digest, -1);
	rb_define_singleton_method(cDigest_SipHash, "hexdigest", siphash_s_hexdigest, -1);
	rb_define_singleton_method(cDigest_SipHash, "rawdigest", siphash_s_rawdigest, -1);
	rb_define_method(cDigest_SipHash, "seed", siphash_seed_get, 0);
	rb_define_method(cDigest_SipHash, "seed=", siphash_seed_set, 1);
	rb_define_const(cDigest_SipHash, "DEFAULT_SEED", rb_str_new(DEFAULT_SEED, 16));
}
