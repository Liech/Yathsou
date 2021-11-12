#include "BlueprintGeneral.h"
#include "BlueprintCommandCaps.h"

namespace Athanah {
  BlueprintGeneral::BlueprintGeneral(const nlohmann::json& input) {

    std::string fact = input["FactionName"];
    if (fact == "Aeon")
      _faction = Faction::Aeon;
    else if (fact == "UEF")
      _faction = Faction::Uef;
    else if (fact == "Seraphim")
      _faction = Faction::Seraphim;
    else if (fact == "Cybran")
      _faction = Faction::Cybran;
    else
      _faction = Faction::Undefined;

    if (input.find("CommandCaps") != input.end())
      _commands = std::make_shared<BlueprintCommandCaps>(input["CommandCaps"]);
    else
      _commands = std::make_shared<BlueprintCommandCaps>();

    _unitName          = read<std::string>("UnitName"         , input, "Undefined");
    _category          = read<std::string>("Category"         , input, "Undefined");
    _icon              = read<std::string>("Icon"             , input, "Undefined");
    _weight            = read<float      >("UnitWeight"       , input, 1.0f);
    _selectionPriority = read<int        >("SelectionPriority", input, 1);
    _classification    = read<std::string>("Classification"   , input, "RULEUC_Undefined");

    _classification = _classification.substr(std::string("RULEUC_").size());
    _unitName = _unitName.substr(_unitName.find_first_of('>') + 1);

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
    _faction           = Faction::Undefined;
    _unitName          = "Undefined";
    _icon              = "Undefined";
    _techLevel         = TechLevel::T0;
    _weight            = 1;
    _selectionPriority = 1;
    _classification    = "Undefined";
    _category          = "Undefined";
    _commands = std::make_shared<BlueprintCommandCaps>();
  }

  const Faction BlueprintGeneral::faction() {
    return _faction;
  }

  const std::string BlueprintGeneral::icon() {
    return _icon;
  }

  const std::string BlueprintGeneral::unitName() {
    return _unitName;
  }

  const TechLevel BlueprintGeneral::techLevel() {
    return _techLevel;
  }

  float BlueprintGeneral::weight() {
    return _weight;
  }

  int BlueprintGeneral::selectionPriority() {
    return _selectionPriority;
  }

  const std::string BlueprintGeneral::classification() {
    return _classification;
  }

  const std::string BlueprintGeneral::category() {
    return _category;
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

  const BlueprintCommandCaps& BlueprintGeneral::commands() {
    return *_commands;
  }
}