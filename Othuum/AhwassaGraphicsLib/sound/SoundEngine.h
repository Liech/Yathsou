#pragma once

#include <string>
#include <memory>
#include "IyathuumCoreLib/BaseTypes/Sound.h"

struct PaStreamCallbackTimeInfo;
struct PaStreamParameters;
typedef void PaStream;

namespace Ahwassa
{
  class SoundHandler {
  public:
    SoundHandler(const Iyathuum::Sound&);
    ~SoundHandler();
    void play();
    bool isRunning();
    void abort();

  private:
    void streamFinised() {};

    static int paCallback(const void* inputBuffer, void* outputBuffer,
      unsigned long framesPerBuffer,
      const PaStreamCallbackTimeInfo* timeInfo,
      unsigned long statusFlags,
      void* userData);
    static void StreamFinished(void* userData);

    size_t                              _position = 0;
    const Iyathuum::Sound&              _sound     ;    
    PaStream*                           _stream    ;
    std::unique_ptr<PaStreamParameters> _parameters;
  };
  
  class SoundEngine
  {
  public:
    SoundEngine();
    ~SoundEngine();

    void                          playAndForget(const Iyathuum::Sound& sound);
    std::shared_ptr<SoundHandler> createHandler(const Iyathuum::Sound& sound);    
  private:
    std::unique_ptr<PaStreamParameters> _outputParameters;


  };
}