#pragma once

#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "AezeselFileIOLib/lib/json.hpp"
#include <memory>

namespace Athanah {
  class BlueprintPhysic {
  public:
    BlueprintPhysic(const nlohmann::json& input);
    virtual ~BlueprintPhysic() = default;
  private:

  };
}