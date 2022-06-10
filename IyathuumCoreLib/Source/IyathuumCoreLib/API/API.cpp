#include "API.h"

namespace Iyathuum {
  API::API(const std::string& name) {
    _name = name;
  }

  void API::addFunction(std::unique_ptr<APIFunction> func) {
    _functions.push_back(std::move(func));
  }

  void API::setDescription(const std::string& desc) {
    _description = desc;
  }

  size_t API::numberOfFunctions() const {
    return _functions.size();
  }

  APIFunction& API::getFunction(size_t number) {
    return *_functions[number];
  }
}