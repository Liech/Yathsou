#include "PythonEngine.h"

#include "PyFunctionRelay.h"
#include "PyConversion.h"

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
      std::unique_ptr<PyFunctionRelay> relay = nullptr;
  };

  PythonEngine& PythonEngine::instance() {
    static PythonEngine engine;
    return engine;
  }

  PythonEngine::~PythonEngine() {
    if (_initialized)
      throw std::runtime_error("Please dispose() the PythonEngine correctly");
  }

  PythonEngine::PythonEngine() {
    _pimpl = std::make_unique<PythonEngine::pimpl>();
    _pimpl->relay = std::make_unique<PyFunctionRelay>();

  }
  
  PYBIND11_EMBEDDED_MODULE(HaasModule, m) {
    PythonEngine& engine = PythonEngine::instance();

    for (size_t apiID = 0; apiID < engine.numberOfApis(); apiID++) {
      auto& api = engine.getAPI(apiID);
      for (size_t f = 0; f < api.numberOfFunctions(); f++) {
        auto& func = api.getFunction(f);
        m.def(func.getName().c_str(), [&func](const pybind11::object& input) {
          auto& r = (PyFunctionRelay&)PythonEngine::instance().getRelay();
          return PyConversion::j2py(func.call(PyConversion::py2j(input, r)));
          }, pybind11::arg("input") = pybind11::none());
      }
    }
  } 

  void PythonEngine::initialize() {
    assert(!_initialized);
    _initialized = true;
    if (!_pimpl) {
      _pimpl = std::make_unique<PythonEngine::pimpl>();
      _pimpl->relay = std::make_unique<PyFunctionRelay>();
    }

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

  Iyathuum::FunctionRelay& PythonEngine::getRelay() {
    return *_pimpl->relay;
  }
}