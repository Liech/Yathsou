#include "RenderTexture.h"


#include "GLFW/glfw3.h"

#include "glad/glad.h"
#include "Renderer/TextureRenderer.h"
#include "Util/ImageIO.h"

namespace YolonaOss {
  void RenderTexture::load(GL::DrawSpecification* d)
  {
    auto im = ImageIO::readImage("cat.png");
    _texture = std::make_unique<GL::Texture>("TestTexture",im.get());
  }

  void RenderTexture::draw()
  {
    TextureRenderer::start();
    TextureRenderer::drawTexture(_texture.get(),glm::mat4(1.0));
    TextureRenderer::end();
  }
}