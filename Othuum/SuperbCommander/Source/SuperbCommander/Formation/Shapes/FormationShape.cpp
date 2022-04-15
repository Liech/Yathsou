#include "FormationShape.h"  

#include "AhwassaGraphicsLib/Renderer/BasicRectangleRenderer.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Superb {
  namespace Formation {
    const Iyathuum::glmAABB<2>& FormationShape::getPosition() const {
      return _position;
    }

    void FormationShape::setPosition(const Iyathuum::glmAABB<2>& position) {
      _position = position;
    }

    float FormationShape::getRotation() const {
      return _rotation;
    }

    void  FormationShape::setRotation(float degree) {
      _rotation = degree;
    }

    int FormationShape::getGroup() const {
      return _group;
    }

    void FormationShape::setGroup(int group) {
      _group = group;
    }

    FormationShapeGradientType FormationShape::getGradientType() const {
      return _gradientType;
    }

    void FormationShape::setGradientType(FormationShapeGradientType type) {
      _gradientType = type;
    }

    void FormationShape::setGradientDirection(const float& dir) {
      _gradientDirection = dir;
    }

    float FormationShape::getGradientDirection() const {
      return _gradientDirection;
    }

    void FormationShape::setGradientCenter(const glm::vec2& center) {
      _gradientSphericalCenter = center;
    }

    glm::vec2 FormationShape::getGradientCenter() const {
      return _gradientSphericalCenter;
    }

    std::string FormationShape::ShapeGradientType2String(FormationShapeGradientType type) {
      if (type == FormationShapeGradientType::Directed)
        return "Directed";
      else
        return "Spherical";
    }

    void FormationShape::draw(Ahwassa::BasicRectangleRenderer& renderer) {
      glm::vec3 center = glm::vec3(_position.getCenter()[0], _position.getCenter()[1], 0);
      glm::mat4 rotation = glm::translate(glm::mat4(1.0), center);
      rotation = glm::rotate(rotation, glm::radians(getRotation()), glm::vec3(0, 0, 1));
      rotation = glm::translate(rotation, -center);
      
      if (_gradientType == FormationShapeGradientType::Spherical) {
        glm::vec4 r = glm::vec4(getGradientCenter()[0]+_position.getCenter()[0], getGradientCenter()[1]+_position.getCenter()[1], 0, 1);
        glm::vec2 pos = rotation * r;
        float buttonSize = 15;
        renderer.drawCircle(pos, glm::vec2(buttonSize/3, buttonSize/3), 0, 1, Iyathuum::Color(255, 0, 0));
        renderer.drawCircle(pos, glm::vec2(buttonSize/2, buttonSize/2), 0, 1, Iyathuum::Color(255, 0, 0));
        renderer.drawCircle(pos, glm::vec2(buttonSize, buttonSize), 0, 1, Iyathuum::Color(255, 0, 0));
      }
      else if (_gradientType == FormationShapeGradientType::Directed) {
        const float arrowLength = 20;
        glm::vec2 gDir(std::sin(getGradientDirection()), std::cos(getGradientDirection()));
        glm::vec4 d = glm::vec4(gDir[0] * arrowLength + _position.getCenter()[0], gDir[1] * arrowLength + _position.getCenter()[1], 0, 1);
        glm::vec2 pos = rotation * d;
        renderer.drawDot(_position.getCenter(), 4, Iyathuum::Color(255, 0, 0));
        renderer.drawLine(_position.getCenter(), pos, 2, Iyathuum::Color(255, 0, 0));
        renderer.drawCircle(pos, glm::vec2(6, 6), 0, 1, Iyathuum::Color(255, 0, 0));
      }

    }
  }
}