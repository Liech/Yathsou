#pragma once

#include "../OpenGL/Drawable.h"
#include "glad/glad.h"
#include <memory>

#include "../OpenGL/VBO.h"
#include "../OpenGL/VAO.h"
#include "../OpenGL/ShaderProgram.h"

//2 render triangle with selfmade api

struct Vector3gl {
  float x;
  float y; 
  float z;
  Vector3gl() {};
  Vector3gl(float X, float Y, float Z){
    x = X;
    y = Y;
    z = Z;
  }

  std::vector<AttributeDescription> getBinding() {
    std::vector<AttributeDescription> result;
    result.push_back(AttributeDescription("position", 3, AttributeDescription::DataType::Float));
    return result;
  }
};

class BasicTriangle : public Drawable
{
public:
  BasicTriangle();
  ~BasicTriangle();

  // Inherited via Drawable
  virtual void load(DrawSpecification *) override;
  virtual void draw() override;

private:  
  DrawSpecification* _spec;
  GLuint program;

  std::unique_ptr<VBO<Vector3gl>> _vbo;
  std::unique_ptr<VAO<Vector3gl>> _vao;  
  std::unique_ptr<ShaderProgram>  _shader;
  GLuint vao;
  
  std::string vertex_shader_source;
  std::string fragment_shader_source;
};

