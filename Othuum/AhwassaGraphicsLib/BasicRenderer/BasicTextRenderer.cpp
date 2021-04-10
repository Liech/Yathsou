#include "BasicTextRenderer.h"

#include "glad/glad.h"
#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H  
#include <filesystem>

#include "BufferObjects/VBO.h"
#include "BufferObjects/VAO.h"
#include "Vertex/PositionTextureVertex.h"
#include "Core/ShaderProgram.h"
#include "Core/Window.h"
#include "Uniforms/UniformMat4.h"
#include "Uniforms/UniformVec3.h"
#include "Uniforms/Texture.h"

namespace Ahwassa {
  struct BasicTextRenderer::RenderVars {
    std::unique_ptr<VBO<PositionTextureVertex>> vbo;
    std::unique_ptr<VAO>                        vao;
    std::unique_ptr<ShaderProgram>              shader;
    Window*                                     window;
    std::map<char, BasicTextRenderer_Character> characters;
    std::unique_ptr<UniformMat4>                projection;
    std::unique_ptr<UniformVec3>                textColor;
    std::unique_ptr<Texture    >                fontTexture;
  };

  BasicTextRenderer::BasicTextRenderer(Window* w) {
    _vars = std::make_shared<BasicTextRenderer::RenderVars>();
    _vars->window = w;
    makeShader();
    makeFreetype();
  }

  void BasicTextRenderer::drawText(std::string text, glm::vec2 pos, float scale, Iyathuum::Color color) {
    drawText(text, pos[0], pos[1], scale, color);
  }
  void BasicTextRenderer::drawText(std::string text, float x, float y, float scale, Iyathuum::Color color) {
    if (_inRenderProcess == false)
      throw std::runtime_error("First call startTextRender, than multiple times drawText and in the end endTextRender. Error in drawText");

    // Activate corresponding render state	
    _vars->textColor->setValue(color.to3());
    _vars->textColor->bind();
    // Iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
      BasicTextRenderer_Character ch = _vars->characters[*c];

      GLfloat xpos = x + ch.Bearing.x * scale;
      GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

      GLfloat w = ch.Size.x * scale;
      GLfloat h = ch.Size.y * scale;

      Iyathuum::glmAABB<2> box = Iyathuum::glmAABB<2>(glm::vec2(xpos,ypos), glm::vec2(w,h));

      if (_clipping)
        box = _clippingBox.getIntersection(box);

      glm::vec2 pos  = glm::vec2(box.getPosition()[0],box.getPosition()[1]);
      glm::vec2 size = glm::vec2(box.getSize()[0], box.getSize()[1]);

      // Update VBO for each character
      std::vector<PositionTextureVertex> vertices = {
        PositionTextureVertex(glm::vec3(pos[0]          , pos[1] + size[1],    0),glm::vec2(0.0, 0.0)),
        PositionTextureVertex(glm::vec3(pos[0]          , pos[1]          ,    0),glm::vec2(0.0, 1.0)),
        PositionTextureVertex(glm::vec3(pos[0] + size[0], pos[1]          ,    0),glm::vec2(1.0, 1.0)),
        PositionTextureVertex(glm::vec3(pos[0]          , pos[1] + size[1],    0),glm::vec2(0.0, 0.0)),
        PositionTextureVertex(glm::vec3(pos[0] + size[0], pos[1]          ,    0),glm::vec2(1.0, 1.0)),
        PositionTextureVertex(glm::vec3(pos[0] + size[0], pos[1] + size[1],    0),glm::vec2(1.0, 0.0))
      };

      // Render glyph texture over quad
      _vars->fontTexture->setTextureID(ch.TextureID);
      _vars->fontTexture->bind();
      _vars->vbo->setData(vertices);

      x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
      _vars->vao->draw();
    }
  }

  glm::vec2 BasicTextRenderer::getTextSize(std::string text, float scale) {
    glm::vec2 result(0, 0);
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
      BasicTextRenderer_Character ch = _vars->characters[*c];
      result[0] += (ch.Advance >> 6) * scale;
    }
    result[1] = (float)_maxHeight;

    return result;
  }

  void BasicTextRenderer::start() {
    if (_inRenderProcess == true)
      throw std::runtime_error("First call startTextRender, than multiple times drawText and in the end endTextRender. Error in startTextRender");
    _inRenderProcess = true;
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    _vars->shader->bind();
  }

  void BasicTextRenderer::end() {
    if (_inRenderProcess == false)
      throw std::runtime_error("First call startTextRender, than multiple times drawText and in the end endTextRender. Error in endTextRender");
    _inRenderProcess = false;
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
  }

  void BasicTextRenderer::makeFreetype() {
    std::cout << "Load Freetype" << std::endl;
    std::filesystem::path cwd = std::filesystem::current_path();
    std::string path = cwd.string() + "/" + "Data/Fonts/arial.ttf";

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
      throw std::runtime_error("ERROR::FREETYPE: Could not init FreeType Library");

    FT_Face face;
    if (FT_New_Face(ft, path.c_str(), 0, &face))
      throw std::runtime_error("ERROR::FREETYPE: Failed to load font");

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
      BasicTextRenderer_Character character = {
        (int)texture,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        face->glyph->advance.x
      };
      _maxHeight = (int)std::max(character.Size[1], _maxHeight);
      _vars->characters.insert(std::pair<GLchar, BasicTextRenderer_Character>(c, character));
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    }
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
  }

  void BasicTextRenderer::makeShader() {
    std::cout << "Load Shader" << std::endl;

    std::string vertex_shader_source = R"(
    out vec2 TexCoords;

    void main()
    {
        gl_Position = projection * vec4(position.xy, 0.0, 1.0);
        TexCoords = texture;
    }  
   )";

    std::string fragment_shader_source = R"(
    in vec2 TexCoords;
    out vec4 color;

    void main()
    {    
        vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
        color = vec4(textColor, 1.0) * sampled;
    }  
   )";

    std::vector<Uniform*> uniforms;
    _vars->projection = std::make_unique<UniformMat4>("projection");
    _vars->projection->setValue(glm::ortho(0.0f, (float)_vars->window->getWidth(), 0.0f, (float)_vars->window->getHeight()));
    _vars->textColor = std::make_unique<UniformVec3>("textColor");
    _vars->fontTexture = std::make_unique<Texture>("text", 0);
    uniforms.push_back(_vars->projection .get());
    uniforms.push_back(_vars->textColor  .get());
    uniforms.push_back(_vars->fontTexture.get());

    std::vector< PositionTextureVertex> input;
    input.resize(6);
    _vars->vbo = std::make_unique<VBO<PositionTextureVertex>>(input);
    _vars->vao = std::make_unique<VAO>(_vars->vbo.get());
    _vars->shader = std::make_unique<ShaderProgram>(PositionTextureVertex::getBinding(), uniforms, vertex_shader_source, fragment_shader_source);
  }

  void BasicTextRenderer::setClippingRectangle(Iyathuum::glmAABB<2> box) {
    _clipping = true;
    _clippingBox = box;
  }

  void BasicTextRenderer::disableClipping() {
    _clipping = false;
  }
}