#include "BlueprintDisplay.h"

namespace Athanah {
  BlueprintDisplay::BlueprintDisplay(const nlohmann::json& input) {
    _scale               = read<float>      ("UniformScale"       , input, 1);
    _randomSpawnRotation = readBool         ("SpawnRandomRotation", input, false);
    _placeholderMeshName = read<std::string>("PlaceholderMeshName", input, "UXB0000");
    _forcedBuildSpin     = read<float>      ("ForcedBuildSpin"    , input, 0);
    _animationLand       = read<std::string>("AnimationLand"      , input, "");
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