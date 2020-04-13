#pragma once

#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"
#include "glad/glad.h"
#include "Uniform.h"
#include "../OpenGL/DrawableList.h"
namespace YolonaOss {
  namespace GL {
    class Rendertarget : public Uniform, public DrawableList {
    public:
      Rendertarget(std::string name, size_t nX, size_t nY);
      ~Rendertarget();

      void bind() override;
      virtual std::string getType() override { return "sampler2D"; }
      virtual void draw() override;

    private:
      GLuint _texture;
      GLuint _framebuffer;
      GLuint _renderbuffer;

      size_t _nX;
      size_t _nY;

      // Inherited via Uniform
    };
  }
}