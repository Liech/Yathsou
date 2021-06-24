#pragma once

#include <vector>

namespace Iyathuum {
  class Sound {
  public:
    enum class SampleRates {
      //https://en.wikipedia.org/wiki/Sampling_(signal_processing)
      BadTelephone     = 8000,
      QuarterCDQuality = 11025,
      VoIPTelephone    = 16000,
      HalfCDQuality    = 22050,
      FMRadio          = 32000,
      CDXAAudio        = 37800,
      TelevisionNTSC   = 44056,
      AudioCD          = 44100,
      ProfessionalVideo= 48000,
      ProfessionalCD   = 88200,
      //...
    };

    SampleRates sampleRate();
    void setSampleRate(SampleRates);

    int  numberOfChannels();
    void setNumberOfChannels(int);

    size_t sampleSize();
    void   setSampleData(const std::vector<float>&);
    float  sample(size_t position);

    int    frameSize();
    double lengthInSeconds();

    float* data() { return _samples.data(); }
  private:
    SampleRates        _sampleRate       = SampleRates::AudioCD;
    int                _numberOfChannels = 1;
    std::vector<float> _samples;
  };
}