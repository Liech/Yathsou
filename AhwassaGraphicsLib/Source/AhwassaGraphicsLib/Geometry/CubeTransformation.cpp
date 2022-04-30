#include "CubeTransformation.h"

#include <glm/gtc/matrix_transform.hpp>


namespace Ahwassa {
  glm::mat4 CubeTransformation::dot(const glm::vec3& position, float scale) {
    return dot(position, glm::vec3(scale, scale, scale));
  }

  glm::mat4 CubeTransformation::dot(const glm::vec3& position, const glm::vec3& size) {
    glm::mat4 m = glm::mat4(1);
    m = glm::translate(m, position);
    m = glm::scale(m, size);
    m = glm::translate(m, glm::vec3(-0.5f, -0.5f, -0.5f));
    return m;
  }

  glm::mat4 CubeTransformation::line(const glm::vec3& start, const glm::vec3& end, float thickness) {
    glm::mat4 m = glm::mat4(1);
    m = glm::translate(m, start);

    glm::vec3 dir = glm::normalize(end - start);
    float angle = std::atan2(dir[0], dir[2]);
    m = glm::rotate(m, angle, glm::vec3(0, 1.0, 0));
    float angleZ = -std::asin(dir[1]);
    m = glm::rotate(m, angleZ, glm::vec3(1.0, 0.0, 0.0));

    m = glm::scale(m, glm::vec3(thickness, thickness, glm::length(end - start)));
    m = glm::translate(m, glm::vec3(-0.5, -0.5, 0));
    return m;
  }

  glm::mat4 CubeTransformation::box(const glm::vec3& start, const glm::vec3& size) {
    glm::mat4 m = glm::mat4(1);
    m = glm::translate(m, start);
    m = glm::scale(m, size);
    return m;
  }
}