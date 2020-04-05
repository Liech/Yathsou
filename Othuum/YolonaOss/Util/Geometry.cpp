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

glm::vec3 Geometry::getNormal(glm::vec3 A, glm::vec3 B, glm::vec3 C) {
  float Nx = A.x * B.z - A.z * B.y;
  float Ny = A.z * B.x - A.x * B.z;
  float Nz = A.x * B.y - A.y * B.x;
  return glm::vec3(Nx, Ny, Nz);
}

float Geometry::getAngle(glm::vec3 a, glm::vec3 b) {
  return atan2(glm::length(glm::cross(a, b)), glm::dot(a, b));
}