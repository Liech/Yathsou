#pragma once

#include <memory>
namespace nqr
{
  struct AudioData;
}
struct PaStreamCallbackTimeInfo;

namespace Ahwassa
{
  class sound
  {
  public:
    void play();

  private:
    size_t                          _position = 0;
    size_t                          _numberOfChannels = 0;
    std::shared_ptr<nqr::AudioData> _fileData;

    static int patestCallback(const void* inputBuffer, void* outputBuffer,
      unsigned long framesPerBuffer,
      const PaStreamCallbackTimeInfo* timeInfo,
      unsigned long statusFlags,
      void* userData);
  };
}