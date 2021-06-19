#pragma once

#include <string>
#include <vector>
#include "SupremeCommander/IO.h"

//http://wiki.xentax.com/index.php/XBOX_XSB
//https://github.com/fesh0r/xnb_parse/blob/master/xnb_parse/xact/xsb.py
// https://github.com/vgmstream/vgmstream/blob/master/src/meta/xwb_xsb.h
//this format does not look like the same. lets just crawl the last entries
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