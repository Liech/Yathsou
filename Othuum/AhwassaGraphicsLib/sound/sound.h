#pragma once

#include <memory>
namespace nqr
{
  struct AudioData;
}
struct PaStreamCallbackTimeInfo;

namespace Iyathuum {
  class Sound;
}

namespace Ahwassa
{
  class sound
  {
  public:
    void play(Iyathuum::Sound*);

  private:
    size_t           _position = 0;
    Iyathuum::Sound* _sound;

    static int patestCallback(const void* inputBuffer, void* outputBuffer,
      unsigned long framesPerBuffer,
      const PaStreamCallbackTimeInfo* timeInfo,
      unsigned long statusFlags,
      void* userData);
  };
}