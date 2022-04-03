#pragma once

#include <memory>
#include <vector>

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"

namespace Ahwassa {
  class Dot;
  class Box;
  class Line;
  class IBox;
  class Camera;

  class BoxRenderer {
  public:
    BoxRenderer(std::shared_ptr<Camera> camera);

    std::shared_ptr<Dot > newDot (const glm::vec3& pos                        , float size, Iyathuum::Color = Iyathuum::Color(255, 255, 255));
    std::shared_ptr<Line> newLine(const glm::vec3& start, const glm::vec3& end, float size, Iyathuum::Color = Iyathuum::Color(255, 255, 255));
    std::shared_ptr<Box > newBox (const glm::mat4&                                        , Iyathuum::Color = Iyathuum::Color(255, 255, 255));

    glm::vec3 getLightDir()const;
    void setLightDir(const glm::vec3&);

    void draw();
    void clear();
  private:
    void shaderCall(const std::vector<glm::mat4>&, const std::vector<glm::vec3>&, size_t amount);
    void makeShader();
    void makeGeometry();
    void makeModelArray(size_t bufferSize);

    struct RenderVars;
    std::shared_ptr<RenderVars> _vars;
    size_t _bufferSize = 1000;
    glm::vec3 _lightDir;

    std::vector<std::weak_ptr<IBox>> _instances;
  };
}