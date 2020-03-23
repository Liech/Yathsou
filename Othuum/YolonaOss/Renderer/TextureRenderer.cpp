#include "TextureRenderer.h"


#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


namespace YolonaOss {
  void TextureRenderer::load(GL::DrawSpecification* spec) {
    _vars.camera = std::make_unique<GL::Camera>("Camera", spec->getCam().get());
    _vars.spec = spec;
    _vars.vertices = {
      GL::PositionTextureVertex(glm::vec3(0, 1, 0),glm::vec2(0.0, 0.0)),
      GL::PositionTextureVertex(glm::vec3(0, 0, 0),glm::vec2(0.0, 1.0)),
      GL::PositionTextureVertex(glm::vec3(1, 0, 0),glm::vec2(1.0, 1.0)),
      GL::PositionTextureVertex(glm::vec3(0, 1, 0),glm::vec2(0.0, 0.0)),
      GL::PositionTextureVertex(glm::vec3(1, 0, 0),glm::vec2(1.0, 1.0)),
      GL::PositionTextureVertex(glm::vec3(1, 1, 0),glm::vec2(1.0, 0.0))
    };
    makeShader();
  }

  void TextureRenderer::drawTexture(MultiDimensionalArray<Color, 2> * texture, glm::mat4 world, glm::vec4 color) {
    GL::Texture t("temporaryTextureRendererTexture", texture);
    drawTexture(&t, world, color);
  }

  void TextureRenderer::drawTexture(GL::Texture* texture, glm::mat4 world, glm::vec4 color) {
    if (_inRenderProcess == false)
      throw std::runtime_error("First call startTextRender, than multiple times drawText and in the end endTextRender. Error in drawText");

    _vars.color->setValue(color);
    _vars.model->setValue(world);
    _vars.shownTexture->setTextureID(texture->getTextureID());

    _vars.color->bind();
    _vars.model->bind();
    _vars.shownTexture->bind();

    //_vars.vbo->setData(_vars.vertices);
    _vars.vao->bind();
  }

  void TextureRenderer::start() {
    if (_inRenderProcess == true)
      throw std::runtime_error("First call startTextRender, than multiple times drawText and in the end endTextRender. Error in startTextRender");
    _inRenderProcess = true;
    _vars.camera->fromCamera(_vars.spec->getCam().get());
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    _vars.shader->bind();
    _vars.camera->bind();
  }

  void TextureRenderer::end() {
    if (_inRenderProcess == false)
      throw std::runtime_error("First call startTextRender, than multiple times drawText and in the end endTextRender. Error in endTextRender");
    _inRenderProcess = false;
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
  }

  void TextureRenderer::makeShader() {
     std::cout << "Load Texture Shader" << std::endl;
    
     std::string vertex_shader_source = R"(
     out vec2 TexCoords;
    
     void main()
     {
         mat4 view = CameraProjection *  CameraView;
         gl_Position = view * model * vec4(position , 1.0);
         TexCoords = texCoord;
     }  
    )";
    
     std::string fragment_shader_source = R"(
     in vec2 TexCoords;
     out vec4 color;
    
     void main()
     {    
         vec4 sampled = texture(shownTexture, TexCoords);
         color = vec4(textureColor.r * sampled.r,textureColor.g * sampled.g,textureColor.b * sampled.b, textureColor.a *  sampled.a);
     }  
    )";

    std::vector<GL::Uniform*> uniforms;
    _vars.shownTexture = std::make_unique<GL::Texture>    ("shownTexture", 0);
    _vars.shownTexture->setBindable(false);
    _vars.color        = std::make_unique<GL::UniformVec4>("textureColor"   );
    _vars.model        = std::make_unique<GL::UniformMat4>("model"          );
    
    std::vector<GL::Uniform*> cameraUniforms = _vars.camera->getUniforms();
    uniforms.insert(uniforms.end(), cameraUniforms.begin(), cameraUniforms.end());
    uniforms.push_back(_vars.shownTexture.get());
    uniforms.push_back(_vars.model.get());
    uniforms.push_back(_vars.color.get());
    
    _vars.vbo = std::make_unique<GL::VBO<GL::PositionTextureVertex>>(_vars.vertices);
    _vars.vao = std::make_unique<GL::VAO<GL::PositionTextureVertex>>(_vars.vbo.get());
    _vars.shader = std::make_unique<GL::ShaderProgram>(_vars.vao.get(), uniforms, vertex_shader_source, fragment_shader_source);
  }
}