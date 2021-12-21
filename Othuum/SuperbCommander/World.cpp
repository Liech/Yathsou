#include "World.h"


#include "AthanahCommonLib/Map/Map.h"
#include "AthanahCommonLib/Physic/NavigationMeshDebugDrawer.h"
#include "AthanahCommonLib/SupCom/Gamedata/Gamedata.h"

#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Vertex/PositionColorNormalVertex.h"
#include "AhwassaGraphicsLib/BufferObjects/IMesh.h"
#include "AhwassaGraphicsLib/Geometry/HeightFieldMeshGenerator.h"

#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "SuthanusPhysicsLib/Objects/HeightMap.h"
#include "SuthanusPhysicsLib/PhysicNavigationMesh.h"

namespace Superb {
  World::World(Ahwassa::Window* window, std::shared_ptr<Suthanus::PhysicEngine> physic,std::shared_ptr<Athanah::Map> map, Athanah::Gamedata& gamedata) {
    _map    = map   ;
    _window = window;
    _physic = physic;
    map->loadFull();

    std::array<std::string,5> textures;
    for (int i = 0; i < 5; i++) {
      textures[i] = map->scmap().terrainTexturePaths[i].path;
    }

    _obj = _physic->newHeightMap(glm::vec3(0, 0, 0), *map->scmap().heightMapData,2000);


    auto tinter = [&](const std::array<size_t, 2> position, Ahwassa::PositionColorNormalVertex& v) {
      std::array<size_t, 2> half = { position[0] / 2,position[1] / 2 };
      if (position[0] == map->scmap().heightMapData->getDimension(0) - 1) half[0] = (position[0] - 1) / 2;
      if (position[1] == map->scmap().heightMapData->getDimension(1) - 1) half[1] = (position[1] - 1) / 2;
      v.color = map->scmap().highTexture->getVal(half).to4();
    };
    _mapMesh = Ahwassa::HeightFieldMeshGenerator::generate<unsigned short, Ahwassa::PositionColorNormalVertex>(*map->scmap().heightMapData, 0, std::numeric_limits<unsigned short>().max(), tinter, 2000, 1);

    _navGraph = std::make_shared<Suthanus::PhysicNavigationMesh>(*physic,_map->aabb(), glm::vec3(30, 30, 30), 1);
    _navGraphVis = std::make_shared<Athanah::NavigationMeshDebugDrawer>(*_navGraph,window->camera());
  }

  void World::update() {
  }

  void World::draw() {
  }

  void World::debugDraw() {
    //_navGraphVis->draw();
  }

  std::shared_ptr<Suthanus::PhysicNavigationMesh> World::navMesh() {
    return _navGraph;
  }
}