#pragma once

#include "AezeselFileIOLib/lib/json.hpp"

namespace Athanah {
  enum class TechLevel {
    T0,T1,T2,T3,T4
  };

  class BlueprintGeneral {
  public:
    BlueprintGeneral(const nlohmann::json& input);
    BlueprintGeneral();
    ~BlueprintGeneral() = default;

    const std::string faction();
    const std::string unitName();
    const TechLevel   techLevel();
    const std::string techLevelString();

  private:
    std::string _faction;
    std::string _unitName;
    TechLevel   _techLevel;
  };
}