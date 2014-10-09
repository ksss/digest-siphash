# Digest::SipHash

[![Build Status](https://travis-ci.org/ksss/digest-siphash.png)](https://travis-ci.org/ksss/digest-siphash)

Digest::SipHash is a class of message digest use algorithm SipHash.

## Usage

```ruby
require 'digest/siphash'

p Digest::SipHash.digest("siphash") #=> "\x59\xca\xae\xb9\x0d\x54\x24\x64"
p Digest::SipHash.hexdigest("siphash") #=> "59caaeb90d542464"
```

you can change seed string(128bits).
seed default value is `SipHash::DEFAULT_SEED` ("\x00" * 16)

```ruby
seed = (0..0x0f).to_a.pack("C16")
p Digest::SipHash.digest("siphash", seed) #=> "\x88\x27\x68\x57\x0d\xc7\x1c\x92"
p Digest::SipHash.hexdigest("siphash", seed) #=> "882768570dc71c92"
```

and other way. instance use.

```ruby
siphash = Digest::SipHash.new
siphash.update "siphash"
p siphash.hexdigest #=> "59caaeb90d542464"

# of course, can change seed value.
siphash.seed = (0..0x0f).to_a.pack("C16")
p siphash.hexdigest #=> "882768570dc71c92"
```

## Installation

Add this line to your application's Gemfile:

    gem 'digest-siphash'

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install digest-siphash

## Simple benchmark

```ruby
#! /usr/bin/env ruby

require 'benchmark'
require 'digest/md5'
require 'digest/sha1'
require 'digest/murmurhash'
require 'digest/siphash'

include Digest

n = 1000
str = "teststrings" * 1024 * 10

Benchmark.bm do |f|
  [MurmurHash1, MurmurHash2, MurmurHash64A, SipHash, MD5, SHA1].each do |klass|
    f.report(klass.to_s) {
      i = 0
      while i < n
        klass.digest(str)
        i += 1
      end
    }
  end
end
```

```
       user     system      total        real
Digest::MurmurHash1  0.050000   0.000000   0.050000 (  0.045282)
Digest::MurmurHash2  0.030000   0.000000   0.030000 (  0.032420)
Digest::MurmurHash64A  0.020000   0.000000   0.020000 (  0.015310)
Digest::SipHash  0.070000   0.000000   0.070000 (  0.068238)
Digest::MD5  0.150000   0.000000   0.150000 (  0.149649)
Digest::SHA1  0.130000   0.000000   0.130000 (  0.133704)
```

## See also

[https://131002.net/siphash/](https://131002.net/siphash/)
