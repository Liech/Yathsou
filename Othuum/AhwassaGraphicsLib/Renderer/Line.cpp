#include "Line.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"

namespace Ahwassa {
  Line::Line(const glm::vec3& start, const glm::vec3& end, const float& size, const Iyathuum::Color& clr) {
    _start = start;
    _end   = end  ;
    _size  = size ;
    _clr   = clr  ;
    recalculate();
  }

  void Line::setStart(const glm::vec3& pos) {
    _start = pos;
    recalculate();
  }

  glm::vec3 Line::getStart() const {
    return _start;
  }

  void Line::setEnd(const glm::vec3& pos) {
    _end = pos;
    recalculate();
  }

  glm::vec3 Line::getEnd() const {
    return _end;
  }

  void Line::setThickness(const float& size) {
    _size = size;
    recalculate();
  }

  float Line::getThickness() const {
    return _size;
  }

  void Line::setColor(const Iyathuum::Color& clr) {
    _clr = clr;
  }

  Iyathuum::Color Line::getColor() const {
    return _clr;
  }

  glm::mat4 Line::matrix() const {
    return _matrix;
  }

  void Line::recalculate() {
    const float l = glm::length(_end - _start);
    const float s = _size;

    glm::vec3 dir = glm::normalize(_end - _start);
    float a = std::atan2(dir[0], dir[2]);
    float b = -std::asin(dir[1]);

    const float x = _start[0];
    const float y = _start[1];
    const float z = _start[2];
    float transAndScale[16] = {
      s , 0 , 0, 0,
      0 , s , 0, 0,
      0 , 0 , l, 0,
      x , y , z, 1
    };

    float xRot[16] = {
      1 ,            0 ,            0 , 0,
      0 ,  std::cos(a) ,  std::sin(a) , 0,
      0 , -std::sin(a) ,  std::cos(a) , 0,
      0 ,            0 ,            0 , 1
    };

    float yRot[16] = {
      std::cos(b),           0 , -std::sin(b) , 0,
      0          ,           1 ,            0 , 0,
      std::sin(b),           0 ,  std::cos(b) , 0,
      0          ,           0 ,            0 , 1
    };


    _matrix = glm::make_mat4(transAndScale);
    _matrix = glm::rotate(_matrix, a, glm::vec3(0, 1, 0));
    _matrix = glm::rotate(_matrix, b, glm::vec3(1, 0, 0));
  }
}