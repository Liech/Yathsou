#include "SoundIO.h"

#include <filesystem>
#include <algorithm>

#include "lib/libnyquist/Decoders.h"
#include "lib/libnyquist/Encoders.h"

#include "IyathuumCoreLib/BaseTypes/Sound.h"

namespace Aezesel {
  std::unique_ptr<Iyathuum::Sound> SoundIO::read(const std::string& filename) {
    std::string suffix = std::filesystem::path(filename).extension().string().substr(1);
    std::transform(suffix.begin(), suffix.end(), suffix.begin(),
      [](unsigned char c) { return std::tolower(c); });

    if (suffix != "wav" && suffix != "mp3")
      throw std::runtime_error("Unsupported file format");

    nqr::NyquistIO loader;
    nqr::NyquistFileBuffer memory = nqr::ReadFile(filename);    
    std::shared_ptr<nqr::AudioData> fileData = std::make_shared<nqr::AudioData>();
    loader.Load(fileData.get(), suffix, memory.buffer); //also mp3 possible

    std::unique_ptr<Iyathuum::Sound> result = std::make_unique<Iyathuum::Sound>();
    result->setSampleRate((Iyathuum::Sound::SampleRate)fileData->sampleRate);
    result->setNumberOfChannels(fileData->channelCount);
    result->setSampleData(fileData->samples);
    return result;
  }

  void SoundIO::write(const std::string&, const Iyathuum::Sound&) {
    throw std::runtime_error("Not implemented yet");
  }

}