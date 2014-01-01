require 'spec_helper'

describe Digest::SipHash do
  it "gc safe" do
    sip = SipHash.new
    GC.start
    sip.update ""
    GC.start
    expect(sip.hexdigest).to eq("1e924b9d737700d7")
  end
end
