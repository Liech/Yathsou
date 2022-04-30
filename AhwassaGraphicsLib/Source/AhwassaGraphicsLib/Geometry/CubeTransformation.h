#pragma once

#include <glm/glm.hpp>

namespace Ahwassa {
  class CubeTransformation {
    public:
      static glm::mat4 dot(const glm::vec3& position, float scale);
      static glm::mat4 dot(const glm::vec3& position, const glm::vec3& scale);
      static glm::mat4 line(const glm::vec3& start, const glm::vec3& end, float thickness);
      static glm::mat4 box(const glm::vec3& start, const glm::vec3& size);
  };
}