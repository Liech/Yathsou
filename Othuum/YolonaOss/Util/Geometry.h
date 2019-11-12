#pragma once

#include "glm/vec3.hpp"


struct Intersection {
  Intersection(glm::vec3 loc, float dist, bool does);

  glm::vec3 location;
  float     distance;
  bool      doesIntersect;
};

class Geometry {
public:
  static Intersection intersectRayPlane(const glm::vec3 rayOrigin,const glm::vec3 rayDirection,const glm::vec3 planeOrigin,const glm::vec3 planeNormal);
};