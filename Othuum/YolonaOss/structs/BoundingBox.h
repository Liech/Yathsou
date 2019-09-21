#pragma once

#include "glm/glm.hpp"

template <typename Content, size_t Dimension>
struct BoundingBox {
  BoundingBox() {
    for (int i = 0; i < Dimension; i++) position[i] = 0;
    for (int i = 0; i < Dimension; i++) size[i] = 0;
  }
  BoundingBox(glm::vec<Dimension, Content, glm::defaultp> pos, glm::vec<Dimension, Content, glm::defaultp> siz) {
    position = pos;
    size = siz;
  }


  glm::vec<Dimension, Content, glm::defaultp> position;
  glm::vec<Dimension, Content, glm::defaultp> size;

  bool inside(glm::vec<Dimension, Content, glm::defaultp> point) {
    glm::vec<Dimension, Content, glm::defaultp> end = position + size;
    for (int i = 0; i < Dimension;i++) {
      if (point[i] < position[i] || point[i] > end[i])
        return false;
    }
    return true;
  }
};

typedef BoundingBox<float,2> BoundingBox2;