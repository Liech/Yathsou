#include "PythonEngine.h"

#include <IyathuumCoreLib/API/API.h>
#include <IyathuumCoreLib/API/APIFunction.h>
#include <IyathuumCoreLib/API/FunctionRelay.h>

#include <python3.10/Python.h>
#include <pybind11/embed.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>

#include <iostream>


namespace Haas {
  class PythonEngine::pimpl {
    public:
      pybind11::module_ mainModule;
  };

  PythonEngine& PythonEngine::instance() {
    static PythonEngine engine;
    return engine;
  }

  PythonEngine::~PythonEngine() {
    if (_initialized)
      throw std::runtime_error("Please dispose the PythonEngine correctly");
  }

  PythonEngine::PythonEngine() {
  }
  
  PYBIND11_EMBEDDED_MODULE(HaasModule, m) {
    PythonEngine& engine = PythonEngine::instance();

    for (size_t apiID = 0; apiID < engine.numberOfApis(); apiID++) {
      auto& api = engine.getAPI(apiID);
      for (size_t f = 0; f < api.numberOfFunctions(); f++) {
        auto& func = api.getFunction(f);
        m.def(func.getName().c_str(), [&func](const pybind11::object& input) {
          return PythonEngine::j2py(func.call(PythonEngine::py2j(input))); 
          }, pybind11::arg("input") = pybind11::none());
      }
    }
  } 

  void PythonEngine::initialize() {
    assert(!_initialized);
    _initialized = true;
    _pimpl = std::make_unique<PythonEngine::pimpl>();

    try {
      Py_SetPythonHome(L"Data/python");
      pybind11::initialize_interpreter();
      _pimpl->mainModule = pybind11::module_::import("HaasModule");
    }
    catch (pybind11::error_already_set& e) {
      std::cout << e.what() << std::endl;
      throw;
    } 
  }

  void PythonEngine::execute(const std::string& pythonCode) {
    try {
      auto locals = pybind11::dict(**_pimpl->mainModule.attr("__dict__"));
      pybind11::exec(pythonCode, pybind11::globals(), locals);
    } 
    catch (pybind11::error_already_set& e) {
      std::cout << e.what() << std::endl;
      throw;
    }
  }

  void PythonEngine::dispose() {
    assert(_initialized);
    _pimpl = nullptr;
    pybind11::finalize_interpreter();
    _initialized = false;
  }

  void PythonEngine::addAPI(std::unique_ptr<Iyathuum::API> api) {
    assert(!_initialized);
    _apis.push_back(std::move(api));
  }

  size_t PythonEngine::numberOfApis() const {
    return _apis.size();
  }

  Iyathuum::API& PythonEngine::getAPI(size_t number) {
    return *_apis[number];
  }

  nlohmann::json PythonEngine::py2j(const pybind11::object& input) {
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
        result[x.first.cast<std::string>()] = py2j(x.second.cast<pybind11::object>());
      }
      return result;
    }
    else if (typ == "<class 'list'>") {
      nlohmann::json result = nlohmann::json::array();
      pybind11::list d = input;
      for (auto& x : d)
        result.push_back(py2j(x.cast<pybind11::object>()));
      return result;
    }
    else if (typ == "<class 'function'>") {
      return py2j(input(6));
    }
    else 
      throw std::runtime_error("Unkown pybind11 object type to json conversion");
  }

  pybind11::object PythonEngine::j2py(const nlohmann::json& input) {
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

  class FRMOCK : public Iyathuum::FunctionRelay {

    virtual nlohmann::json call(size_t id, const nlohmann::json&) override{
      throw std::runtime_error("AWASDASD");
    }
  };

  Iyathuum::FunctionRelay& PythonEngine::getRelay() {
    return *new FRMOCK();
  }
}