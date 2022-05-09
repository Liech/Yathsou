#pragma once

#include <memory>
#include <vector>

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"

namespace Ahwassa {
  class Dot;
  class Decal;
  class Line;
  class Camera;
  class Texture;

  class DecalRenderer {
  public:
    DecalRenderer(std::shared_ptr<Camera> camera);

    std::shared_ptr<Decal> newDecal(const glm::mat4&, Iyathuum::Color = Iyathuum::Color(255, 255, 255));

    void draw(std::shared_ptr<Texture> depthTexture);
    void debugDraw();
    void clear();
  private:
    void shaderCall(const std::vector<glm::mat4>&, const std::vector<glm::mat4>&, const std::vector<glm::vec3>&, size_t amount);
    void makeShader();
    void makeGeometry();
    void makeModelArray(size_t bufferSize);

    struct RenderVars;
    std::shared_ptr<RenderVars> _vars;
    size_t _bufferSize = 1000;
    glm::vec3 _lightDir;

    std::vector<std::weak_ptr<Decal>> _instances;
  };
}