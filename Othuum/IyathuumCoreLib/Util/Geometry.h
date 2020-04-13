#pragma once

#include <array>

#define _USE_MATH_DEFINES
#include <math.h>

namespace Iyathuum {
  template<size_t Dimension>
  class Geometry {
  public:
    using vec = std::array<double, Dimension>;

    template<typename A, typename B>
    static std::array<A, Dimension> convert(std::array<B, Dimension> val) {
      std::array<A, Dimension> result;
      for (size_t i = 0; i < Dimension; i++)
        result[i] = val[i];
      return result;
    }

    static vec value(double v) {
      vec result;
      for (size_t i = 0; i < Dimension; i++)
        result[i] = v;
      return result;
    }

    static double length(vec A) {
      double result = 0;
      for (size_t i = 0; i < Dimension; i++)
        result += A[i] * A[i];
      result = std::sqrt(result);
      return result;
    }

    static vec normalize(vec A) {
      double len = length(A);
      vec result;
      for (size_t i = 0; i < Dimension; i++)
        result[i] = A[i] / len;
      return result;
    }

    static vec subtract(vec A, vec B) {
      vec result = A;
      for (size_t i = 0; i < Dimension; i++)
        result[i] -= B[i];
      return result;
    }

    static vec add(vec A, vec B) {
      vec result = A;
      for (size_t i = 0; i < Dimension; i++)
        result[i] += B[i];
      return result;
    }

    static vec multiply(vec A, double B) {
      vec result = A;
      for (size_t i = 0; i < Dimension; i++)
        result[i] *= B;
      return result;
    }

    static double dot(vec A, vec B) {
      double result = 0;
      for (size_t i = 0; i < Dimension; i++)
        result += A[i] * B[i];
      return result;
    }

    static double distancePoint2LineSegment(vec p, vec a, vec b) {
      //https://www.randygaul.net/2014/07/23/distance-point-to-line-segment/
      vec n = subtract(b, a);
      vec pa = subtract(a, p);
      double c = dot(n, pa);
      // Closest point is a
      if (c > 0.0f)
        return dot(pa, pa);
      vec bp = subtract(p, b);

      // Closest point is b
      if (dot(n, bp) > 0.0f)
        return dot(bp, bp);

      // Closest point is between a and b
      vec m = multiply(n, (c / dot(n, n)));
      vec e = subtract(pa, m);

      return dot(e, e);
    }

    static vec slerp(vec p0, vec p1, double t) {
      //https://en.wikipedia.org/wiki/Slerp
      float omega = std::acos(std::clamp(dot(p0, p1), -1.0f, 1.0f));
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
      return normalize(result);
    }

    static float getAngle(vec A, vec B) {
      //https://stackoverflow.com/questions/2827393/angles-between-two-n-dimensional-vectors-in-python/13849249#13849249
      A = normalize(A);
      B = normalize(B);
      return std::acos(std::clamp(dot(A, B), -1.0f, 1.0f));
    }

    //is not used and i have no reason to write a determinant function yet
    ////ok, more or less heavy shit in n-Dimensions :s
    ////https://math.stackexchange.com/questions/2371022/cross-product-in-higher-dimensions
    ////gets an orthogonal vector to the set of vectors. You should enter Dimension-1 Vectors
    ////2D: 1 vector -> (-y,x)
    ////3D: 2 vectors-> 
    ////                (c_P[0] = v_A[1] * v_B[2] - v_A[2] * v_B[1],
    ////                c_P[1] = -(v_A[0] * v_B[2] - v_A[2] * v_B[0]),
    ////                c_P[2] = v_A[0] * v_B[1] - v_A[1] * v_B[0])
    ////(https://www.tutorialspoint.com/cplusplus-program-to-compute-cross-product-of-two-vectors)
    ////4D...: 
    ////   determinant juggling
    //static vec cross(std::array<vec, Dimension - 1> input) {
    //  //matrix[row][column]
    //  vec result;
    //  for (size_t currentDimension = 0; currentDimension < Dimension; currentDimension++) {
    //    glm::mat<Dimension - 1, Dimension - 1, float> matrix;
    //    for (size_t row = 0; row < Dimension - 1; row++) {
    //      for (size_t column = 0; column < Dimension - 1)
    //        matrix[row][column] = input[column][column + currentDimension <= column ? 1 : 0];
    //    }
    //    result[currentDimension] = glm::determinant(matrix); 
    //  }
    //  return result;
    //}

  };
}