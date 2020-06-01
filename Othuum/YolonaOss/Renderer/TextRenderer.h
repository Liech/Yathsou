#pragma once

//#include "structs/Factory.h"
#include "../OpenGL/Loadable.h"
#include <iostream>
#include "IyathuumCoreLib/Singleton/Factory.h"
#include "glm/glm.hpp"
#include <memory>

#include <map>
#include "../OpenGL/VAO.h"
#include "../OpenGL/VBO.h"
#include "IyathuumCoreLib/BaseTypes/AABB.h"
#include "../OpenGL/Texture.h"
#include "../OpenGL/ShaderProgram.h"
#include "../OpenGL/PositionTextureVertex.h"
//https://learnopengl.com/In-Practice/Text-Rendering

namespace YolonaOss {
  namespace GL {
    class ShaderProgram;
    class UniformMat4;
    class UniformVec3;
  }
  class TextRenderer : public GL::Loadable {
    REGISTER(Loadable, TextRenderer, "TextRenderer", { "Main" })
  public:
    TextRenderer() {}
    virtual          ~TextRenderer() {}
    static void      start();
    static void      end();
    static void      drawText(std::string text, float x, float y, float scale, glm::vec3 color);
    static void      drawText(std::string text, glm::vec2 pos, float scale, glm::vec3 color);
    static glm::vec2 getTextSize(std::string text, float scale);
    static void      setClippingRectangle(Iyathuum::AABB<2> box);
    static void      disableClipping(Iyathuum::AABB<2> box);
    virtual void     load(GL::DrawSpecification*) override;

  private:
    struct Character {
      int        TextureID;  // ID handle of the glyph texture
      glm::ivec2 Size;       // Size of glyph
      glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
      int        Advance;    // Offset to advance to next glyph
    };
    struct RenderVars {
      std::unique_ptr<GL::VBO<GL::PositionTextureVertex>> vbo;
      std::unique_ptr<GL::VAO<GL::PositionTextureVertex>> vao;
      std::unique_ptr<GL::ShaderProgram>              shader;
      GL::DrawSpecification* spec = nullptr;
      std::map<char, TextRenderer::Character>     characters;
      std::unique_ptr<GL::UniformMat4>                projection;
      std::unique_ptr<GL::UniformVec3>                textColor;
      std::unique_ptr<GL::Texture    >                fontTexture;
    };

    void makeShader();
    void makeFreetype();

    static inline bool              _alreadyLoaded   = false;
    static inline bool              _inRenderProcess = false;
    static inline bool              _clipping        = false;
    static inline Iyathuum::AABB<2> _clippingBox            ;

    static RenderVars _vars;
    static inline int        _maxHeight = 0;

  };
}