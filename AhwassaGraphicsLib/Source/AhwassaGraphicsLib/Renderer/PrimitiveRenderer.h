#pragma once

#include <memory>

#include <glm/glm.hpp>

#include <IyathuumCoreLib/BaseTypes/Color.h>

namespace Ahwassa {
  class Dot;

  class PrimitiveRenderer {
    public:
      PrimitiveRenderer();
      virtual ~PrimitiveRenderer() = 0;

      void                 drawDot(const glm::vec3& position, float size, const Iyathuum::Color&);
      std::shared_ptr<Dot> addDot (const glm::vec3& position, float size, const Iyathuum::Color&);

    private:

  };
}