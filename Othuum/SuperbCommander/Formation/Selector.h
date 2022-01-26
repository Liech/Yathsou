#pragma once

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"

namespace Ahwassa {
  class BasicRectangleRenderer;
}

namespace Superb {
  namespace Formation {
    enum class SelectedEdge {
      None,
      MM,
      MP,//MinusPlus
      PM,
      PP
    };

    class Selector {
    public:
      virtual ~Selector() = default;

      void setSelected(bool);
      void setColor(const Iyathuum::Color&);
      void setPosition(const Iyathuum::glmAABB<2> &);
      void setRotation(float degree);
      Iyathuum::glmAABB<2> setEdge(const glm::vec2& mousePos, SelectedEdge);      

      void draw(Ahwassa::BasicRectangleRenderer&);

      bool insideRotate(const glm::vec2&) const;
      bool insideSelect(const glm::vec2&) const;
      bool insideGradientCenter(const glm::vec2&) const;
      bool insideGradientDirGrip(const glm::vec2&) const;
      SelectedEdge getSelectedEdge(const glm::vec2&) const;      

    private:
      glm::vec2 rot(const glm::vec2&, const glm::mat4&) const;
      glm::vec2 mouse2local(const glm::vec2&) const;
      glm::mat4 getMatrix() const;

      glm::vec2 rotatorPosition() const;

      bool                 _rotationCenterSelectable = false;
      glm::vec2            _rotationCenter = glm::vec2(0, 0);
      float                _rotation = 0;
      glm::mat4            _matrix;
      Iyathuum::glmAABB<2> _position;
      Iyathuum::Color      _color;
      bool                 _selected = false;
    };
  }
}