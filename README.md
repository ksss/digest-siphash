# Digest::SipHash

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
seed = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
p Digest::SipHash.digest("siphash", seed) #=> "\x88\x27\x68\x57\x0d\xc7\x1c\x92"
p Digest::SipHash.hexdigest("siphash", seed) #=> "882768570dc71c92"
```

and other way. instance use.

```ruby
siphash = Digest::SipHash.new
siphash.update "siphash"
p siphash.digest #=> "\x88\x27\x68\x57\x0d\xc7\x1c\x92"
# of course, can change seed value.
siphash.seed = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
p siphash.hexdigest "siphash" #=> "882768570dc71c92"
```

## Installation

Add this line to your application's Gemfile:

    gem 'digest-siphash'

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install digest-siphash

## Contributing

1. Fork it ( http://github.com/<my-github-username>/digest-siphash/fork )
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request

## See also

[https://131002.net/siphash/](https://131002.net/siphash/)
