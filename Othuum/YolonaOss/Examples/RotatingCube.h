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

class RotatingCube : public Drawable
{
public:

  // Inherited via Drawable
  virtual void load(DrawSpecification *) override;
  virtual void draw() override;

private:
  DrawSpecification* _spec;
  GLuint program;

  std::unique_ptr<UniformVec3>              _light;
  std::unique_ptr<Camera>                   _camera;
  std::unique_ptr<IBO>                      _ibo;
  std::unique_ptr<VBO<PositionColorNormalVertex>> _vbo;
  std::unique_ptr<VAO<PositionColorNormalVertex>> _vao;
  std::unique_ptr<ShaderProgram>            _shader;
  int drawCall = 0;

  std::string vertex_shader_source;
  std::string fragment_shader_source;
};

