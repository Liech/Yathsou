#pragma once

#include "../OpenGL/Drawable.h"
#include "glad/glad.h"
#include <memory>

#include "../OpenGL/VBO.h"
#include "../OpenGL/VAO.h"
#include "../OpenGL/ShaderProgram.h"


class TextRender : public Drawable
{
public:
  TextRender();
  ~TextRender();

  // Inherited via Drawable
  virtual void load(DrawSpecification *) override;
  virtual void draw() override;

private:  
  DrawSpecification* _spec;
  GLuint program;

  std::unique_ptr<ShaderProgram>  _shader;
  GLuint vao;
  
  std::string vertex_shader_source;
  std::string fragment_shader_source;
};

