#pragma once

#include "../OpenGL/Loadable.h"
#include "../structs/Factory.h"
#include "../OpenGL/Texture.h"
#include "../OpenGL/VAO.h"
#include "../OpenGL/VBO.h"
#include "../OpenGL/ShaderProgram.h"
#include "../OpenGL/PositionTextureVertex.h"
#include "../OpenGL/Camera.h"

#include <memory>

namespace YolonaOss {
  namespace GL {
    class ShaderProgram;
    class UniformMat4;
    class UniformVec3;
  }
  class TextureRenderer : public GL::Loadable {
    REGISTER(Loadable, TextureRenderer, "TextureRenderer", { "Main" })
  public:
    TextureRenderer() {}
    virtual          ~TextureRenderer() {}
    virtual void     load(GL::DrawSpecification*) override;

    static void start();
    static void end();
    static void drawTexture(GL::Texture texture, glm::mat4 world, glm::vec4 color = glm::vec4(1,1,1,1));

  private:
    struct RenderVars {
      std::unique_ptr<GL::VBO<GL::PositionTextureVertex>> vbo;
      std::unique_ptr<GL::VAO<GL::PositionTextureVertex>> vao;
      std::unique_ptr<GL::ShaderProgram>              shader;
      GL::DrawSpecification*                          spec = nullptr;
      std::unique_ptr<GL::UniformMat4>                model;
      std::unique_ptr<GL::UniformVec3>                color;
      std::unique_ptr<GL::Texture    >                shownTexture;
      std::unique_ptr<GL::Camera>                     camera;
      std::vector<GL::PositionTextureVertex>          vertices;
    };

    void makeShader();
    static inline RenderVars _vars;
    static inline bool       _inRenderProcess = false;


  };
}