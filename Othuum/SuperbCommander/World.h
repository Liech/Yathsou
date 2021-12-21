#pragma once

#include <string>
#include <memory>
#include <vector>

namespace Athanah {
  class Map;
  class NavigationMeshDebugDrawer;
  class Gamedata;
}
namespace Ahwassa {
  class Window;
  class IMesh;
}
namespace Suthanus {
  class PhysicEngine;
  class PhysicNavigationMesh;
  class Box;
  class HeightMap;
  class PhysicObject;
}

namespace Superb {
  class World {
  public:
    World(Ahwassa::Window*,std::shared_ptr<Suthanus::PhysicEngine>,std::shared_ptr<Athanah::Map> mapFolder, Athanah::Gamedata&);

    std::shared_ptr<Suthanus::PhysicNavigationMesh> navMesh();

    void update();
    void draw();
    void debugDraw();
  private:
    Ahwassa::Window* _window;

    std::shared_ptr<Athanah::Map>                       _map        ;
    std::shared_ptr<Ahwassa::IMesh>                     _mapMesh    ;
    std::shared_ptr<Suthanus::PhysicEngine>             _physic     ;
    std::shared_ptr<Suthanus::HeightMap>                _obj        ;
    std::shared_ptr<Suthanus::PhysicNavigationMesh>     _navGraph   ;
    std::shared_ptr<Athanah::NavigationMeshDebugDrawer> _navGraphVis;
  };
}