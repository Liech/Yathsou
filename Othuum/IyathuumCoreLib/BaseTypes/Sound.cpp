#include "Sound.h"

namespace Iyathuum {



  int Sound::numberOfChannels() {
    return _numberOfChannels;
  }

  void Sound::setNumberOfChannels(int channels) {
    _numberOfChannels = channels;
  }

  Sound::SampleRates Sound::sampleRate() {
    return _sampleRate;
  }

  void Sound::setSampleRate(Sound::SampleRates newSampleRate) {
    _sampleRate = newSampleRate;
  }

  size_t Sound::sampleSize() {
    return _samples.size();
  }

  void Sound::setSampleData(const std::vector<float>& data) {
    _samples = data;
  }

  float Sound::sample(size_t position) {
    return _samples[position];
  }

  int Sound::frameSize() {
    return 4 * numberOfChannels();
  }

  double Sound::lengthInSeconds() {
    return (double)(sampleSize() / frameSize()) / (double)sampleRate();
  }

}