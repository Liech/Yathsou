#pragma once

#include "../OpenGL/Drawable.h"
#include <memory>

#include "../OpenGL/VBO.h"
#include "../OpenGL/VAO.h"
#include "../OpenGL/IBO.h"
#include "../OpenGL/ShaderProgram.h"
#include "../OpenGL/PositionColorNormalVertex.h"
#include <time.h>
#include "../OpenGL/Camera.h"
#include "../OpenGL/Uniform.h"

//5 camera

namespace YolonaOss {
  namespace GL
  {
    class Texture;
  }
  class RenderTexture : public GL::Drawable
  {
  public:

    // Inherited via Drawable
    virtual void load(GL::DrawSpecification*) override;
    virtual void draw() override;

  private:
    int drawCall = 0;
    std::unique_ptr<GL::Texture> _texture;
  };
}