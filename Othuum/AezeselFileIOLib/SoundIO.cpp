#include "SoundIO.h"

#include "lib/libnyquist/Decoders.h"
#include "lib/libnyquist/Encoders.h"

namespace Aezesel {
  void SoundIO::read(std::string filename) {
    nqr::NyquistIO loader;
    nqr::NyquistFileBuffer memory = nqr::ReadFile(filename);
  }
}