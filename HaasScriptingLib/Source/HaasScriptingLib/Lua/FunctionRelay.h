#pragma once

#include <IyathuumCoreLib/API/FunctionRelay.h>

namespace Haas {
  namespace Lua {
    class FunctionRelay : public Iyathuum::FunctionRelay {
      public:
      FunctionRelay();
      virtual ~FunctionRelay() = default;

      virtual nlohmann::json call(size_t id, const nlohmann::json&) override;

      //size_t addFunction(pybind11::object);

      private:
      size_t counter = 1;
    };
  }
}