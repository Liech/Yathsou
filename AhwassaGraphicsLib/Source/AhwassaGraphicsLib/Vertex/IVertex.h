#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace Ahwassa {
  struct AttributeDescription;

  //IVertex offers unified access to variables by name
  //useful when a simpler (e.g. debugging) shader is used to display a more verbose mesh

  class IVertex {
  public:    
    int getOffset(std::string name) const;
    glm::vec3 getVec2(int offset)   const;
    glm::vec2 getVec3(int offset)   const;
    glm::vec4 getVec4(int offset)   const;

    virtual std::vector<AttributeDescription> binding() const = 0;
  private:
  };
}