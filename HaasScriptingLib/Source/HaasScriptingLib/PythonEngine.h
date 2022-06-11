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
  class object;
}

namespace Haas {
  class PythonEngine {
  public:
    static PythonEngine& instance();
    virtual ~PythonEngine();

    void addAPI(std::unique_ptr<Iyathuum::API>);
    void initialize();
    void dispose();
    
    void execute(const std::string& pythonCode);

    size_t numberOfApis() const;
    Iyathuum::API& getAPI(size_t number);
    Iyathuum::FunctionRelay& getRelay();
     
    static nlohmann::json   py2j(const pybind11::object&);
    static pybind11::object j2py(const nlohmann::json&);
  private:
    PythonEngine();

    bool                                          _initialized = false;
    std::vector<std::unique_ptr<Iyathuum::API>>   _apis;
    std::unique_ptr<Iyathuum::FunctionRelay>      _relay = nullptr;

    class pimpl;
    std::unique_ptr<pimpl> _pimpl;
  };
}