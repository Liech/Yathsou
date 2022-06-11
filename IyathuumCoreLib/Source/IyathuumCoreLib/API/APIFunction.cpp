#include "APIFunction.h"

namespace Iyathuum {
  APIFunction::APIFunction(const std::string& name, std::function<nlohmann::json(const nlohmann::json&)> func) {
    _name = name;
    _func = func;
  }

  void APIFunction::setDescription(const std::string& desc) {
    _description = desc;
  }

  nlohmann::json APIFunction::call(const nlohmann::json& input) const {
    return _func(input);
  }

  std::string APIFunction::getDescription() const {
    return _description;
  }

  std::string APIFunction::getName() const {
    return _name;
  }
}