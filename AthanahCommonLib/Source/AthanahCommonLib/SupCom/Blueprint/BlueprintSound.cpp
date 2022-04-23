#include "BlueprintSound.h"

namespace Athanah {
  BlueprintSound::BlueprintSound(const nlohmann::json& input) {
    _bank = input["Bank"];
    _cue = input["Cue"];
    if (input.find("LodCutoff") != input.end())
      _cutoff = EnumConvert::str2SoundLodCutOff(input["LodCutoff"]);
  }

  std::string BlueprintSound::bank() const {
    return _bank;
  }

  std::string BlueprintSound::name() const {
    return _cue;
  }

  SoundLodCutOff BlueprintSound::cutoff() const {
    return _cutoff;
  }
}