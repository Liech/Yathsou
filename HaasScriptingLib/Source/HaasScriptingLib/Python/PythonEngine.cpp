#include "PythonEngine.h"

#include "FunctionRelay.h"
#include "Conversion.h"

#include <IyathuumCoreLib/API/API.h>
#include <IyathuumCoreLib/API/APIFunction.h>
#include <IyathuumCoreLib/API/FunctionRelay.h>

#include <python3.10/Python.h>
#include <pybind11/embed.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>

#include <iostream>
#include <fstream>
#include <filesystem>


namespace Haas {
  namespace Python {
    class PythonEngine::pimpl {
      public:
      pybind11::module_ mainModule;
      std::unique_ptr<Python::FunctionRelay> relay = nullptr;
      std::vector<std::unique_ptr<Iyathuum::API>>   _apis;
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
      _pimpl->relay = std::make_unique<Python::FunctionRelay>();

    }

    PYBIND11_EMBEDDED_MODULE(HaasModule, m) {
      PythonEngine& engine = PythonEngine::instance();

      for (size_t apiID = 0; apiID < engine.numberOfApis(); apiID++) {
        auto& api = engine.getAPI(apiID);
        for (size_t f = 0; f < api.numberOfFunctions(); f++) {
          auto& func = api.getFunction(f);
          m.def(func.getName().c_str(), [&func](const pybind11::object& input) {
            auto& r = (Python::FunctionRelay&)PythonEngine::instance().getRelay();
            return Conversion::j2py(func.call(Conversion::py2j(input, r)));
            }, pybind11::arg("input") = pybind11::none());
        }
      }
    }

    void PythonEngine::initialize() {
      assert(!_initialized);
      _initialized = true;
      if (!_pimpl) {
        _pimpl = std::make_unique<PythonEngine::pimpl>();
        _pimpl->relay = std::make_unique<Python::FunctionRelay>();
      }

      try {
        Py_SetPythonHome(L"Data/python");
        pybind11::initialize_interpreter();
        _pimpl->mainModule = pybind11::module_::import("HaasModule");
      } catch (pybind11::error_already_set& e) {
        std::cout << e.what() << std::endl;
        throw;
      }
    }

    void PythonEngine::execute(const std::string& pythonCode) {
      try {
        auto locals = pybind11::dict(**_pimpl->mainModule.attr("__dict__"));
        pybind11::exec(pythonCode, pybind11::globals(), locals);
      } catch (pybind11::error_already_set& e) {
        std::cout << e.what() << std::endl;
        throw;
      }
    }

    void PythonEngine::executeFile(const std::string& filename) {
      if (!std::filesystem::exists(filename))
        throw std::runtime_error("File not found!");

      std::ifstream t(filename);
      std::string str((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());
      execute(str);
    }

    void PythonEngine::dispose() {
      assert(_initialized);
      _pimpl = nullptr;
      pybind11::finalize_interpreter();
      _initialized = false;
    }

    void PythonEngine::addAPI(std::unique_ptr<Iyathuum::API> api) {
      assert(!_initialized);
      _pimpl->_apis.push_back(std::move(api));
    }

    size_t PythonEngine::numberOfApis() const {
      return _pimpl->_apis.size();
    }

    Iyathuum::API& PythonEngine::getAPI(size_t number) {
      return *_pimpl->_apis[number];
    }

    Iyathuum::FunctionRelay& PythonEngine::getRelay() {
      return *_pimpl->relay;
    }
  }
}