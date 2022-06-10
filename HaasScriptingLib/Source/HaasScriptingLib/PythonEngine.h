#pragma once

#include <memory>

namespace pybind11 {
  class scoped_interpreter;
}

namespace Haas {
  class PythonEngine {
  public:
    static PythonEngine& instance();
    virtual ~PythonEngine();
    
     
  private:
    PythonEngine();
    std::unique_ptr<pybind11::scoped_interpreter> _interpreterScope = nullptr;

  };
}