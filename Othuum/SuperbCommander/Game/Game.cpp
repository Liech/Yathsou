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
#include "NonGame.h"

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

    _nonGame = std::make_unique<NonGame>(w);
  }

  void Game::drawMenu() {
    _ui->start();
    ImGui::Begin("Main Menu",0,ImGuiWindowFlags_AlwaysAutoResize);

    _overlay      ->menu();
    _physic       ->menu();
    _database     ->menu();
    _visualization->menu();
    _control      ->menu();
    _terrain      ->menu();
    _nonGame      ->menu();

    ImGui::End();
    _ui->end();
  }

  void Game::draw() {
    _nonGame->preDraw();
    _overlay->drawFirstLayer();
    _visualization->draw();
    _visualization->drawLastLayer();
    _overlay->drawLastLayer();
    _control->debugDraw();
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
            
  void Game::save(nlohmann::json& output) {
    _overlay      ->save(output);
    _terrain      ->save(output);
    _physic       ->save(output);
    _database     ->save(output);
    _units        ->save(output);
    _visualization->save(output);
    _control      ->save(output);
    _nonGame      ->save(output);
  }

  void Game::load(nlohmann::json& input) {
    _overlay      ->load(input);
    _terrain      ->load(input);
    _physic       ->load(input);
    _database     ->load(input);
    _units        ->load(input);
    _visualization->load(input);
    _control      ->load(input);
    _nonGame      ->load(input);
  }
  void Game::start() {
    _overlay      ->start();
    _physic       ->start();
    _database     ->start();
    _terrain      ->start();
    _units        ->start();
    _visualization->start();
    _control      ->start();
    _nonGame      ->start();
  } 

}