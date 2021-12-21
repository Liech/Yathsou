#include "Game.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Input/IMGUIRenderer.h"
#include "AhwassaGraphicsLib/lib/DearIMGUI/imgui.h"

#include "Overlay.h"
#include "World.h"
#include "Terrain.h"
#include "Physic.h"
#include "Database.h"

namespace Superb {
  Game::Game(Ahwassa::Window& w) {
    _ui = std::make_unique<Ahwassa::IMGUIRenderer>(&w);

    _overlay  = std::make_unique<Overlay>(w);
    _terrain  = std::make_unique<Terrain>();
    _physic   = std::make_unique<Physic >();
    _database = std::make_unique<Database>();
  }

  void Game::drawMenu() {
    _ui->start();
    ImGui::Begin("Main Menu");                          // Create a window called "Hello, world!" and append into it.

    _overlay ->menu();
    _physic  ->menu();
    _database->menu();

    ImGui::End();
    _ui->end();
  }

  void Game::drawFirstLayer() {
    _overlay->drawFirstLayer();
  }

  void Game::drawLastLayer() {
    _overlay->drawLastLayer();
  }

  void Game::update() {
    _physic->update();
  }

  Physic& Game::physic() {
    return *_physic;
  }

  Database& Game::database() {
    return *_database;
  }

}