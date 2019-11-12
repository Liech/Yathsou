#include "Geometry.h"

#include <glm/gtx/intersect.hpp>

Intersection::Intersection(glm::vec3 loc, float dist, bool does) {
  location = loc;
  distance = dist;
  doesIntersect = does;
}

Intersection Geometry::intersectRayPlane(const glm::vec3 rayOrigin, const glm::vec3 rayDirection, const glm::vec3 planeOrigin, const glm::vec3 planeNormal){
  float distance = 0;
  bool doesIntersect = glm::intersectRayPlane(rayOrigin, rayDirection, planeOrigin, planeNormal, distance);

  return Intersection(rayOrigin + rayDirection * distance, distance, doesIntersect);
}