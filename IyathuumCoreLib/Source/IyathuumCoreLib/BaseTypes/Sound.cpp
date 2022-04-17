#include "Sound.h"

namespace Iyathuum {



  int Sound::numberOfChannels()  const {
    return _numberOfChannels;
  }

  void Sound::setNumberOfChannels(int channels) {
    _numberOfChannels = channels;
  }

  Sound::SampleRate Sound::sampleRate()  const {
    return _sampleRate;
  }

  void Sound::setSampleRate(Sound::SampleRate newSampleRate) {
    _sampleRate = newSampleRate;
  }

  size_t Sound::sampleSize()  const {
    return _samples.size();
  }

  void Sound::setSampleData(const std::vector<float>& data) {
    _samples = data;
  }

  float Sound::sample(size_t position)  const {
    return _samples[position];
  }

  int Sound::frameSize() const {
    return 4 * numberOfChannels();
  }

  double Sound::lengthInSeconds()  const {
    return (double)(sampleSize() / frameSize()) / (double)sampleRate();
  }

}