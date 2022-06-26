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
  namespace Python {
    class PythonEngine {
      public:
      static PythonEngine& instance();
      virtual ~PythonEngine();

      void addAPI(std::unique_ptr<Iyathuum::API>);
      void initialize();
      void dispose();

      void execute(const std::string& pythonCode);
      void executeFile(const std::string& filename);

      size_t numberOfApis() const;
      Iyathuum::API& getAPI(size_t number);
      Iyathuum::FunctionRelay& getRelay();

      private:
      PythonEngine();

      bool                                          _initialized = false;

      class pimpl;
      std::unique_ptr<pimpl> _pimpl;
    };
  }
}