# coding: utf-8

Gem::Specification.new do |spec|
  spec.name          = "digest-siphash"
  spec.version       = "1.0.1"
  spec.authors       = ["ksss"]
  spec.email         = ["co000ri@gmail.com"]
  spec.summary       = %q{Digest::SipHash is a class of message digest use algorithm SipHash.}
  spec.description   = %q{Digest::SipHash is a class of message digest use algorithm SipHash.}
  spec.homepage      = ""
  spec.license       = "MIT"

  spec.files         = `git ls-files`.split($/)
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ["lib"]
  spec.extensions    = ["ext/digest/siphash/extconf.rb"]

  spec.add_runtime_dependency "digest-simple"
  spec.add_development_dependency "bundler"
  spec.add_development_dependency "rake"
  spec.add_development_dependency "rspec"
  spec.add_development_dependency "rake-compiler", ["~> 0.8.3"]
end
