#pragma once

#include <IyathuumCoreLib/API/FunctionRelay.h>

namespace pybind11 {
  class object;
}

namespace Haas {
  namespace Python {
    class FunctionRelay : public Iyathuum::FunctionRelay {
      public:
      FunctionRelay();
      virtual ~FunctionRelay() = default;

      virtual nlohmann::json call(size_t id, const nlohmann::json&) override;

      size_t addFunction(pybind11::object);

      private:
      size_t counter = 1;

      class pimpl;
      std::unique_ptr<pimpl> _pimpl;
    };
  }
}