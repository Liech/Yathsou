#pragma once

#include <string>
#include <vector>
#include "AezeselFileIOLib/IO.h"

//http://wiki.xentax.com/index.php/XBOX_XSB //this format is wrong?
//https://github.com/fesh0r/xnb_parse/blob/master/xnb_parse/xact/xsb.py //this is the implemented
//https://github.com/vgmstream/vgmstream/blob/master/src/meta/xwb_xsb.h //this looks too complicated

namespace Aezesel {
  //Sound bank files (supremme commander and maybe other xbox related games)
  //xsb files contains names for xwb files
  class XSB : IO{
  public:
    std::vector<std::string> load(std::string filepath);
  private:
    std::vector<std::string> loadInternal();

    std::string filepath;
    size_t                     _fileposition;
    std::vector<unsigned char> _buffer;
  };
}