#pragma once

#include "BaseTypes/glmAABB.h"

//thing that should help you with your glm::ortho 2D cam
//Goals: Fancy Mouse Zoom, no deps, follow cam, no tween, best 2d cam without cam out there
namespace Iyathuum {
  class View2D {
  public:
    View2D(const glmAABB<2>&);

    glmAABB<2> getView();
    void       setView(const glmAABB<2>&);

    void       move(glm::vec2 amount);
    glm::vec2  getCenter();
  private:
    glmAABB<2> _view;
  };
}