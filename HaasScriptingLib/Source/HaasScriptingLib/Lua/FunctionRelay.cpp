#include "FunctionRelay.h"

namespace Haas {
  namespace Lua {
    FunctionRelay::FunctionRelay() {
    }

    nlohmann::json FunctionRelay::call(size_t id, const nlohmann::json&) {
      return nlohmann::json();
    }
  }
}