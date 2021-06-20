#pragma once

#include <string>
#include "SupremeCommander/IO.h"

//https://github.com/fesh0r/xnb_parse/blob/master/xnb_parse/xact/xwb.py
//http://wiki.xentax.com/index.php/XBOX_XWB3
namespace Aezesel {
  enum class XWBFormat {
    PCM   = 0,
    XMA   = 1,
    ADPCM = 2,
    WMA   = 3,
  };

  struct XWBEntry {
    unsigned int flags_duration;
    unsigned int format        ;
    unsigned int play_offset   ;
    unsigned int play_length   ;
    unsigned int loop_start    ;
    unsigned int loop_total    ;
    unsigned int entry_flags    ;
    unsigned int duration       ;
    XWBFormat    format_tag     ;
    unsigned int channels       ;
    unsigned int samples_per_sec;
    unsigned int block_align    ;
    unsigned int bits_per_sample;
  };

  //Sound bank files (supremme commander and maybe other xbox related games)
  //the corresponding xsb files contains correct names
  class XWB : IO{
  public:
    void load(std::string filename);

  private:
    void loadInternal();

    size_t                     _fileposition;
    std::vector<unsigned char> _buffer;
  };
}