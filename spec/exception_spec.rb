require 'spec_helper'

describe Digest::SipHash do
  it "no data given" do
    expect{ SipHash::digest }.to raise_error(ArgumentError)
  end

  it "seed string should 128 bit chars" do
    expect{ SipHash::digest("siphash", "\x00") }.to raise_error(ArgumentError)

    sip = SipHash.new
    expect{ sip.seed = "0x00" }.to raise_error(ArgumentError)
  end
end



