#pragma once

#include <glad/glad.h>
#include <vector>
#include "AttributeDescription.h"
#include <glm/glm.hpp>

struct PositionTextureVertex {
  glm::vec3 position;
  glm::vec2 texture;
  PositionTextureVertex() {
    position = glm::vec3(0, 0, 0);
    texture = glm::vec2(0, 0);
  };
  PositionTextureVertex(glm::vec3 Position, glm::vec2 Texture) {
    position = Position;
    texture = Texture;
  }

  std::vector<AttributeDescription> getBinding() {
    std::vector<AttributeDescription> result;
    result.push_back(AttributeDescription("position", 3, AttributeDescription::DataType::Float));
    result.push_back(AttributeDescription("texCoord", 2, AttributeDescription::DataType::Float));
    return result;
  }
};