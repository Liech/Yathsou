#include "PythonEngine.h"
#include <python3.10/Python.h>
#include <iostream>
#include <pybind11/embed.h>

namespace Haas {

  void greetTheWorld() {
    std::cout << "Hallo Welt" << std::endl;
  }

  PythonEngine::PythonEngine() {
    //Py_SetProgramName(L"Haas");
    Py_SetPythonHome(L"Data/python");
    //Py_Initialize();

    pybind11::scoped_interpreter guard{};

    pybind11::print("Hello, World!");

    pybind11::exec(R"(
        kwargs = dict(name="World", number=42)
        message = "Hello, {name}! The answer is {number}".format(**kwargs)
        print(message)
    )");


  }
}