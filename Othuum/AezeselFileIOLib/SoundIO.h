#pragma once

#include <string>
#include <memory>

namespace Iyathuum {
  class Sound;
}

namespace Aezesel {
  class SoundIO {
  public:
    std::unique_ptr<Iyathuum::Sound> read(std::string filename);
  private:
  };
}