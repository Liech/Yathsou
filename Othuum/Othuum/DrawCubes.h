#pragma once

#include "YolonaOss/OpenGL/Drawable.h"
#include <memory>

#include "YolonaOss/OpenGL/VBO.h"
#include "YolonaOss/OpenGL/VAO.h"
#include "YolonaOss/OpenGL/IBO.h"
#include "YolonaOss/OpenGL/ShaderProgram.h"
#include "YolonaOss/OpenGL/PositionColorNormalVertex.h"
#include <time.h>
#include "YolonaOss/OpenGL/Camera.h"
#include "YolonaOss/OpenGL/Uniform.h"

//5 camera

class DrawCubes : public Drawable
{
public:
  DrawCubes(std::shared_ptr<Camera> camera);

  // Inherited via Drawable
  virtual void load(DrawSpecification *) override;
  virtual void draw() override;

private:
  DrawSpecification* _spec;
  GLuint program;

  std::unique_ptr<UniformVec3>              _light;
  std::unique_ptr<UniformMat4>              _model;
  std::shared_ptr<Camera>                   _camera;
  std::unique_ptr<IBO>                      _ibo;
  std::unique_ptr<VBO<PositionColorNormalVertex>> _vbo;
  std::unique_ptr<VAO<PositionColorNormalVertex>> _vao;
  std::unique_ptr<ShaderProgram>            _shader;
  std::vector<glm::vec3>                    _positions;
  int drawCall = 0;

  std::string vertex_shader_source;
  std::string fragment_shader_source;
};

