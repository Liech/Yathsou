#include "PythonEngine.h"
#include <python3.10/Python.h>
#include <iostream>
#include <pybind11/embed.h>

namespace Haas {
  PythonEngine& PythonEngine::instance() {
    static PythonEngine engine;
    return engine;
  }

  void greetTheWorld() {
    std::cout << "Hallo Welt" << std::endl;
  }
  
  PYBIND11_EMBEDDED_MODULE(HaasModule, m) {
    m.def("add", [](int i, int j) {
      std::cout << "Waahhh" << std::endl;
      return i + j;
      });
  } 

  PythonEngine::PythonEngine() {
    Py_SetPythonHome(L"Data/python");
    _interpreterScope = std::make_unique< pybind11::scoped_interpreter>();

    auto module = pybind11::module_::import("HaasModule");
    //auto locals = pybind11::dict(**module.attr("__dict__"));
    //
    //pybind11::exec(R"(
    //    print('EXEC :D')
    //    add(1,1);
    //)", pybind11::globals(), locals);
  }

  PythonEngine::~PythonEngine() {

  }
}