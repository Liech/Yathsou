#pragma once

#include <string>
#include <memory>

namespace Iyathuum {
  class Sound;
}

namespace Aezesel {
  class SoundIO {
  public:
    std::unique_ptr<Iyathuum::Sound> read(const std::string& filename);
    void                             write(const std::string&, const Iyathuum::Sound&);
  private:
  };
}