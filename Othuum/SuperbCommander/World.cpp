#include "World.h"

#include "AezeselFileIOLib/ImageIO.h"

#include "AthanahCommonLib/Map/Map.h"
#include "AthanahCommonLib/Map/MapRenderer.h"

#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Vertex/PositionColorNormalVertex.h"
#include "AhwassaGraphicsLib/BufferObjects/IMesh.h"
#include "AhwassaGraphicsLib/Geometry/HeightFieldMeshGenerator.h"

#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "SuthanusPhysicsLib/Box.h"

namespace Superb {
  World::World(Ahwassa::Window* window, std::shared_ptr<Suthanus::PhysicEngine> physic,std::shared_ptr<Athanah::Map> map) {
    _map    = map   ;
    _window = window;
    _physic = physic;
    map->loadFull();

    std::array<std::shared_ptr<Ahwassa::Texture>, 5> textures;
    for (int i = 0; i < 5; i++) {
      std::string path = "Data" + map->scmap().terrainTexturePaths[i].path;
      auto img = Aezesel::ImageIO::readImage(path);
      textures[i] = std::make_shared<Ahwassa::Texture>("TerrainTexture" + std::to_string(i), img.get());
    }

    _obj = _physic->newBox(glm::vec3(0, 0, 0), glm::vec3(4, 4, 4), false);

    _mapRenderer = std::make_shared<Athanah::MapRenderer>(window->camera(), textures);

    auto tinter = [&](const std::array<size_t, 2> position, Ahwassa::PositionColorNormalVertex& v) {
      std::array<size_t, 2> half = { position[0] / 2,position[1] / 2 };
      if (position[0] == map->scmap().heightMapData->getDimension(0) - 1) half[0] = (position[0] - 1) / 2;
      if (position[1] == map->scmap().heightMapData->getDimension(1) - 1) half[1] = (position[1] - 1) / 2;
      v.color = map->scmap().highTexture->getVal(half).to4();
    };
    _mapMesh = Ahwassa::HeightFieldMeshGenerator::generate<unsigned short, Ahwassa::PositionColorNormalVertex>(*map->scmap().heightMapData, 0, std::numeric_limits<unsigned short>().max(), tinter, 2000, 1);
  }

  void World::update() {

  }

  void World::draw() {
    _mapRenderer->draw(*_mapMesh);
  }
}