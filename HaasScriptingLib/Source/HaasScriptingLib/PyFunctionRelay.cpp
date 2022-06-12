#include "PyFunctionRelay.h"

#include "PyConversion.h"

#include <python3.10/Python.h>
#include <pybind11/embed.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>

namespace Haas {
  class PyFunctionRelay::pimpl {
    public:
    std::map<size_t, pybind11::object> functionMap;
    std::map<pybind11::object, size_t> objectMap;

  };

  PyFunctionRelay::PyFunctionRelay() {
    _pimpl = std::make_unique<PyFunctionRelay::pimpl>();
  }

  nlohmann::json PyFunctionRelay::call(size_t id, const nlohmann::json& input) {
    return PyConversion::py2j(_pimpl->functionMap[id](PyConversion::j2py(input)),*this);
  }

  size_t PyFunctionRelay::addFunction(pybind11::object fun) {
    if (_pimpl->objectMap.count(fun) != 0) {
      return _pimpl->objectMap[fun];
    }
    _pimpl->functionMap[counter] = fun;
    _pimpl->objectMap[fun] = counter;
    size_t result = counter;
    counter++;
    return result;
  }
}