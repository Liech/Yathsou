#include "Game.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Input/IMGUIRenderer.h"
#include "AhwassaGraphicsLib/lib/DearIMGUI/imgui.h"

#include "Overlay.h"
#include "World.h"
#include "Terrain.h"
#include "Physic.h"
#include "Database.h"
#include "Units.h"
#include "Visualization.h"
#include "Control.h"

namespace Superb {
  Game::Game(Ahwassa::Window& w) {
    _ui = std::make_unique<Ahwassa::IMGUIRenderer>(&w);

    _overlay       = std::make_unique<Overlay >(w);
    _physic        = std::make_unique<Physic  >();
    _database      = std::make_unique<Database>();
    _terrain       = std::make_unique<Terrain >(*_physic, *_database);
    _units         = std::make_unique<Units   >(*_physic, *_database);
    
    _visualization = std::make_unique<Visualization>(w,*this);
    _control       = std::make_unique<Control>(w,*this);
  }

  void Game::drawMenu() {
    _ui->start();
    ImGui::Begin("Main Menu");                          // Create a window called "Hello, world!" and append into it.

    _overlay ->menu();
    _physic  ->menu();
    _database->menu();
    _visualization->menu();
    _control->menu();

    ImGui::End();
    _ui->end();
  }

  void Game::draw() {
    _overlay->drawFirstLayer();
    _visualization->draw();
    _visualization->drawLastLayer();
    _overlay->drawLastLayer();
  }

  void Game::update() {
    _physic ->update();
    _units  ->update();
    _control->update();
  }

  Physic& Game::physic() {
    return *_physic;
  }

  Database& Game::database() {
    return *_database;
  }

  Terrain& Game::terrain() {
    return *_terrain;
  }

  Units& Game::units() {
    return *_units;
  }

  Overlay& Game::overlay() {
    return *_overlay;
  }


}