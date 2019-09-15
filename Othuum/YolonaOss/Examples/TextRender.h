#pragma once

#include "../OpenGL/Drawable.h"
#include "glad/glad.h"
#include <memory>
#include <map>

#include "../OpenGL/VBO.h"
#include "../OpenGL/VAO.h"
#include "../OpenGL/ShaderProgram.h"
#include "../OpenGL/VBO.h"
#include "../OpenGL/VAO.h"
#include "../OpenGL/PositionTextureVertex.h"

class UniformMat4;
class UniformVec3;
class Texture;


struct Character {
	GLuint     TextureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};


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

  std::unique_ptr<UniformMat4> _projection;
  std::unique_ptr<UniformVec3> _textColor;
  std::unique_ptr<Texture> _fontTexture;
  

  void freetype();
  void makeShader();
  void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

  std::string vertex_shader_source;
  std::string fragment_shader_source;
  std::unique_ptr<VBO<PositionTextureVertex>> _vbo;
  std::unique_ptr<VAO<PositionTextureVertex>> _vao;
  std::map<GLchar, Character> _characters;
};

