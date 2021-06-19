#pragma once

#include <string>
#include "SupremeCommander/IO.h"

//http://wiki.xentax.com/index.php/XBOX_XWB3
//http://wiki.xentax.com/index.php/XBOX_XSB
namespace Aezesel {
  //Sound bank files (supremme commander and maybe other xbox related games)
  //the corresponding xsb files contains correct names
  class XWB : IO{
  public:
    XWB(std::string filepath);

  private:
    std::string                _filepath;
    size_t                     _fileposition;
    std::vector<unsigned char> _buffer;
  };
}