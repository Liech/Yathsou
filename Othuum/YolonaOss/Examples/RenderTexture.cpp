#include "RenderTexture.h"


#include "GLFW/glfw3.h"

#include "glad/glad.h"
#include "Renderer/TextureRenderer.h"
#include "Util/ImageIO.h"
#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include <IyathuumCoreLib/lib/glm/ext/scalar_constants.hpp>
#include <IyathuumCoreLib/lib/glm/glm.hpp>


namespace YolonaOss {
  void RenderTexture::load(GL::DrawSpecification* d)
  {
    auto im = ImageIO::readImage("cat.png");
    auto im2 = ImageIO::readImage("YolonaOssData\\textures\\SmallMap.png");
    _texture = std::make_unique<GL::Texture>("TestTexture", im.get());
    _texture2 = std::make_unique<GL::Texture>("TestTexture", im2.get());
  }

  void RenderTexture::draw()
  {
    glm::mat4 world(1.0);
    world = glm::rotate(world, -glm::pi<float>() /2.0f, glm::vec3(1, 0, 0)); // where x, y, z is axis of rotation (e.g. 0 1 0)
    world = glm::translate(world, glm::vec3(2,2,0));
    world = glm::scale(world, glm::vec3(10, 10, 10));

    TextureRenderer::start();
    TextureRenderer::drawTexture(_texture.get(), world);
    world = glm::translate(world, glm::vec3(2, 2, 0));
    TextureRenderer::drawTexture(_texture2.get(), world);
    TextureRenderer::end();
  }
}