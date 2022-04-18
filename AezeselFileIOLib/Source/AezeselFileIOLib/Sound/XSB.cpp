#include "XSB.h"

#include <map>

namespace Aezesel {
  std::vector<std::string> XSB::load(std::string filename) {
    _fileposition = 0;
    std::ifstream input(filename, std::ios::binary);
    if (input.fail())
      return std::vector<std::string>();
    _buffer = std::vector<unsigned char>(std::istreambuf_iterator<char>(input), {});
    return loadInternal();
  }

  std::vector<std::string> XSB::loadInternal() {
    //https://github.com/fesh0r/xnb_parse/blob/master/xnb_parse/xact/xsb.py
    //https://docs.python.org/3/library/struct.html
    //4s         | h_sig
    std::string signature = readString(_buffer, _fileposition,4);
    if (signature != "SDBK")
      throw std::runtime_error("Magic byte wrong");
    //H ushort   | self.version
    unsigned short version = readUShort(_buffer, _fileposition);
    //H ushort   | self.header_version
    unsigned short headerversion = readUShort(_buffer, _fileposition);
    //H ushort   | self.crc
    unsigned short crc = readUShort(_buffer, _fileposition);
    // 
    //I uint     | buildtime_raw_low
    unsigned int buildtimeRawLow = readUInt(_buffer, _fileposition);
    //I uint     | buildtime_raw_high          
    unsigned int buildtimeRawHigh = readUInt(_buffer, _fileposition);
    // 
    //B uchar    | self.platform
    unsigned char platform = read(_buffer, _fileposition, 1)[0];
    // 
    //H          | h_simple_cue_count
    unsigned short h_simple_cue_count = readUShort(_buffer, _fileposition);
    //H          | h_complex_cue_count
    unsigned short h_complex_cue_count = readUShort(_buffer, _fileposition);
    //H          | h_unknown_count
    unsigned short h_unknown_count = readUShort(_buffer, _fileposition);
    //H          | h_cue_name_hash_count
    unsigned short h_cue_name_hash_count = readUShort(_buffer, _fileposition);
    //B          | h_wave_bank_count
    unsigned char h_wave_bank_count = read(_buffer, _fileposition, 1)[0];
    //H          | h_sound_count
    unsigned short h_sound_count = readUShort(_buffer, _fileposition);

    //I          | h_cue_names_length
    unsigned int h_cue_names_length = readUInt(_buffer, _fileposition);

     
    //i          | simple_cue_offset_raw
    int            simple_cue_offset_raw = readUInt(_buffer, _fileposition);
    //i          | complex_cue_offset_raw
    int            complex_cue_offset_raw = readUInt(_buffer, _fileposition);
    //i          | cue_name_offset_raw
    int            cue_name_offset_raw = readUInt(_buffer, _fileposition);
    //i          | unknown_offset_raw
    int            unknown_offset_raw = readUInt(_buffer, _fileposition);
    //i          | variation_offset_raw
    int            variation_offset_raw = readUInt(_buffer, _fileposition);
    //i          | transition_offset_raw
    int            transition_offset_raw = readUInt(_buffer, _fileposition);
    //i          | wave_bank_offset_raw
    int            wave_bank_offset_raw = readUInt(_buffer, _fileposition);
    //i          | cue_name_hash_offset_raw
    int            cue_name_hash_offset_raw = readUInt(_buffer, _fileposition);
    //i          | cue_name_table_offset_raw
    int            cue_name_table_offset_raw = readUInt(_buffer, _fileposition);
    //i          | sound_offset_raw
    int            sound_offset_raw = readUInt(_buffer, _fileposition);
    //64s        | h_name_raw
    std::string name = readString(_buffer, _fileposition, 64);

    std::vector<std::string> waveBankNames;
    if (h_wave_bank_count && wave_bank_offset_raw > 0) {
      _fileposition = wave_bank_offset_raw;
      for (int i = 0; i < h_wave_bank_count; i++) {
        waveBankNames.push_back(readString(_buffer, _fileposition, 64));
      }
    }

    std::vector<unsigned short> cue_name_hash;
    if (h_cue_name_hash_count && cue_name_hash_offset_raw > 0) {
      _fileposition = cue_name_hash_offset_raw;
      for (int i = 0; i < h_cue_name_hash_count; i++) {
        cue_name_hash.push_back(readUShort(_buffer, _fileposition));
      }
    }

    std::map<int, unsigned short> cue_name_hash_entry;
    if (h_cue_names_length && cue_name_table_offset_raw > 0) {
      _fileposition = cue_name_table_offset_raw;
      for (int i = 0; i < h_simple_cue_count + h_complex_cue_count; i++) {
        int key = readInt(_buffer, _fileposition);  //maybe order wrong
        unsigned short value = readUShort(_buffer, _fileposition);//maybe order wrong
        cue_name_hash_entry[key] = value;
      }
    }

    std::vector<std::string> cue_names;
    for (auto k : cue_name_hash_entry) {
      _fileposition = k.first;
      cue_names.push_back(readString(_buffer, _fileposition));
    }
    return cue_names;
  }
}