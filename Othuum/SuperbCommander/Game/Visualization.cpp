#include "Visualization.h"

#include "AhwassaGraphicsLib/lib/DearIMGUI/imgui.h"

#include "Game.h"
#include "Terrain.h"
#include "Database.h"
#include "Units.h"
#include "Physic.h"

#include "SuperbCommander/World.h"
#include "SuperbCommander/UnitsOld.h"
#include "SuperbCommander/UnitsVisualization.h"
#include "SuperbCommander/PhysicsDebugView.h"

#include "AthanahCommonLib/Map/MapRenderer.h"
#include "AthanahCommonLib/Map/Map.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"
#include "AhwassaGraphicsLib/Vertex/PositionColorNormalVertex.h"
#include "AhwassaGraphicsLib/Geometry/HeightFieldMeshGenerator.h"
#include "AhwassaGraphicsLib/PostProcessing/DeferredComposer.h"

namespace Superb {
  Visualization::Visualization(Ahwassa::Window& w, Game& g) : _window(w), _game(g) {    

  }

  void Visualization::menu() {
    ImGui::ColorEdit3("Background Color", (float*)&_backgroundColor);
    ImGui::Checkbox("Draw Terrain", &_drawTerrain);
    ImGui::Checkbox("Unit View", &_unitsView);
    ImGui::Checkbox("Debug Unit View", &_debugUnitView);
    ImGui::Checkbox("Debug Physic View", &_debugPhysicView);    
    if (ImGui::BeginCombo("Renderer", getRendererNames(_currentRendererMode).c_str(), 0)) {
      if (ImGui::Selectable("Result", _currentRendererMode == RendererModes::Result))
        _currentRendererMode = RendererModes::Result;
      if (ImGui::Selectable("Depth", _currentRendererMode == RendererModes::Depth))
        _currentRendererMode = RendererModes::Depth;
      if (ImGui::Selectable("gPosition", _currentRendererMode == RendererModes::gPosition))
        _currentRendererMode = RendererModes::gPosition;
      if (ImGui::Selectable("gNormal", _currentRendererMode == RendererModes::gNormal))
        _currentRendererMode = RendererModes::gNormal;
      if (ImGui::Selectable("gAlbedoSpec", _currentRendererMode == RendererModes::gAlbedoSpec))
        _currentRendererMode = RendererModes::gAlbedoSpec;
      if (ImGui::Selectable("gSpecial", _currentRendererMode == RendererModes::gSpecial))
        _currentRendererMode = RendererModes::gSpecial;

      ImGui::EndCombo();
    }
  }

  std::string Visualization::getRendererNames(RendererModes mode) {
    if (mode == RendererModes::Result)
      return "Result";
    else if (mode == RendererModes::Depth)
      return "Depth";
    else if (mode == RendererModes::gPosition)
      return "gPosition";
    else if (mode == RendererModes::gNormal)
      return "gNormal";
    else if (mode == RendererModes::gAlbedoSpec)
      return "gAlbedoSpec";
    else if (mode == RendererModes::gSpecial)
      return "gSpecial";
    return "Unkown";
  }

  void Visualization::draw() {
    _composer->start();

    _background->setColor(Iyathuum::Color(_backgroundColor));
    _background->draw();

    if (_mapRenderer && _mapMesh && _drawTerrain)
      _mapRenderer->draw(*_mapMesh);
    if (_unitsView)
    _unitsVis->draw();

    _composer->end();

    _textureRenderer->start();

    std::shared_ptr<Ahwassa::Texture> tex;
    if (_currentRendererMode == RendererModes::Result)
      tex = _composer->getResult();
    else if (_currentRendererMode == RendererModes::Depth)
      tex = _composer->getDepth();
    else if (_currentRendererMode == RendererModes::gPosition)
      tex = _composer->getRawTextures()[0];
    else if (_currentRendererMode == RendererModes::gNormal)
      tex = _composer->getRawTextures()[1];
    else if (_currentRendererMode == RendererModes::gAlbedoSpec)
      tex = _composer->getRawTextures()[2];
    else if (_currentRendererMode == RendererModes::gSpecial)
      tex = _composer->getRawTextures()[3];
    else throw std::runtime_error("Unkown render mode");

    _textureRenderer->draw(*tex, Iyathuum::glmAABB<2>(glm::vec2(0), glm::vec2(_window.getWidth(), _window.getHeight())), true);
    _textureRenderer->end();

    _composer->blitDepth();
  }

  void Visualization::drawLastLayer() {
    if (_debugPhysicView)
      _physicDebug->draw();
    if (_debugUnitView)
      _unitsVis->debugDraw();
  }

  void Visualization::save(nlohmann::json& output) {
    output["DrawTerrain"]     = _drawTerrain;
    output["DebugPhysicView"] = _debugPhysicView;
    output["UnitsView"]       = _unitsView;
    output["BackgroundColor"] = { _backgroundColor[0],_backgroundColor[1],_backgroundColor[2] };
    output["RendererMode"]    = (int)_currentRendererMode;
    output["ScreenWidth"]     = _screenWidth ;
    output["ScreenHeight"]    = _screenHeight;

    auto p = _window.camera()->getPosition();
    output["CameraPosition"] = { p[0],p[1],p[2] };
    auto t = _window.camera()->getTarget();
    output["CameraTarget"] = { t[0],t[1],t[2] };
  }

  void Visualization::load(nlohmann::json& input) {
    _drawTerrain         = input["DrawTerrain"];
    _debugPhysicView     = input["DebugPhysicView"];
    _unitsView           = input["UnitsView"];
    _backgroundColor[0]  = input["BackgroundColor"][0];
    _backgroundColor[1]  = input["BackgroundColor"][1];
    _backgroundColor[2]  = input["BackgroundColor"][2];
    _currentRendererMode = (RendererModes)input["RendererMode"];
    _screenWidth  = input["ScreenWidth"];
    _screenHeight = input["ScreenHeight"];

    _window.camera()->setPosition(glm::vec3(input["CameraPosition"][0],input["CameraPosition"][1],input["CameraPosition"][2]));
    _window.camera()->setTarget  (glm::vec3(input["CameraTarget"][0],input["CameraTarget"][1],input["CameraTarget"][2]));
  }

  void Visualization::start() {
    _unitsVis = std::make_unique<Superb::UnitsVisualization>(&_window, _game.database().gamedata(), _game.units().units());

    // terrain
    std::array<std::string, 5> textures;
    for (int i = 0; i < 5; i++) {
      textures[i] = _game.terrain().world().map().scmap().terrainTexturePaths[i].path;
    }
    auto tinter = [&](const std::array<size_t, 2> position, Ahwassa::PositionColorNormalVertex& v) {
      std::array<size_t, 2> half = { position[0] / 2,position[1] / 2 };
      if (position[0] == _game.terrain().world().map().scmap().heightMapData->getDimension(0) - 1) half[0] = (position[0] - 1) / 2;
      if (position[1] == _game.terrain().world().map().scmap().heightMapData->getDimension(1) - 1) half[1] = (position[1] - 1) / 2;
      v.color = _game.terrain().world().map().scmap().highTexture->getVal(half).to4();
    };
    _mapMesh = Ahwassa::HeightFieldMeshGenerator::generate<unsigned short, Ahwassa::PositionColorNormalVertex>(*_game.terrain().world().map().scmap().heightMapData, 0, std::numeric_limits<unsigned short>().max(), tinter, 2000, 1);
    _mapRenderer = std::make_unique<Athanah::MapRenderer>(_window.camera(), textures, _game.database().gamedata());
    //terrain end

    _background = std::make_unique<Ahwassa::Background>(&_window);
    _physicDebug = std::make_unique<Superb::PhysicsDebugView>(_game.physic().physic(), &_window);
    _composer = std::make_unique<Ahwassa::DeferredComposer>(&_window, _window.getWidth(), _window.getHeight());
    _textureRenderer = std::make_unique< Ahwassa::BasicTexture2DRenderer>(&_window);
  }
}