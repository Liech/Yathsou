#pragma once

#include "glm/vec3.hpp"
#include <array>
#include <glm/glm.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

struct Intersection {
  Intersection(glm::vec3 loc, float dist, bool does);

  glm::vec3 location;
  float     distance;
  bool      doesIntersect;
};

class Geometry {
public:
  static Intersection intersectRayPlane(const glm::vec3 rayOrigin,const glm::vec3 rayDirection,const glm::vec3 planeOrigin,const glm::vec3 planeNormal);
  static glm::vec3 getNormal(glm::vec3 a, glm::vec3 b, glm::vec3 c);
  static float getAngle(glm::vec3 a, glm::vec3 b);
};

template<size_t Dimension>
class GeometryND {
public:
  using vec = typedef glm::vec<Dimension, float, glm::defaultp>;


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

  static vec slerp(vec p0, vec p1, double t) {
    //https://en.wikipedia.org/wiki/Slerp
    float omega = std::acos(std::clamp(glm::dot(p0, p1),-1.0f,1.0f));
    if (std::abs(omega) < 1e-4)
      return p0;
    if (std::abs(omega+M_PI) < 1e-4)
      assert(false);
    if (std::abs(omega-M_PI) < 1e-4)
      assert(false);
    float a = std::sin((1.0 - t) * omega) / sin(omega);
    float b = std::sin(t * omega)         / sin(omega);
    vec result = p0 * a + p1 * b;
    for (size_t i = 0; i < Dimension; i++)
      assert(std::isfinite(result[i]));
    return glm::normalize(result);
  }

  static float getAngle(vec A, vec B) {
    //https://stackoverflow.com/questions/2827393/angles-between-two-n-dimensional-vectors-in-python/13849249#13849249
    A = glm::normalize(A);
    B = glm::normalize(B);
    return std::acos(std::clamp(Dot(A, B), -1.0f, 1.0f));
  }

  //ok, more or less heavy shit in n-Dimensions :s
  //https://math.stackexchange.com/questions/2371022/cross-product-in-higher-dimensions
  //gets an orthogonal vector to the set of vectors. You should enter Dimension-1 Vectors
  //2D: 1 vector -> (-y,x)
  //3D: 2 vectors-> 
  //                (c_P[0] = v_A[1] * v_B[2] - v_A[2] * v_B[1],
  //                c_P[1] = -(v_A[0] * v_B[2] - v_A[2] * v_B[0]),
  //                c_P[2] = v_A[0] * v_B[1] - v_A[1] * v_B[0])
  //(https://www.tutorialspoint.com/cplusplus-program-to-compute-cross-product-of-two-vectors)
  //4D...: 
  //   determinant juggling
  static vec Cross(std::array<vec,Dimension-1> input) {
    //matrix[row][column]
    vec result;
    for (size_t currentDimension = 0; currentDimension < Dimension; currentDimension++) {
      glm::mat<Dimension - 1, Dimension - 1, float> matrix;
      for (size_t row = 0; row < Dimension - 1; row++) {
        for (size_t column = 0; column < Dimension - 1)
          matrix[row][column] = input[column][column + currentDimension<=column?1:0];
      }
      result[currentDimension] = glm::determinant(matrix);
    }
    return result;
  }

};