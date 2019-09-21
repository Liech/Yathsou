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
  class RotatingCube : public GL::Drawable
  {
  public:

    // Inherited via Drawable
    virtual void load(GL::DrawSpecification*) override;
    virtual void draw() override;

  private:
    GL::DrawSpecification* _spec;
    GLuint program;

    std::unique_ptr<GL::UniformVec3>              _light;
    std::unique_ptr<GL::Camera>                   _camera;
    std::unique_ptr<GL::IBO>                      _ibo;
    std::unique_ptr<GL::VBO<GL::PositionColorNormalVertex>> _vbo;
    std::unique_ptr<GL::VAO<GL::PositionColorNormalVertex>> _vao;
    std::unique_ptr<GL::ShaderProgram>            _shader;
    int drawCall = 0;

    std::string vertex_shader_source;
    std::string fragment_shader_source;
  };
}