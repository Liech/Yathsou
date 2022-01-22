#include "Selector.h"

#include "AhwassaGraphicsLib/BasicRenderer/BasicRectangleRenderer.h"
#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>

namespace Superb {
  namespace Formation {
    void Selector::setPosition(const Iyathuum::glmAABB<2>& pos) {
      _position = pos;
    }

    void Selector::draw(Ahwassa::BasicRectangleRenderer& renderer) {
      const float extra = 3;
      const auto p = _position.getPosition() - glm::vec2(extra, extra);
      const auto s = _position.getSize() + glm::vec2(extra*2,extra*2);
      updateMatrix();

      renderer.drawLine(rot(p), rot(p + glm::vec2(10, 0)), 3, _color);
      renderer.drawLine(rot(p), rot(p + glm::vec2(0, 10)), 3, _color);

      const auto p2 = p + glm::vec2(s[0], 0);
      renderer.drawLine(rot(p2), rot(p2 + glm::vec2(-10, 0)), 3, _color);
      renderer.drawLine(rot(p2), rot(p2 + glm::vec2(0, 10) ), 3 , _color);
      
      const auto p3 = p + glm::vec2(0, s[0]);
      renderer.drawLine(rot(p3), rot(p3 + glm::vec2(10, 0) ), 3 , _color);
      renderer.drawLine(rot(p3), rot(p3 + glm::vec2(0, -10)), 3, _color);
      
      const auto p4 = p + s;
      renderer.drawLine(rot(p4), rot(p4 + glm::vec2(-10, 0)), 3, _color);
      renderer.drawLine(rot(p4), rot(p4 + glm::vec2(0, -10)), 3, _color);

      if (_selected) {
        renderer.drawCircle(rotatorPosition(), glm::vec2(5,5), 0, 1, _color);
      }
    }

    glm::vec2 Selector::rot(const glm::vec2& pos) {
      glm::vec4 v = _matrix * glm::vec4(pos[0], pos[1], 0,1);
      return glm::vec2(v[0], v[1]);
    }

    void Selector::updateMatrix(){
      glm::vec3 center = glm::vec3(_position.getCenter()[0], _position.getCenter()[1], 0);
      glm::mat4 rotation = glm::translate(glm::mat4(1.0), center);
      rotation = glm::rotate(rotation, glm::radians(_rotation), glm::vec3(0, 0, 1));
      _matrix = glm::translate(rotation, -center);
    }

    void Selector::setRotation(float degree) {
      _rotation = degree;
    }

    void Selector::setSelected(bool sel) {
      _selected = sel;
    }

    void Selector::setColor(const Iyathuum::Color& clr) {
      _color = clr;
    }

    bool Selector::insideRotate(const glm::vec2& mousePos) {
      return glm::distance(mousePos, rotatorPosition()) < 5;
    }

    bool Selector::insideSelect(const glm::vec2& mousePos) {
      glm::vec3 center = glm::vec3(_position.getCenter()[0], _position.getCenter()[1], 0);
      glm::mat4 rotation = glm::translate(glm::mat4(1.0), center);
      rotation = glm::rotate(rotation, -glm::radians(_rotation), glm::vec3(0, 0, 1));
      rotation = glm::translate(rotation, -center);

      glm::vec4 v = rotation * glm::vec4(mousePos[0], mousePos[1], 0, 1);
      glm::vec2 mp = glm::vec2(v[0], v[1]);      
      return _position.isInside(mp);
    }

    glm::vec2 Selector::rotatorPosition() {
      updateMatrix();
      const float extra = 3;
      const auto p = _position.getCenter()-glm::vec2(0,_position.getSize()[1]/2 + extra);
      return rot(p - glm::vec2(0, 10));
    }

  }
}