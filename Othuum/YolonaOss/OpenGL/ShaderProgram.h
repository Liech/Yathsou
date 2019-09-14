#pragma once

#include "VAO.h"
#include "IBO.h"
#include "Uniform.h"
#include <string>

class ShaderProgram
{
public:
  ShaderProgram(VAO_I* vao, std::vector<Uniform*> uniforms, std::string vs, std::string fs);
  ~ShaderProgram();


  void bind();
  GLuint getID() { return _program; };

private:
  std::string _vertexShader;
  std::string _fragmentShader;

  VAO_I* _vao;
  GLuint _program;
  std::vector<Uniform*> _uniform;
  std::vector<bool>     _uniformIsActive;

  std::string toGLSL_vs();
  std::string toGLSL_fs();
  void checkUsageOfUniforms();
};

