#pragma once

//#include "structs/Factory.h"
#include "../OpenGL/Loadable.h"
#include <iostream>
#include "../structs/Factory.h"
#include "glm/glm.hpp"
#include <memory>

#include <map>
#include "../OpenGL/VAO.h"
#include "../OpenGL/VBO.h"
#include "../OpenGL/Texture.h"
#include "../OpenGL/ShaderProgram.h"
#include "../OpenGL/PositionTextureVertex.h"
class ShaderProgram;
class UniformMat4;
class UniformVec3;
//https://learnopengl.com/In-Practice/Text-Rendering

class TextRenderer : public Loadable {
REGISTER(Loadable, TextRenderer, "TextRenderer", { "PreDrawCall" })
public:
                   TextRenderer() {}
  virtual          ~TextRenderer() {}
  static void      startTextRender();
  static void      endTextRender();
  static void      drawText(std::string text, float x, float y, float scale, glm::vec3 color);
  static void      drawText(std::string text, glm::vec2 pos, float scale, glm::vec3 color);
  static glm::vec2 getTextSize(std::string text, float scale);
  virtual void     load(DrawSpecification*) override;
  
private:
  struct Character {
    int        TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    int        Advance;    // Offset to advance to next glyph
  };
  struct RenderVars {
    std::unique_ptr<VBO<PositionTextureVertex>> vbo        ;
    std::unique_ptr<VAO<PositionTextureVertex>> vao        ;
    std::unique_ptr<ShaderProgram>              shader     ;
    DrawSpecification*                          spec       ;
    std::map<char, TextRenderer::Character>     characters ;
    std::unique_ptr<UniformMat4>                projection ;
    std::unique_ptr<UniformVec3>                textColor  ;
    std::unique_ptr<Texture    >                fontTexture;
  };

  void makeShader();
  void makeFreetype();

  static inline bool       _alreadyLoaded = false;
  static inline bool       _inRenderProcess = false;
  static RenderVars _vars;
  static inline int        _maxHeight = 0;

};