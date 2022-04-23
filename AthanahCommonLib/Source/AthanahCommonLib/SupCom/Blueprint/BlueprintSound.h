#pragma once

#include <nlohmann/json.hpp>

#include "AthanahCommonLib/SupCom/SupComEnums.h"

namespace Athanah {
  class BlueprintSound{
    public:
    BlueprintSound(const nlohmann::json&);

    std::string    bank  () const;
    std::string    name  () const;
    SoundLodCutOff cutoff() const;

    private:
    std::string    _bank;
    std::string    _cue;
    SoundLodCutOff _cutoff = SoundLodCutOff::None;
  };
}