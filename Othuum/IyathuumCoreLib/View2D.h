#pragma once

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"

//thing that should help you with your glm::ortho 2D cam
//Goals: Fancy Mouse Zoom, no deps, follow cam, no tween, best 2d cam without cam out there
namespace Iyathuum {
  class View2D {
  public:
    glmAABB<2> getView();
    void       setView(const glmAABB<2>&);
  private:
    glmAABB<2> _view;
  };
}