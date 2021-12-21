#include "Overlay.h"

#include "AhwassaGraphicsLib/lib/DearIMGUI/imgui.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Drawables/FPS.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"

namespace Superb{
  Overlay::Overlay(Ahwassa::Window& w) {
    fps        = std::make_unique<Ahwassa::FPS>(&w);
    background = std::make_unique<Ahwassa::Background>(&w);
  }

  void Overlay::menu() {
    ImGui::Checkbox("Show FPS", &showFPS);
    ImGui::ColorEdit3("Background Color", (float*)&backgroundColor);
  }

  void Overlay::drawLastLayer() {
    if (showFPS)
      fps->draw();
  }

  void Overlay::drawFirstLayer() {
    background->setColor(Iyathuum::Color(backgroundColor));
    background->draw();
  }
}