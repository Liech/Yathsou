#pragma once

#include "Component.h"
#include "IyathuumCoreLib/lib/glm/glm.hpp"

namespace Uyanah {
  namespace Components {
    class Transform2D : public Component {
      REGISTERCOMPONENT(Transform2D, "Transform2D");
      virtual const std::string      ComponentName() const override { return "Transform2D"; }

      glm::vec2 position;
      float     rotation;

      virtual Vishala::BinaryPackage toBinary()                                  override;
      virtual void                   fromBinary(Vishala::BinaryPackage& Package) override;
      virtual nlohmann::json         toJson()                                    override;
      virtual void                   fromJson(nlohmann::json)                    override;
    };
  }
}