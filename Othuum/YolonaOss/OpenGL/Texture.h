#pragma once

#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"
#include "glad/glad.h"
#include "Uniform.h"
namespace YolonaOss {
  namespace GL {
    class Texture : public Uniform {
    public:
      Texture(std::string name, Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2> * tex);
      Texture(std::string name, GLuint tex);
      virtual ~Texture() override;
      virtual bool isTexture() override { return true; }

      void   setTextureID(GLuint tex);
      GLuint getTextureID() const { return _texture; }
      void bind() override;
      virtual std::string getType() override { return "sampler2D"; }
      void release();
    private:
      GLuint _texture;
      bool   _released = false;
      // Inherited via Uniform
    };
  }
}