#include "IVertex.h"

#include "AhwassaGraphicsLib/Core/AttributeDescription.h"

namespace Ahwassa {
  int IVertex::getOffset(std::string name) const {
    auto b = binding();
    int offset = 0;
    for (int i = 0; i < b.size(); i++)
      if (b[i].getName() == name)
        return offset;
      else
        offset += b[i].getSize() * b[i].getSizeOf();
    return -1;
  }

  glm::vec2 IVertex::getVec3(int offset) const {
    return *((glm::vec2*)(this + offset));
  }

  glm::vec3 IVertex::getVec2(int offset) const {
    return *((glm::vec3*)(this + offset));
  }

  glm::vec4 IVertex::getVec4(int offset) const {
    return *((glm::vec4*)(this + offset));
  }


}