#include "SoundEngine.h"

#include <math.h>
#include <stdexcept>
#include <portaudio.h>

namespace Ahwassa
{

  /* This routine will be called by the PortAudio engine when audio is needed.
  ** It may called at interrupt level on some machines so don't do anything
  ** that could mess up the system like calling malloc() or free().
  */
  int SoundHandler::paCallback(const void* inputBuffer, void* outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    unsigned long statusFlags,
    void* userData)
  {
    float* out = (float*)outputBuffer;
    SoundHandler* s = (SoundHandler*)userData;

    (void)timeInfo; /* Prevent unused variable warnings. */
    (void)statusFlags;
    (void)inputBuffer;

    for (size_t i = 0; i < framesPerBuffer * s->_sound.numberOfChannels(); i++)
    {
      if (s->_sound.sampleSize() <= s->_position + i)
        break;
      *out++ = s->_sound.sample(s->_position + i) * 0.9;
    }
    s->_position += framesPerBuffer * s->_sound.numberOfChannels();
    if (s->_position >= s->_sound.sampleSize())
      return paComplete;
    else
      return paContinue;
  }

  /*
   * This routine is called by portaudio when playback is done.
   */
  void SoundHandler::StreamFinished(void* userData)
  {
    SoundHandler* data = (SoundHandler*)userData;
    data->streamFinised();
  }

  SoundEngine::SoundEngine() {
    PaStream* stream;
    PaError err = Pa_Initialize();
    if (err != paNoError)
      throw std::runtime_error("Error on initialization of PortAudio");
  }

  SoundEngine::~SoundEngine() {

    Pa_Terminate();
  }

  void SoundEngine::playAndForget(const Iyathuum::Sound& sound)
  {

  }

  std::shared_ptr<SoundHandler> SoundEngine::createHandler(const Iyathuum::Sound& sound)
  {
    std::shared_ptr<SoundHandler> result = std::make_shared<SoundHandler>(sound);

    return result;
  }

  SoundHandler::SoundHandler(const Iyathuum::Sound& sound) : _sound(sound) {
    _parameters = std::make_unique< PaStreamParameters>();
    _parameters->device = Pa_GetDefaultOutputDevice();
    if (_parameters->device == paNoDevice)
      throw std::runtime_error("No device available");
    _parameters->channelCount = sound.numberOfChannels();       /* stereo output */
    _parameters->sampleFormat = paFloat32; /* 32 bit floating point output */
    _parameters->suggestedLatency = Pa_GetDeviceInfo(_parameters->device)->defaultLowOutputLatency;
    _parameters->hostApiSpecificStreamInfo = NULL;

    int FRAMES_PER_BUFFER = 64;
    PaError err = Pa_OpenStream(
      &_stream,
      NULL, /* no input */
      _parameters.get(),
      (double)_sound.sampleRate(),
      FRAMES_PER_BUFFER,
      paClipOff,      /* we won't output out of range samples so don't bother clipping them */
      paCallback,
      this);

    if (err != paNoError)
      throw std::runtime_error("Could not play sound");

  }

  SoundHandler::~SoundHandler() {
    if (isRunning())
      Pa_AbortStream(_stream);    
  }

  void SoundHandler::abort() {
    if (isRunning())
      Pa_AbortStream(_stream);
  }

  bool SoundHandler::isRunning() {
    return Pa_IsStreamActive(_stream);
  }

  void SoundHandler::play() {
    if (isRunning())
      Pa_AbortStream(_stream);

    _position = 0;

    PaError err = Pa_SetStreamFinishedCallback(_stream, &StreamFinished);
    err = Pa_StartStream(_stream);
    if (err != paNoError)
      throw std::runtime_error("Could not start stream");
    //Pa_Sleep((_sound.lengthInSeconds() + 1) * 1000);
  }

}