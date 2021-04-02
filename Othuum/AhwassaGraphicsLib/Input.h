#pragma once

#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "IyathuumCoreLib/BaseTypes/Keys.h"

struct GLFWwindow;

namespace Ahwassa {
  class Input {
  public:
    Input(GLFWwindow*);

    Iyathuum::KeyStatus  getKeyStatus(Iyathuum::Key key);
    void                 setCursorStatus(Iyathuum::CursorStatus);
    glm::vec2            getCursorPos();
    void                 setCursorPos(glm::vec2 pos);

  private:
    GLFWwindow* _window;
  };
}