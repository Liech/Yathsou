#pragma once

#include "AezeselFileIOLib/lib/json.hpp"
#include <memory>
#include "SupComEnums.h"

namespace Athanah {
  class BlueprintCommandCaps;


  class BlueprintGeneral {
  public:
    BlueprintGeneral(const nlohmann::json& input);
    BlueprintGeneral();
    ~BlueprintGeneral() = default;

    const Faction     faction();
    const std::string icon();
    const std::string unitName();
    const TechLevel   techLevel();
    const std::string techLevelString();

    float weight();
    int   selectionPriority();
    const std::string classification();
    const std::string category();
    const BlueprintCommandCaps& commands();

  private:
    std::shared_ptr< BlueprintCommandCaps> _commands;

    Faction     _faction;
    std::string _unitName;
    TechLevel   _techLevel;
    std::string _icon;
    float       _weight;
    int         _selectionPriority;
    std::string _classification;
    std::string _category;
  };
}