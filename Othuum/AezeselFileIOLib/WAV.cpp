#include "WAV.h"

namespace Aezesel {
  void WAV::writeWav(std::string filename) {
    std::ofstream outfile(filename, std::ofstream::binary);
    writeRIFFHeader(outfile);
    writeFMTHeader(outfile);
    writeDataHeader(outfile);
  }

  void WAV::writeRIFFHeader(std::ofstream& out) {
    writeString(out,"RIFF");
    const int fmtSize = 20;
    const int riffSize = 8;
    const int dataHeader = 8;
    writeUInt(out, data.size() + fmtSize + riffSize + dataHeader); //file size
    writeString(out, "WAVE");
  }

  void WAV::writeFMTHeader(std::ofstream& out) {
    writeString(out, "fmt "); //magic byte
    bool endianSwap = true;
    writeUInt(out, 16              , endianSwap); ///header length
    writeUShort(out, 1             , endianSwap);//formatTag
    writeUShort(out, channels      , endianSwap);
    writeUInt  (out, sampleRate    , endianSwap);
    writeUInt  (out, bytesPerSecond, endianSwap);
    writeUShort(out, blockAlign    , endianSwap);
    writeUShort(out, bitsPerSample , endianSwap);
  }

  void WAV::writeDataHeader(std::ofstream& out) {
    writeString(out, "data");
    writeUInt(out, data.size());
    write(out,data);
  }

}