#include "FormationShape.h"  

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
  }
}