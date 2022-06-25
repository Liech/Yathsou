#pragma once

#include <nlohmann/json.hpp>

namespace pybind11 {
  class object;
}

namespace Haas {

  namespace Python {
    class FunctionRelay;

    class Conversion {
      public:
      static nlohmann::json   py2j(const pybind11::object&, Python::FunctionRelay&);
      static pybind11::object j2py(const nlohmann::json&);
    };
  }
}