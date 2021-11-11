#include "Blueprint.h"
#include "BlueprintGeneral.h"
#include "BlueprintDisplay.h"
#include "BlueprintPhysic.h"

namespace Athanah {
  Blueprint::Blueprint(const std::string id, const nlohmann::json& input) {
    if (input.find("Description") != input.end()) {
      _description = input["Description"];
      _description = _description.substr(_description.find_first_of('>')+1);
    }
    else if (input.find("Description") != input.end())
      _description = id;
    
    if (input.find("StrategicIconName") != input.end()) {
      _strategicIcon = input["StrategicIconName"];
    }
    else if (input.find("StrategicIconName") != input.end())
      _strategicIcon = "";

    _general = std::make_shared<BlueprintGeneral>(input["General"]);
    _display = std::make_shared<BlueprintDisplay>(input["Display"]);
    _physic  = std::make_unique<BlueprintPhysic >(input["Physics"]);
    _id = id;

    _raw = input;
  }

  Blueprint::Blueprint(const std::string id) {
    _description = id;
    _id = id;
    _general = std::make_shared<BlueprintGeneral>();
    _display = std::make_shared<BlueprintDisplay>();
  }

  std::string Blueprint::strategicIcon() const {
    return _strategicIcon;
  }

  std::string Blueprint::description() const {
    return _description;
  }

  BlueprintGeneral& Blueprint::general() const {
    return *_general;
  }

  BlueprintDisplay& Blueprint::display() const {
    return *_display;
  }

  BlueprintPhysic& Blueprint::physic() const {
    return *_physic;
  }

  nlohmann::json Blueprint::getRaw() const {
    return _raw;
  }
}