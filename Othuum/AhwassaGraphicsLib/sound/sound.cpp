#include "sound.h"

#include <filesystem>
#include <math.h>
#include "lib/portaudio/portaudio.h"
#include "IyathuumCoreLib/BaseTypes/Sound.h"

namespace Ahwassa
{

  /* This routine will be called by the PortAudio engine when audio is needed.
  ** It may called at interrupt level on some machines so don't do anything
  ** that could mess up the system like calling malloc() or free().
  */
  int sound::patestCallback(const void* inputBuffer, void* outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    unsigned long statusFlags,
    void* userData)
  {
    float* out = (float*)outputBuffer;
    Ahwassa::sound* s = (Ahwassa::sound*)userData;
    
    (void)timeInfo; /* Prevent unused variable warnings. */
    (void)statusFlags;
    (void)inputBuffer;
    
    for (size_t i = 0; i < framesPerBuffer*s->_sound->numberOfChannels(); i++)
    {
      if (s->_sound->sampleSize() <= s->_position + i)
        break;
      *out++ = s->_sound->sample(s->_position + i) * 0.9;
    }
    s->_position += framesPerBuffer * s->_sound->numberOfChannels();
    return paContinue;
  }

  /*
   * This routine is called by portaudio when playback is done.
   */
  static void StreamFinished(void* userData)
  {
    //paTestData* data = (paTestData*)userData;
    //printf("Stream Completed: %s\n", data->message);
  }


  void sound::play(Iyathuum::Sound* sound)
  {
    int FRAMES_PER_BUFFER = 64;
    
    _sound = sound;

    PaStreamParameters outputParameters;
    PaStream* stream;
    PaError err;
    int i;
    
    err = Pa_Initialize();
    if (err != paNoError) goto error;
    
    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    if (outputParameters.device == paNoDevice) {
      //fprintf(stderr, "Error: No default output device.\n");
      goto error;
    }
    outputParameters.channelCount = _sound->numberOfChannels();       /* stereo output */
    outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;
    
    err = Pa_OpenStream(
      &stream,
      NULL, /* no input */
      &outputParameters,
      (double)_sound->sampleRate(),
      FRAMES_PER_BUFFER,
      paClipOff,      /* we won't output out of range samples so don't bother clipping them */
      patestCallback,
      this);
    if (err != paNoError) goto error;
    
    //sprintf(data.message, "No Message");
    err = Pa_SetStreamFinishedCallback(stream, &StreamFinished);
    if (err != paNoError) goto error;
    
    err = Pa_StartStream(stream);
    if (err != paNoError) goto error;
    
    //printf("Play for %d seconds.\n", NUM_SECONDS);
    Pa_Sleep((_sound->lengthInSeconds()+1) * 1000);
    
    err = Pa_StopStream(stream);
    if (err != paNoError) goto error;
    
    err = Pa_CloseStream(stream);
    if (err != paNoError) goto error;
    
    Pa_Terminate();
    //printf("Test finished.\n");
    
    return;
    error:
      Pa_Terminate();
      //fprintf(stderr, "An error occured while using the portaudio stream\n");
      //fprintf(stderr, "Error number: %d\n", err);
      //fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
      return;
  }
}