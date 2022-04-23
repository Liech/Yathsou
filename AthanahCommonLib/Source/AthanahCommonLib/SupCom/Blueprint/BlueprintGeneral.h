#pragma once

#include <nlohmann/json.hpp>
#include "BlueprintBase.h"
#include <memory>
#include "AthanahCommonLib/SupCom/SupComEnums.h"

namespace Athanah {
  class BlueprintCommandCaps;


  class BlueprintGeneral : public BlueprintBase {
  public:
    BlueprintGeneral(const nlohmann::json& input);
    BlueprintGeneral();
    ~BlueprintGeneral() = default;

    const Faction     faction();
    const std::string icon();
    const std::string unitName();

    float weight();
    int   selectionPriority();
    const std::string classification();
    const std::string category();
    const BlueprintCommandCaps& commands();

  private:
    std::shared_ptr< BlueprintCommandCaps> _commands;

    Faction     _faction;
    std::string _unitName;
    std::string _icon;
    float       _weight;
    int         _selectionPriority;
    std::string _classification;
    std::string _category;
  };
}