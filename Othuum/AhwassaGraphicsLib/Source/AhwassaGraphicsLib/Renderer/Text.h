#pragma once

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"

namespace Ahwassa {
  class Text{
  public:
    void setText(const std::string& text);
    std::string getText() const;

    void setPosition(const glm::vec2& position);
    glm::vec2 getPosition() const;

    void setColor(const Iyathuum::Color& clr);
    Iyathuum::Color getColor() const;

    void setSize(const float& size);
    float getSize() const;

  private:
    glm::vec2       _position;
    std::string     _text    ;
    Iyathuum::Color _color   ;
    float           _size    ;
  };
}