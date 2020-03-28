#pragma once

#include "glm/vec3.hpp"
#include <array>
#include <glm/glm.hpp>

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

template<size_t Dimension>
class GeometryND {
public:
  typedef std::array<double, Dimension> vec;

  static vec Subtract(vec A, vec B) {
    vec result = A;
    for (size_t i = 0; i < Dimension; i++)
      result[i] -= B[i];
    return result;
  }
  
  static vec Add(vec A, vec B) {
    vec result = A;
    for (size_t i = 0; i < Dimension; i++)
      result[i] += B[i];
    return result;
  }

  static vec Multiply (vec A, double B) {
    vec result = A;
    for (size_t i = 0; i < Dimension; i++)
      result[i] *= B;
    return result;
  }

  static double Dot (vec A, vec B) {
    double result = 0;
    for (size_t i = 0; i < Dimension; i++)
      result += A[i] * B[i];
    return result;
  }

  static double distancePoint2LineSegment(vec p, vec a, vec b) {
    //https://www.randygaul.net/2014/07/23/distance-point-to-line-segment/
    vec n = Subtract(b, a);
    vec pa = Subtract(a, p);
    double c = Dot(n, pa);
    // Closest point is a
    if (c > 0.0f)
      return Dot(pa, pa);
    vec bp = Subtract(p, b);

    // Closest point is b
    if (Dot(n, bp) > 0.0f)
      return Dot(bp, bp);

    // Closest point is between a and b
    vec m = Multiply(n, (c / Dot(n, n)));
    vec e = Subtract(pa, m);

    return Dot(e, e);
  }
};