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
  PythonEngine& PythonEngine::instance() {
    static PythonEngine engine;
    return engine;
  }

  PythonEngine::~PythonEngine() {
  }


  PythonEngine::PythonEngine() {
  }
  
  PYBIND11_EMBEDDED_MODULE(HaasModule, m) {
    PythonEngine& engine = PythonEngine::instance();

    for (size_t apiID = 0; apiID < engine.numberOfApis(); apiID++) {
      auto& api = engine.getAPI(apiID);
      for (size_t f = 0; f < api.numberOfFunctions(); f++) {
        auto& func = api.getFunction(f);
        m.def(func.getName().c_str(), [&func](pybind11::dict input) {
          return PythonEngine::j2py(func.call(PythonEngine::py2j(input))); 
          }, pybind11::arg("input") = pybind11::dict());
      }
    }
  } 

  void PythonEngine::initialize() {
    assert(!_initialized);
    _initialized = true;

    Py_SetPythonHome(L"Data/python");
    _interpreterScope = std::make_unique< pybind11::scoped_interpreter>();
    auto module = pybind11::module_::import("HaasModule");

    auto locals = pybind11::dict(**module.attr("__dict__"));
    try {
      pybind11::exec(R"(
      print(str(Hallo({'X' : 31, 'ASD':321})));
    )", pybind11::globals(), locals);
    }
    catch (pybind11::error_already_set& e) {
      std::cout << e.what() << std::endl;
      throw;
    }
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

  nlohmann::json PythonEngine::py2j(const pybind11::dict& input) {
    nlohmann::json result;

    for (auto& x : input) {
      result[x.first.str()] = x.second.cast<int>();
    }

    return result;
  }

  pybind11::dict PythonEngine::j2py(const nlohmann::json& input) {
    using namespace pybind11::literals;

    pybind11::dict result;

    for (auto& x : input.items()) {
      int v = x.value();
      result[x.key().c_str()] =  v;
    }

    return result;
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