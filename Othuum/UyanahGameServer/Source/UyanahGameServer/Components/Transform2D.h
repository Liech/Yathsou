#pragma once

#include "UyanahGameServer/Component.h"
#include <glm/glm.hpp>

namespace Uyanah {
  namespace Components {
    class Transform2D : public Component {
      SERIALIZATION(Transform2D, "Transform2D")
    public:
      virtual const std::string Name() const override { return "Transform2D"; }
      void update() { position += velocity; }
      glm::vec2 position = glm::vec2(0, 0);
      glm::vec2 velocity = glm::vec2(0, 0);
      float     rotation = 0;

      virtual Vishala::BinaryPackage toBinary()             const                     override;
      virtual void                   fromBinary(Vishala::BinaryPackage& Package) override;
      virtual nlohmann::json         toJson()              const                      override;
      virtual void                   fromJson(nlohmann::json)                    override;
    };
  }
}