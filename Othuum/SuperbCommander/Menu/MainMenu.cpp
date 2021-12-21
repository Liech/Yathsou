#include "MainMenu.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Input/IMGUIRenderer.h"
#include "AhwassaGraphicsLib/lib/DearIMGUI/imgui.h"

#include "OverlayMenu.h"

namespace Superb {
  MainMenu::MainMenu(Ahwassa::Window& w) {
    ui = std::make_unique<Ahwassa::IMGUIRenderer>(&w);
    overlay = std::make_unique<OverlayMenu>(w);

  }

  void MainMenu::drawMenu() {
    ui->start();
    ImGui::Begin("Main Menu");                          // Create a window called "Hello, world!" and append into it.

    overlay->menu();


    ImGui::End();
    ui->end();
  }

  void MainMenu::drawFirstLayer() {
    overlay->drawFirstLayer();
  }

  void MainMenu::drawLastLayer() {
    overlay->drawLastLayer();
  }
}