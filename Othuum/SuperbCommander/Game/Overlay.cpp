#include "Overlay.h"

#include "AhwassaGraphicsLib/lib/DearIMGUI/imgui.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Drawables/FPS.h"

namespace Superb{
  Overlay::Overlay(Ahwassa::Window& w) {
    fps        = std::make_unique<Ahwassa::FPS>(&w);
  }

  void Overlay::menu() {
    ImGui::Checkbox("Show FPS", &showFPS);
  }

  void Overlay::drawLastLayer() {
    if (showFPS)
      fps->draw();
  }

  void Overlay::drawFirstLayer() {
  }
}