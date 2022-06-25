#include "Conversion.h"

#include "FunctionRelay.h"

#include <python3.10/Python.h>
#include <pybind11/embed.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>

namespace Haas {
  namespace Python {
    nlohmann::json Conversion::py2j(const pybind11::object& input, Python::FunctionRelay& relay) {
      //maybe this is a better way if it would work: https://github.com/pybind/pybind11/issues/1914
      auto typ = input.get_type().str().cast<std::string>();

      if (typ == "<class 'float'>")
        return input.cast<float>();
      else if (typ == "<class 'int'>")
        return input.cast<int>();
      else if (typ == "<class 'str'>")
        return input.cast<std::string>();
      else if (typ == "<class 'dict'>") {
        nlohmann::json result;
        pybind11::dict d = input;
        for (auto& x : d) {
          result[x.first.cast<std::string>()] = py2j(x.second.cast<pybind11::object>(), relay);
        }
        return result;
      }
      else if (typ == "<class 'list'>") {
        nlohmann::json result = nlohmann::json::array();
        pybind11::list d = input;
        for (auto& x : d)
          result.push_back(py2j(x.cast<pybind11::object>(), relay));
        return result;
      }
      else if (typ == "<class 'function'>") {
        return relay.addFunction(input);
      }
      else if (typ == "<class 'NoneType'>")
        return nlohmann::json();
      else
        throw std::runtime_error("Unkown pybind11 object type to json conversion");
    }

    pybind11::object Conversion::j2py(const nlohmann::json& input) {
      if (input.is_boolean())
        return pybind11::cast((bool)input);
      else if (input.is_number_unsigned())
        return pybind11::cast((unsigned int)input);
      else if (input.is_number_integer())
        return pybind11::cast((int)input);
      else if (input.is_number_float())
        return pybind11::cast((float)input);
      else if (input.is_string())
        return pybind11::cast((std::string)input);
      else if (input.is_null())
        return pybind11::none();
      else if (input.is_object()) {
        pybind11::dict result;
        for (auto& x : input.items()) {
          auto& val = x.value();
          result[x.key().c_str()] = j2py(val);
        }
        return result;
      }
      else if (input.is_array()) {
        pybind11::list result;
        for (int i = 0; i < input.size(); i++)
          result.append(j2py(input[i]));
        return result;
      }
      else
        throw std::runtime_error("Unkown json to pybind11 object type conversion");
    }
  }
}