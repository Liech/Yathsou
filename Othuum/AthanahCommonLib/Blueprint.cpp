#include "Blueprint.h"
#include "BlueprintGeneral.h"

namespace Athanah {
  Blueprint::Blueprint(const std::string id, const nlohmann::json& input) {
    if (input.find("Description") != input.end()) {
      _name = input["Description"];
      _name = _name.substr(_name.find_first_of('>')+1);
    }
    else if (input.find("Description") != input.end())
      _name = id;

    _general = std::make_shared<BlueprintGeneral>(input["General"]);

    _id = id;
  }

  Blueprint::Blueprint(const std::string id) {
    _name = id;
    _id = id;
    _general = std::make_shared<BlueprintGeneral>();
  }

  std::string Blueprint::getName() const {
    return _name;
  }

  BlueprintGeneral& Blueprint::general() const {
    return *_general;
  }
}