#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

namespace Aezesel {
  class STLWriter {
  public:
    static void write(const std::string& filename, const std::vector<glm::vec3>&);
  };
}