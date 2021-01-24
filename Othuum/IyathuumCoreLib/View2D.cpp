#include "View2D.h"

namespace Iyathuum {

  View2D::View2D(const glmAABB<2>& view) {
    _view = view;
  }

  glmAABB<2> View2D::getView() {
    return _view;
  }

  void View2D::setView(const glmAABB<2>& view) {
    _view = view;
  }

  void View2D::move(glm::vec2 amount){
    _view.setPosition(_view.getPosition() + amount);
  }

  glm::vec2 View2D::getCenter() {
    return _view.getCenter();
  }

}