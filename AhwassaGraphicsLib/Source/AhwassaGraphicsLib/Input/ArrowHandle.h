#pragma once

#include <functional>

#include <IyathuumCoreLib/BaseTypes/Color.h>
#include <glm/glm.hpp>

namespace Ahwassa {
  class BasicBoxRenderer;

  class ArrowHandle {
  public:
    ArrowHandle(BasicBoxRenderer& renderer, const Iyathuum::Color& color);

    void update();
    void draw  ();

    void setPosition(const glm::vec3& position);
    void setDirection(const glm::vec3& direction);

    glm::vec3 direction() const;
    glm::vec3 position() const;

    void setOnMovedCallback(std::function<void()>);
  private:
  BasicBoxRenderer& _renderer;

    glm::vec3             _position = glm::vec3(0,0,0);
    glm::vec3             _direction= glm::vec3(1,0,0);
    Iyathuum::Color       _color;
    std::function<void()> _onMoved  = []() {};
  };
}