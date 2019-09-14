#pragma once

#include "structs/MultiDimensionalArray.h"
#include "structs/Color.h"
#include "glad/glad.h"
#include "Uniform.h"

class Texture : public Uniform{
public:
  Texture(std::string name, MultiDimensionalArray<Color,2>* tex);
  ~Texture();

  void bind() override;
  virtual std::string getType() override { return "sampler2D"; }

private:
  GLuint _texture;

  // Inherited via Uniform
};