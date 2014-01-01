require 'spec_helper'

describe Digest::SipHash do
  it "gc safe" do
    sip = SipHash.new
    GC.start
    sip.update "siphash"
    GC.start
    expect(sip.hexdigest).to eq("59caaeb90d542464")
  end
end
