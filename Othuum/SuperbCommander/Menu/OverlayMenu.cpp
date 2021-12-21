#include "OverlayMenu.h"

#include "AhwassaGraphicsLib/lib/DearIMGUI/imgui.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Drawables/FPS.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"

namespace Superb{
  OverlayMenu::OverlayMenu(Ahwassa::Window& w) {
    fps        = std::make_unique<Ahwassa::FPS>(&w);
    background = std::make_unique<Ahwassa::Background>(&w);
  }

  void OverlayMenu::menu() {
    ImGui::Checkbox("Show FPS", &showFPS);
    ImGui::ColorEdit3("Background Color", (float*)&backgroundColor);
  }

  void OverlayMenu::drawLastLayer() {
    if (showFPS)
      fps->draw();
  }

  void OverlayMenu::drawFirstLayer() {
    background->setColor(Iyathuum::Color(backgroundColor));
    background->draw();
  }
}