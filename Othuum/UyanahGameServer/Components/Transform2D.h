#pragma once

#include "Component.h"
#include "IyathuumCoreLib/lib/glm/glm.hpp"

namespace Uyanah {
  namespace Components {
    class Transform2D : public Component {
      REGISTERCOMPONENT(Transform2D, "Transform2D");
    public:
      virtual const std::string      ComponentName() const override { return "Transform2D"; }

      glm::vec2 position = glm::vec2(0,0);
      float     rotation = 0;

      virtual Vishala::BinaryPackage toBinary()                                  override;
      virtual void                   fromBinary(Vishala::BinaryPackage& Package) override;
      virtual nlohmann::json         toJson()                                    override;
      virtual void                   fromJson(nlohmann::json)                    override;
    };
  }
}