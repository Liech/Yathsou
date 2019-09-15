#include "TextRender.h"
#include <ft2build.h>
#include FT_FREETYPE_H  
#include <filesystem>
#include <iostream>
#include <map>
#include "OpenGL/Window.h"
#include "OpenGL/ShaderProgram.h"
#include "OpenGL/Uniform.h"
#include "OpenGL/Texture.h"
#include <glm/gtc/matrix_transform.hpp>
//https://learnopengl.com/In-Practice/Text-Rendering

TextRender::TextRender()
{
}


TextRender::~TextRender()
{
}


void TextRender::freetype() {
  std::filesystem::path cwd = std::filesystem::current_path();
  std::string path = cwd.string() + "/" + "YolonaOssData/fonts/arial.ttf";

  FT_Library ft;
  if (FT_Init_FreeType(&ft))
    std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

  FT_Face face;
  if (FT_New_Face(ft, path.c_str(), 0, &face))
    std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

  FT_Set_Pixel_Sizes(face, 0, 48);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

  for (GLubyte c = 0; c < 128; c++)
  {
	  // Load character glyph 
	  if (FT_Load_Char(face, c, FT_LOAD_RENDER))
	  {
      throw std::runtime_error("ERROR::FREETYTPE: Failed to load Glyph");
		  continue;
	  }
	  // Generate texture
	  GLuint texture;
	  glGenTextures(1, &texture);
	  glBindTexture(GL_TEXTURE_2D, texture);
	  glTexImage2D(
		  GL_TEXTURE_2D,
		  0,
		  GL_RED,
		  face->glyph->bitmap.width,
		  face->glyph->bitmap.rows,
		  0,
		  GL_RED,
		  GL_UNSIGNED_BYTE,
		  face->glyph->bitmap.buffer
	  );
	  // Set texture options
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	  // Now store character for later use
	  Character character = {
		  texture,
		  glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
		  glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
		  (GLuint)face->glyph->advance.x
	  };
    _characters.insert(std::pair<GLchar, Character>(c, character));
	  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  }
  FT_Done_Face(face);
  FT_Done_FreeType(ft);
}

void TextRender::makeShader() {
  vertex_shader_source = R"(
    out vec2 TexCoords;

    void main()
    {
        gl_Position = projection * vec4(position.xy, 0.0, 1.0);
        TexCoords = texCoord;
    }  
   )";

  fragment_shader_source = R"(
    in vec2 TexCoords;
    out vec4 color;

    void main()
    {    
        vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
        color = vec4(textColor, 1.0) * sampled;
    }  
   )";

  std::vector<Uniform*> uniforms;  
  _projection  = std::make_unique<UniformMat4>("projection");
  _projection->setValue(glm::ortho(0.0f, (float)_spec->getWindow()->getWidth(), 0.0f, (float)_spec->getWindow()->getHeight()));
  _textColor   = std::make_unique<UniformVec3>("textColor");
  _fontTexture = std::make_unique<Texture>("text", 0);
  uniforms.push_back(_projection.get());
  uniforms.push_back(_textColor.get());
  uniforms.push_back(_fontTexture.get());

  std::vector< PositionTextureVertex> input;
  input.resize(6);
  _vbo = std::make_unique<VBO<PositionTextureVertex>>(input);
  _vao = std::make_unique<VAO<PositionTextureVertex>>(_vbo.get());
  _shader = std::make_unique<ShaderProgram>(_vao.get(), uniforms, vertex_shader_source, fragment_shader_source);
}

void TextRender::load(DrawSpecification *d)
{
  _spec = d;
  freetype();
  makeShader();
}

void TextRender::RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
  // Activate corresponding render state	
  _textColor->setValue(color);
  
  // Iterate through all characters
  std::string::const_iterator c;
  for (c = text.begin(); c != text.end(); c++)
  {
    Character ch = _characters[*c];

    GLfloat xpos = x + ch.Bearing.x * scale;
    GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

    GLfloat w = ch.Size.x * scale;
    GLfloat h = ch.Size.y * scale;
    // Update VBO for each character
    std::vector<PositionTextureVertex> vertices = {
      PositionTextureVertex(glm::vec3(xpos,     ypos + h,0),glm::vec2(0.0, 0.0)),
      PositionTextureVertex(glm::vec3(xpos,     ypos,    0),glm::vec2(0.0, 1.0)),
      PositionTextureVertex(glm::vec3(xpos + w, ypos,    0),glm::vec2(1.0, 1.0)),
      PositionTextureVertex(glm::vec3(xpos,     ypos + h,0),glm::vec2(0.0, 0.0)),
      PositionTextureVertex(glm::vec3(xpos + w, ypos,    0),glm::vec2(1.0, 1.0)),
      PositionTextureVertex(glm::vec3(xpos + w, ypos + h,0),glm::vec2(1.0, 0.0))
    };

    // Render glyph texture over quad
    _fontTexture->setTextureID(ch.TextureID);
    _fontTexture->bind();
    _vbo->setData(vertices);

    x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
    _vao->bind();
  }
}

void TextRender::draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  _shader->bind();
  RenderText("Hello World", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
  RenderText("Yathsou", 1820.0f, 1060.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));

  glDisable(GL_BLEND);
}
