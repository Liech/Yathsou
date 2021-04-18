#include "BlueprintGeneral.h"

namespace Athanah {
  BlueprintGeneral::BlueprintGeneral(const nlohmann::json& input) {
    _faction = input["FactionName"];

    if (input.find("UnitName") != input.end()) {
      _unitName = input["UnitName"];
      _unitName = _unitName.substr(_unitName.find_first_of('>')+1);
    }
    else
      _unitName = "Undefined";

    if (input.find("TechLevel") != input.end()) {
      std::string lvl = input["TechLevel"];
      if (lvl == "RULEUTL_Basic")
        _techLevel = TechLevel::T1;
      else if (lvl == "RULEUTL_Advanced")
        _techLevel = TechLevel::T2;
      else if (lvl == "RULEUTL_Secret")
        _techLevel = TechLevel::T3;
      else if (lvl == "RULEUTL_Experimental")
        _techLevel = TechLevel::T4;
      else
        throw std::runtime_error("Unkown Tech Level");
    }
    else
      _techLevel = TechLevel::T1;
  }

  BlueprintGeneral::BlueprintGeneral() {
    _faction = "None";
    _unitName = "Undefined";
    _techLevel = TechLevel::T0;
  }

  const std::string BlueprintGeneral::faction() {
    return _faction;
  }

  const std::string BlueprintGeneral::unitName() {
    return _unitName;
  }

  const TechLevel BlueprintGeneral::techLevel() {
    return _techLevel;
  }

  const std::string BlueprintGeneral::techLevelString() {
    if (_techLevel == TechLevel::T0)
      return "No Tech";
    else if (_techLevel == TechLevel::T1)
      return "T1";
    else if (_techLevel == TechLevel::T2)
      return "T2";
    else if (_techLevel == TechLevel::T3)
      return "T3";
    else if (_techLevel == TechLevel::T4)
      return "Experimental";
    throw std::runtime_error("Unkown Tech Level");
  }
}