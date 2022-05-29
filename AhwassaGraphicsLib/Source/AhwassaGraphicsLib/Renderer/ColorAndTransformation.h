#pragma once

#include <glm/glm.hpp>
#include <IyathuumCoreLib/BaseTypes/Color.h>

namespace Ahwassa {
  struct ColorAndTransformation {
    Iyathuum::Color color;
    glm::mat4       transformation;
  };
}