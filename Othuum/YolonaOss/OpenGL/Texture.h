#pragma once

#include "../structs/MultiDimensionalArray.h"
#include "../structs/Color.h"
#include "glad/glad.h"
#include "Uniform.h"
namespace YolonaOss {
  namespace GL {
    class Texture : public Uniform {
    public:
      Texture(std::string name, MultiDimensionalArray<Color, 2> * tex);
      Texture(std::string name, GLuint tex);
      virtual ~Texture() override;

      void setTextureID(GLuint tex);
      void bind() override;
      virtual std::string getType() override { return "sampler2D"; }

    private:
      GLuint _texture;

      // Inherited via Uniform
    };
  }
}