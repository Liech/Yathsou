#include "Blueprint.h"

namespace Athanah {
  Blueprint::Blueprint(const nlohmann::json& input) {
    _name = input["Description"];
    _name = _name.substr(_name.find_first_of('>') + 1);
  }

  std::string Blueprint::getName() const {
    return _name;
  }
}