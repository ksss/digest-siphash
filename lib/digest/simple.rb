module Digest
  class Simple < Class
    def initialize
      @buffer = ""
    end

    def reset
      @buffer.clear
    end

    def update(str)
      @buffer += str
    end
    alias << update

    def digest(str=nil)
      if str
        reset
        update(str)
        v = finish
        reset
        v
      else
        dup.send :finish
      end
    end

    private

    def finish
      fail NotImplementedError, "must be defined finish method"
    end
  end
end
