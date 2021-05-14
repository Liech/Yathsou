#pragma once

#include "AezeselFileIOLib/lib/json.hpp"
#include <memory>
#include <string>
#include "AthanahCommonLib/SupCom/SupComEnums.h"

namespace Athanah {
  class BlueprintCommandCaps;


  class BlueprintDisplay {
  public:
    BlueprintDisplay(const nlohmann::json& input);
    BlueprintDisplay();
    ~BlueprintDisplay() = default;


    float       scale()               const;
    bool        randomSpawnRotation() const;
    std::string placeholderMeshName() const;
    float       forcedBuildSpin()     const;
    std::string animationLand()       const;
  private:
    float       _scale;
    float       _forcedBuildSpin;
    bool        _randomSpawnRotation;
    std::string _placeholderMeshName;
    std::string _animationLand;
    
  };
}