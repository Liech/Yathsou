#pragma once

#include <string>
#include <memory>
#include "AezeselFileIOLib/IO.h"

namespace Iyathuum {
  class Sound;
}

//https://github.com/fesh0r/xnb_parse/blob/master/xnb_parse/xact/xwb.py
//http://wiki.xentax.com/index.php/XBOX_XWB3
namespace Aezesel {
  //Sound bank files (supremme commander and maybe other xbox related games)
  //the corresponding xsb files contains correct names
  class XWB : IO{
  public:
    std::vector<std::unique_ptr<Iyathuum::Sound>> load(std::string filename);

  private:
    std::vector<std::unique_ptr<Iyathuum::Sound>> loadInternal();

    size_t                     _fileposition = 0;
    std::vector<unsigned char> _buffer;
  };
}