#pragma once

#include <string>
#include "SupremeCommander/IO.h"

//http://wiki.xentax.com/index.php/XBOX_XSB
namespace Aezesel {
  //Sound bank files (supremme commander and maybe other xbox related games)
  //xsb files contains names for xwb files
  class XSB : IO{
  public:
    XSB(std::string filepath);

  private:
    std::string filepath;
    size_t                     _fileposition;
    std::vector<unsigned char> _buffer;
  };
}