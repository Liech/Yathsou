#include "World.h"


#include "AthanahCommonLib/Map/Map.h"
#include "AthanahCommonLib/Physic/NavigationMeshDebugDrawer.h"
#include "AthanahCommonLib/SupCom/Gamedata/Gamedata.h"

#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AhwassaGraphicsLib/BufferObjects/IMesh.h"

#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "SuthanusPhysicsLib/Objects/HeightMap.h"
#include "SuthanusPhysicsLib/PhysicNavigationMesh.h"

namespace Superb {
  World::World(std::shared_ptr<Suthanus::PhysicEngine> physic,std::shared_ptr<Athanah::Map> map, Athanah::Gamedata& gamedata) {
    _map    = map   ;
    _physic = physic;
    map->loadFull();
    _obj = _physic->newHeightMap(glm::vec3(0, 0, 0), *map->scmap().heightMapData,2000);
    _navGraph = std::make_shared<Suthanus::PhysicNavigationMesh>(*physic,_map->aabb(), glm::vec3(30, 30, 30), 1);
    //_navGraphVis = std::make_shared<Athanah::NavigationMeshDebugDrawer>(*_navGraph,window->camera());
  }

  void World::update() {
  }

  //void World::debugDraw() {
  //  //_navGraphVis->draw();
  //}

  std::shared_ptr<Suthanus::PhysicNavigationMesh> World::navMesh() {
    return _navGraph;
  }

  Athanah::Map& World::map() {
    return *_map;
  }

}