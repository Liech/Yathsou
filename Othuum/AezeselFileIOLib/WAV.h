#pragma once

#include "SupremeCommander/IO.h"

namespace Aezesel {
  class WAV : private IO{
  public:
    void writeWav(std::string filename);

    //HEADER
    //"FMT "
    //uint  Header length
    unsigned short formatTag = 0;
    unsigned short channels = 1;
    unsigned int   sampleRate = 44100;
    unsigned int   bytesPerSecond;
    unsigned short blockAlign;
    unsigned short bitsPerSample;

    std::vector<unsigned char> data;

  private:
    size_t fileSizeOffset;
    void writeRIFFHeader(std::ofstream&);
    void writeFMTHeader(std::ofstream&);
    void writeDataHeader(std::ofstream&);
  };
}