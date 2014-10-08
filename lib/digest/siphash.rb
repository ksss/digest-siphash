require 'digest'
require "digest/simple"

module Digest
  class SipHash < Simple
    VERSION = "1.0.0"
    DEFAULT_SEED = "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00".encode('ASCII-8BIT')

    def initialize
      @seed = DEFAULT_SEED
      super
    end

    def seed
      @seed
    end

    def seed=(s)
      fail ArgumentError, "seed string should 128 bit chars" if s.bytesize != 16
      @seed = s
    end

    def to_i
      finish.unpack("Q")[0]
    end
  end
end

require "digest/siphash/siphash"
