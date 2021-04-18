#include "Blueprint.h"
#include "BlueprintGeneral.h"

namespace Athanah {
  Blueprint::Blueprint(const std::string id, const nlohmann::json& input) {
    if (input.find("Description") != input.end()) {
      _description = input["Description"];
      _description = _description.substr(_description.find_first_of('>')+1);
    }
    else if (input.find("Description") != input.end())
      _description = id;

    _general = std::make_shared<BlueprintGeneral>(input["General"]);

    _id = id;
  }

  Blueprint::Blueprint(const std::string id) {
    _description = id;
    _id = id;
    _general = std::make_shared<BlueprintGeneral>();
  }

  std::string Blueprint::description() const {
    return _description;
  }

  BlueprintGeneral& Blueprint::general() const {
    return *_general;
  }
}