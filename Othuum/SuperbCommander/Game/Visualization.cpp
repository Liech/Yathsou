#include "Visualization.h"

#include "AhwassaGraphicsLib/lib/DearIMGUI/imgui.h"

#include "Game.h"
#include "Terrain.h"
#include "Database.h"
#include "Units.h"

#include "SuperbCommander/World.h"
#include "SuperbCommander/UnitsOld.h"
#include "SuperbCommander/UnitsVisualization.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AthanahCommonLib/Map/MapRenderer.h"
#include "AthanahCommonLib/Map/Map.h"
#include "AhwassaGraphicsLib/Vertex/PositionColorNormalVertex.h"
#include "AhwassaGraphicsLib/Geometry/HeightFieldMeshGenerator.h"

namespace Superb {
  Visualization::Visualization(Ahwassa::Window& w, Game& g) : _window(w), _game(g) {    
    _unitsVis = std::make_unique<Superb::UnitsVisualization>(&w, g.database().gamedata(), g.units().units());
    
    // terrain
    std::array<std::string, 5> textures;
    for (int i = 0; i < 5; i++) {
      textures[i] = g.terrain().world().map().scmap().terrainTexturePaths[i].path;
    }
    auto tinter = [&](const std::array<size_t, 2> position, Ahwassa::PositionColorNormalVertex& v) {
      std::array<size_t, 2> half = { position[0] / 2,position[1] / 2 };
      if (position[0] == g.terrain().world().map().scmap().heightMapData->getDimension(0) - 1) half[0] = (position[0] - 1) / 2;
      if (position[1] == g.terrain().world().map().scmap().heightMapData->getDimension(1) - 1) half[1] = (position[1] - 1) / 2;
      v.color = g.terrain().world().map().scmap().highTexture->getVal(half).to4();
    };
    _mapMesh = Ahwassa::HeightFieldMeshGenerator::generate<unsigned short, Ahwassa::PositionColorNormalVertex>(*g.terrain().world().map().scmap().heightMapData, 0, std::numeric_limits<unsigned short>().max(), tinter, 2000, 1);
    _mapRenderer = std::make_unique<Athanah::MapRenderer>(w.camera(), textures, g.database().gamedata());
  }

  void Visualization::menu() {
    ImGui::Checkbox("Draw Terrain", &_drawTerrain);
    ImGui::Checkbox("Unit View", &_unitsView);
    ImGui::Checkbox("Debug Unit View", &_debugUnitView);
  }

  void Visualization::draw() {
    if (_mapRenderer && _mapMesh && _drawTerrain)
      _mapRenderer->draw(*_mapMesh);
    if (_unitsView)
    _unitsVis->draw();

  }

  void Visualization::drawLastLayer() {
    if (_debugUnitView)
      _unitsVis->debugDraw();
  }
}