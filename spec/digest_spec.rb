# coding: ascii-8bit
require 'spec_helper'

describe Digest::SipHash do
  let :seed do
    (0..0x0f).to_a.pack("C16")
  end

  it "initialize" do
    expect(SipHash.new).to be_a_kind_of(Digest::Class)
  end

  it "DEFAULT_SEED" do
    expect(SipHash::DEFAULT_SEED).to eq("\x00" * 16)
  end

  it "seed" do
    sip = SipHash.new
    expect(sip.seed).to eq("\x00" * 16)
  end

  it "seed=" do
    sip = SipHash.new
    sip.seed = seed
    expect(sip.seed).to eq(seed)
  end

  it "digest" do
    expect(SipHash.digest("")).to eq("\x1e\x92\x4b\x9d\x73\x77\x00\xd7")
    expect(SipHash.digest("", seed)).to eq("\x72\x6f\xdb\x47\xdd\x0e\x0e\x31")
    expect(SipHash.digest("\x00", seed)).to eq("\x74\xf8\x39\xc5\x93\xdc\x67\xfd")
    expect(SipHash.digest("\x00\x01", seed)).to eq("\x0d\x6c\x80\x09\xd9\xa9\x4f\x5a")
  end

  it "hexdigest" do
    expect(SipHash.hexdigest("")).to eq("1e924b9d737700d7")
    expect(SipHash.hexdigest("", seed)).to eq("726fdb47dd0e0e31")
    expect(SipHash.hexdigest("\x00", seed)).to eq("74f839c593dc67fd")
    expect(SipHash.hexdigest("\x00\x01", seed)).to eq("0d6c8009d9a94f5a")
  end

  it "rawdigest" do
    expect(SipHash.rawdigest("")).to eq(0xd70077739d4b921e)
    expect(SipHash.rawdigest("", seed)).to eq(0x310e0edd47db6f72)
    expect(SipHash.rawdigest("\x00", seed)).to eq(0xfd67dc93c539f874)
    expect(SipHash.rawdigest("\x00\x01", seed)).to eq(0x5a4fa9d909806c0d)
  end

  it "instance digest" do
    sip = SipHash.new
    sip.update ""
    expect(sip.digest).to eq("\x1e\x92\x4b\x9d\x73\x77\x00\xd7")
    expect(sip.to_i).to eq(0xd70077739d4b921e)

    sip.seed = seed
    expect(sip.digest).to eq("\x72\x6f\xdb\x47\xdd\x0e\x0e\x31")
    expect(sip.to_i).to eq(0x310e0edd47db6f72)
  end
end

