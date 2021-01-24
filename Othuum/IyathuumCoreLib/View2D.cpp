#include "View2D.h"

namespace Iyathuum {
  glmAABB<2> View2D::getView() {
    return _view;
  }

  void View2D::setView(const glmAABB<2>& view) {
    _view = view;
  }
}