#pragma once

#include <glad/glad.h>
#include <vector>
#include "AttributeDescription.h"
namespace YolonaOss {
  namespace GL {
    struct PositionColorVertex {
      float x;
      float y;
      float z;
      float r;
      float g;
      float b;
      float a;
      PositionColorVertex() {};
      PositionColorVertex(float X, float Y, float Z, float R, float G, float B, float A) {
        x = X;
        y = Y;
        z = Z;
        r = R;
        g = G;
        b = B;
        a = A;
      }
      PositionColorVertex(glm::vec3 pos, glm::vec4 color) {
        x = pos[0];
        y = pos[1];
        z = pos[2];
        r = color[0];
        g = color[1];
        b = color[2];
        a = color[3];
      }
      std::vector<AttributeDescription> getBinding() {
        std::vector<AttributeDescription> result;
        result.push_back(AttributeDescription("position", 3, AttributeDescription::DataType::Float));
        result.push_back(AttributeDescription("color", 4, AttributeDescription::DataType::Float));
        return result;
      }
    };
  }
}