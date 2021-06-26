#pragma once

#include <vector>

namespace Iyathuum {
  class Sound {
  public:
    enum class SampleRate {
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

    SampleRate sampleRate() const;
    void setSampleRate(SampleRate);

    int  numberOfChannels() const;
    void setNumberOfChannels(int);

    size_t sampleSize() const;
    void   setSampleData(const std::vector<float>&);
    float  sample(size_t position) const;

    int    frameSize() const;
    double lengthInSeconds() const;

    float* data() { return _samples.data(); }
  private:
    SampleRate        _sampleRate       = SampleRate::AudioCD;
    int                _numberOfChannels = 1;
    std::vector<float> _samples;
  };
}