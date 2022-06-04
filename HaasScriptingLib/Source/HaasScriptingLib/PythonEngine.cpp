#include "PythonEngine.h"
#include <python3.10/Python.h>

namespace Haas {
  PythonEngine::PythonEngine() {
    Py_SetProgramName(L"Haas");
    Py_SetPythonHome(L"Data/python");
    Py_Initialize();
    PyObject* sys = PyImport_ImportModule("sys");
    PyRun_SimpleString("from time import time,ctime\n"
      "print('Today is', ctime(time()))\n");
  }
}