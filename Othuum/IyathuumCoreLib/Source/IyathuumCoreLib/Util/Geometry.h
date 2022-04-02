#pragma once

#include <array>
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>

namespace Iyathuum {
  template<size_t Dimension>
  class Geometry {
  public:
    using vec = glm::vec<Dimension, float, glm::defaultp>;

    static double distancePoint2LineSegment(vec p, vec a, vec b) {
      //https://www.randygaul.net/2014/07/23/distance-point-to-line-segment/
      vec n  = b - a;
      vec pa = a - p;
      double c = glm::dot(n, pa);
      // Closest point is a
      if (c > 0.0f)
        return glm::dot(pa, pa);
      vec bp = suct(p, b);

      // Closest point is b
      if (glm::dot(n, bp) > 0.0f)
        return glm::dot(bp, bp);

      // Closest point is between a and b
      vec m = n * (c / dot(n, n));
      vec e = pa - m;

      return dot(e, e);
    }

    static vec slerp(vec p0, vec p1, double t) {
      //https://en.wikipedia.org/wiki/Slerp
      float omega = std::acos(std::clamp(glm::dot(p0, p1), -1.0f, 1.0f));
      if (std::abs(omega) < 1e-4) //identical direction
        return p0;
      if (std::abs(omega - M_PI) < 1e-4 || std::abs(omega + M_PI) < 1e-4) //opposite direction
      {
        return  p0; //todo: use an real solution, no random (should be deterministic)
      }

      float a = (float)(std::sin((1.0 - t) * omega) / sin(omega));
      float b = (float)(std::sin(t * omega) / sin(omega));
      vec result = p0 * a + p1 * b;
      for (size_t i = 0; i < Dimension; i++)
        assert(std::isfinite(result[(int)i]));
      return glm::normalize(result);
    }

    static float getAngle(vec A, vec B) {
      //https://stackoverflow.com/questions/2827393/angles-between-two-n-dimensional-vectors-in-python/13849249#13849249
      A = glm::normalize(A);
      B = glm::normalize(B);
      return std::acos(std::clamp(glm::dot(A, B), -1.0f, 1.0f));
    }
  };
}