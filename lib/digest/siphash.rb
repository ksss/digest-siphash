require "digest/stringbuffer"
begin
  require "digest/siphash/#{RUBY_VERSION[/\d+.\d+/]}/siphash"
rescue LoadError
  require "digest/siphash/siphash"
end
