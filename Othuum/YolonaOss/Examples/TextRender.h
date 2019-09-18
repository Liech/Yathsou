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
};

