#include "FormationShape.h"  

namespace Superb {
  namespace Formation {
    const Iyathuum::glmAABB<2>& FormationShape::getPosition() {
      return _position;
    }

    void FormationShape::setPosition(const Iyathuum::glmAABB<2>& position) {
      _position = position;
    }
  }
}