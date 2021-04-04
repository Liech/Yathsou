#pragma once

#include <memory>
#include <vector>

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"

namespace Ahwassa {
  class InstancedSphere;
  class Camera;

  class InstancedSphereRenderer {
  public:
    InstancedSphereRenderer(std::shared_ptr<Camera> camera);

    std::shared_ptr<InstancedSphere> newSphere (const glm::vec3& pos, float size, Iyathuum::Color = Iyathuum::Color(255, 255, 255));

    glm::vec3 getLightDir()const;
    void setLightDir(const glm::vec3&);

    void draw();
  private:
    void shaderCall(const std::vector<glm::mat4>&, const std::vector<glm::vec3>&, size_t amount);
    void makeShader();
    void makeModelArray(size_t bufferSize);
    void genSphere();

    struct RenderVars;
    std::shared_ptr<RenderVars> _vars;
    size_t _bufferSize = 1000;
    glm::vec3 _lightDir;

    std::vector<std::weak_ptr<InstancedSphere>> _instances;
  };
}