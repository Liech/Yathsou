#pragma once

#include <memory>
#include <vector>
#include <nlohmann/json.hpp>

namespace Iyathuum {
  class API;
  class APIFunction;
  class FunctionRelay;
}
namespace pybind11 {
  class scoped_interpreter;
  class dict;
}

namespace Haas {
  class PythonEngine {
  public:
    static PythonEngine& instance();
    virtual ~PythonEngine();

    void addAPI(std::unique_ptr<Iyathuum::API>);
    void initialize();
    
    size_t numberOfApis() const;
    Iyathuum::API& getAPI(size_t number);
    Iyathuum::FunctionRelay& getRelay();
     
    static nlohmann::json py2j(const pybind11::dict&);
    static pybind11::dict j2py(const nlohmann::json&);
  private:
    PythonEngine();

    std::unique_ptr<pybind11::scoped_interpreter> _interpreterScope = nullptr;
    bool                                          _initialized = false;
    std::vector<std::unique_ptr<Iyathuum::API>>   _apis;
    std::unique_ptr<Iyathuum::FunctionRelay>      _relay = nullptr;
  };
}