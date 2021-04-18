#include "Blueprint.h"

namespace Athanah {
  Blueprint::Blueprint(const std::string id, const nlohmann::json& input) {
    if (input.find("Description") != input.end()) {
      _name = input["Description"];
      _name = _name.substr(_name.find_first_of('>')+1);
    }
    else if (input.find("Description") != input.end())
      _name = id;

    _id = id;
  }

  Blueprint::Blueprint(const std::string id) {
    _name = id;
    _id = id;
  }

  std::string Blueprint::getName() const {
    return _name;
  }
}