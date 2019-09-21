#include "TextRenderer.h"


#include <glm/gtc/matrix_transform.hpp>
#include "../OpenGL/DrawSpecification.h"
#include "../OpenGL/Window.h"
#include <ft2build.h>
#include FT_FREETYPE_H  
#include <filesystem>


namespace YolonaOss {
  TextRenderer::RenderVars TextRenderer::_vars;

  void TextRenderer::drawText(std::string text, glm::vec2 pos, float scale, glm::vec3 color) {
    drawText(text, pos[0], pos[1], scale, color);
  }
  void TextRenderer::drawText(std::string text, float x, float y, float scale, glm::vec3 color) {
    if (_inRenderProcess == false)
      throw std::runtime_error("First call startTextRender, than multiple times drawText and in the end endTextRender. Error in drawText");

    // Activate corresponding render state	
    _vars.textColor->setValue(color);
    _vars.textColor->bind();
    // Iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
      Character ch = _vars.characters[*c];

      GLfloat xpos = x + ch.Bearing.x * scale;
      GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

      GLfloat w = ch.Size.x * scale;
      GLfloat h = ch.Size.y * scale;
      // Update VBO for each character
      std::vector<GL::PositionTextureVertex> vertices = {
        GL::PositionTextureVertex(glm::vec3(xpos,     ypos + h,0),glm::vec2(0.0, 0.0)),
        GL::PositionTextureVertex(glm::vec3(xpos,     ypos,    0),glm::vec2(0.0, 1.0)),
        GL::PositionTextureVertex(glm::vec3(xpos + w, ypos,    0),glm::vec2(1.0, 1.0)),
        GL::PositionTextureVertex(glm::vec3(xpos,     ypos + h,0),glm::vec2(0.0, 0.0)),
        GL::PositionTextureVertex(glm::vec3(xpos + w, ypos,    0),glm::vec2(1.0, 1.0)),
        GL::PositionTextureVertex(glm::vec3(xpos + w, ypos + h,0),glm::vec2(1.0, 0.0))
      };

      // Render glyph texture over quad
      _vars.fontTexture->setTextureID(ch.TextureID);
      _vars.fontTexture->bind();
      _vars.vbo->setData(vertices);

      x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
      _vars.vao->bind();
    }
  }

  glm::vec2 TextRenderer::getTextSize(std::string text, float scale) {
    glm::vec2 result(0, 0);
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
      Character ch = _vars.characters[*c];
      result[0] += (ch.Advance >> 6) * scale;
    }
    result[1] = (float)_maxHeight;

    return result;
  }

  void TextRenderer::start() {
    if (_inRenderProcess == true)
      throw std::runtime_error("First call startTextRender, than multiple times drawText and in the end endTextRender. Error in startTextRender");
    _inRenderProcess = true;
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    _vars.shader->bind();
  }

  void TextRenderer::end() {
    if (_inRenderProcess == false)
      throw std::runtime_error("First call startTextRender, than multiple times drawText and in the end endTextRender. Error in endTextRender");
    _inRenderProcess = false;
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
  }

  void TextRenderer::load(GL::DrawSpecification* spec) {
    std::cout << "++++++++++++++++++++++++++++++++++++++++++++++ Load Text Renderer +++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    if (_alreadyLoaded)
      throw std::runtime_error("TextRenderer Twice Initialized.");
    _alreadyLoaded = true;
    _vars.spec = spec;
    makeShader();
    makeFreetype();
    std::cout << "++++++++++++++++++++++++++++++++++++++++++++++ End Of Load Text Renderer +++++++++++++++++++++++++++++++++++++" << std::endl;
  };



  void TextRenderer::makeFreetype() {
    std::cout << "Load Freetype" << std::endl;
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
        (int)texture,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        face->glyph->advance.x
      };
      _maxHeight = (int)std::max(character.Size[1], _maxHeight);
      _vars.characters.insert(std::pair<GLchar, Character>(c, character));
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    }
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
  }

  void TextRenderer::makeShader() {
    std::cout << "Load Shader" << std::endl;

    std::string vertex_shader_source = R"(
    out vec2 TexCoords;

    void main()
    {
        gl_Position = projection * vec4(position.xy, 0.0, 1.0);
        TexCoords = texCoord;
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

    std::vector<GL::Uniform*> uniforms;
    _vars.projection = std::make_unique<GL::UniformMat4>("projection");
    _vars.projection->setValue(glm::ortho(0.0f, (float)_vars.spec->getWindow()->getWidth(), 0.0f, (float)_vars.spec->getWindow()->getHeight()));
    _vars.textColor = std::make_unique<GL::UniformVec3>("textColor");
    _vars.fontTexture = std::make_unique<GL::Texture>("text", 0);
    uniforms.push_back(_vars.projection.get());
    uniforms.push_back(_vars.textColor.get());
    uniforms.push_back(_vars.fontTexture.get());

    std::vector< GL::PositionTextureVertex> input;
    input.resize(6);
    _vars.vbo = std::make_unique<GL::VBO<GL::PositionTextureVertex>>(input);
    _vars.vao = std::make_unique<GL::VAO<GL::PositionTextureVertex>>(_vars.vbo.get());
    _vars.shader = std::make_unique<GL::ShaderProgram>(_vars.vao.get(), uniforms, vertex_shader_source, fragment_shader_source);
  }
}