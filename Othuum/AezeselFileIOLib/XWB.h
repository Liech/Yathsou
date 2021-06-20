#pragma once

#include <string>
#include "SupremeCommander/IO.h"

//http://wiki.xentax.com/index.php/XBOX_XWB3
namespace Aezesel {
  struct XWBEntry {
    unsigned int flags_duration;
    unsigned int format        ;
    unsigned int play_offset   ;
    unsigned int play_length   ;
    unsigned int loop_start    ;
    unsigned int loop_total    ;
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