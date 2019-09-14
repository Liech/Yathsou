#pragma once

#include <glad/glad.h>
#include <vector>
#include "AttributeDescription.h"

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

  std::vector<AttributeDescription> getBinding() {
    std::vector<AttributeDescription> result;
    result.push_back(AttributeDescription("position", 3, AttributeDescription::DataType::Float));
    result.push_back(AttributeDescription("color", 4, AttributeDescription::DataType::Float));
    return result;
  }
};