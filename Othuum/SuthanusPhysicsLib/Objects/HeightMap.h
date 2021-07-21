#pragma once

#include "PhysicObject.h"

namespace Suthanus
{
  class HeightMap : public PhysicObject
  {
  public:
    struct Mesh
    {
      std::vector<int> indices;
      std::vector<glm::vec3> vertecies;
      std::vector<glm::vec3> normals;
    };
    virtual HeightMap::Mesh getMesh() = 0;
  };
}