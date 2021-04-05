#include "Text.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"

namespace Ahwassa {
  void Text::setText(const std::string& text) {
    _text = text;
  }

  std::string Text::getText() const {
    return _text;
  }

  void Text::setPosition(const glm::vec2& position) {
    _position = position;
  }

  glm::vec2 Text::getPosition() const {
    return _position;
  }

  void Text::setColor(const Iyathuum::Color& clr) {
    _color = clr;
  }

  Iyathuum::Color Text::getColor() const {
    return _color;
  }

  void Text::setSize(const float& size) {
    _size = size;
  }

  float Text::getSize() const {
    return _size;
  }
}