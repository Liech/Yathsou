#include "FunctionRelay.h"

#include "Conversion.h"

#include <python3.10/Python.h>
#include <pybind11/embed.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>

namespace Haas {
  namespace Python {
    class pyobjcmp {
      public:
      bool operator()(const pybind11::object& x, const pybind11::object& y) const {
        return x.ptr() > y.ptr();
      }
    };

    class FunctionRelay::pimpl {
      public:
      std::map<size_t          , pybind11::object          > functionMap;
      std::map<pybind11::object, size_t          , pyobjcmp> objectMap  ;
    };

    FunctionRelay::FunctionRelay() {
      _pimpl = std::make_unique<FunctionRelay::pimpl>();
    }

    nlohmann::json FunctionRelay::call(size_t id, const nlohmann::json& input) {
      return Conversion::py2j(_pimpl->functionMap[id](Conversion::j2py(input)), *this);
    }

    size_t FunctionRelay::addFunction(pybind11::object fun) {
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
}