#include "XWB.h"

namespace Aezesel {
  void XWB::load(std::string filename){
    std::ifstream input(filename, std::ios::binary);
    if (input.fail())
      throw std::runtime_error("Error opening " + filename);
    _buffer = std::vector<unsigned char>(std::istreambuf_iterator<char>(input), {});
    loadInternal();
    //return loadInternal();
  }

  void XWB::loadInternal() {

    //_WB_HEADER = '4s I I'
    //(h_sig, self.h_version, self.h_header_version) = stream.unpack(_WB_HEADER)

    std::string h_sig = readString(_buffer, _fileposition, 4);
    if (h_sig != "WBND")
      throw std::runtime_error("Magic byte wrong");

    unsigned int version       = readUInt(_buffer, _fileposition);
    unsigned int headerVersion = readUInt(_buffer, _fileposition);

    //_REGIONS = ['BANKDATA', 'ENTRYMETADATA', 'SEEKTABLES', 'ENTRYNAMES', 'ENTRYWAVEDATA']
    //_WB_REGION = 'II' //offset, length
    //regions = {k: XWBRegion._make(stream.unpack(_WB_REGION)) for k in _REGIONS}

    unsigned int bankDataOffset      = readUInt(_buffer, _fileposition);
    unsigned int bankDataLength      = readUInt(_buffer, _fileposition);

    unsigned int entryMetaDataOffset = readUInt(_buffer, _fileposition);
    unsigned int entryMetaDataLength = readUInt(_buffer, _fileposition);

    unsigned int SeektablesOffset    = readUInt(_buffer, _fileposition);
    unsigned int SeektablesLength    = readUInt(_buffer, _fileposition);

    unsigned int EntryNamesOffset    = readUInt(_buffer, _fileposition);
    unsigned int EntryNamesLength    = readUInt(_buffer, _fileposition);

    unsigned int EntryWaveDataOffset = readUInt(_buffer, _fileposition);
    unsigned int EntryWaveDataLength = readUInt(_buffer, _fileposition);

    _fileposition = bankDataOffset;
    //_WB_DATA = 'I I 64s I I I I II'
    
    unsigned int flags                    = readUInt  (_buffer, _fileposition);
    unsigned int entryCount               = readUInt  (_buffer, _fileposition);
    std::string  bank_name                = readString(_buffer, _fileposition, 64);
    unsigned int entryMetaDataElementSize = readUInt  (_buffer, _fileposition);
    unsigned int entryNameElementSize     = readUInt  (_buffer, _fileposition);
    unsigned int alignment                = readUInt  (_buffer, _fileposition);
    unsigned int compactFormat            = readUInt  (_buffer, _fileposition);
    unsigned int buildTimeLow             = readUInt  (_buffer, _fileposition);
    unsigned int buildTimeHigh            = readUInt  (_buffer, _fileposition);

    std::vector<XWBEntry> entries;
    //_WB_ENTRY = 'I I II II' x entryCount
    _fileposition = entryMetaDataOffset;

    for (int i = 0; i < entryCount; i++) {
      XWBEntry entry;
      entry.flags_duration   = readUInt(_buffer, _fileposition);
      entry.format           = readUInt(_buffer, _fileposition);
      entry.play_offset      = readUInt(_buffer, _fileposition);
      entry.play_length      = readUInt(_buffer, _fileposition);
      entry.loop_start       = readUInt(_buffer, _fileposition);
      entry.loop_total       = readUInt(_buffer, _fileposition);
      entry.entry_flags      = entry.flags_duration & 0x0000000F;
      entry.duration         = (entry.flags_duration & 0xFFFFFFF0) >> 4;
      entry.format_tag       = (XWBFormat)(entry.format & 0x00000003);
      entry.channels         = (entry.format & 0x0000001C) >> 2;
      entry.samples_per_sec  = (entry.format & 0x007FFFE0) >> 5;
      entry.block_align      = (entry.format & 0x7F800000) >> 23;
      entry.bits_per_sample  = (entry.format & 0x80000000) >> 31;
      if (XWBFormat::XMA        == entry.format_tag) {}
      else if (XWBFormat::WMA   == entry.format_tag) {}
      else if (XWBFormat::PCM   == entry.format_tag) {}
      else if (XWBFormat::ADPCM == entry.format_tag) {}
      entries.push_back(entry);
    }


    _fileposition = entries[0].play_offset;
    auto wavFile = read(_buffer, _fileposition, entries[0].play_length);
    std::ofstream outfile("wavtest.wav", std::ofstream::binary);
    write(outfile, wavFile);
  }
}