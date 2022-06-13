#pragma once

#include <nlohmann/json.hpp>

namespace pybind11 {
  class object;
}

namespace Haas {
  class PyFunctionRelay;

  class PyConversion {
    public:
      static nlohmann::json   py2j(const pybind11::object&, PyFunctionRelay&);
      static pybind11::object j2py(const nlohmann::json&);
  };
}