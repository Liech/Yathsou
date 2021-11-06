#include "BlueprintDisplay.h"

namespace Athanah {
  BlueprintDisplay::BlueprintDisplay(const nlohmann::json& input) {
    if (input.find("UniformScale") != input.end())
      _scale = input["UniformScale"];
    else
      _scale = 1;
    if (input.find("SpawnRandomRotation") != input.end())
      _randomSpawnRotation = input["SpawnRandomRotation"]!=0;
    else
      _randomSpawnRotation = false;
    if (input.find("PlaceholderMeshName") != input.end())
      _placeholderMeshName = input["PlaceholderMeshName"];
    else
      _placeholderMeshName = "UXB0000";
    if (input.find("ForcedBuildSpin") != input.end())
      _forcedBuildSpin = input["ForcedBuildSpin"];
    else
      _forcedBuildSpin = 0;
    if (input.find("AnimationLand") != input.end())
      _animationLand = input["AnimationLand"];
    else
      _animationLand = "";
  }

  BlueprintDisplay::BlueprintDisplay() {
    _scale = 1;
    _randomSpawnRotation = true;
    _placeholderMeshName = "UXB0000";
    _forcedBuildSpin = 0;
    _animationLand = "";
  }

  float BlueprintDisplay::scale() const {
    return _scale;
  }

  bool BlueprintDisplay::randomSpawnRotation() const{
    return _randomSpawnRotation;
  }

  std::string BlueprintDisplay::placeholderMeshName() const{
    return _placeholderMeshName;
  }

  float BlueprintDisplay::forcedBuildSpin() const{
    return _forcedBuildSpin;
  }

  std::string BlueprintDisplay::animationLand() const{
    return _animationLand;
  }

}