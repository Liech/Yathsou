#pragma once

#include <string>
#include <memory>
#include <vector>

namespace Athanah {
  class Map;
  class MapRenderer;
}
namespace Ahwassa {
  class Window;
  class IMesh;
}
namespace Suthanus {
  class PhysicEngine;
  class Box;
  class HeightMap;
  class PhysicObject;
}

namespace Superb {
  class World {
  public:
    World(Ahwassa::Window*,std::shared_ptr<Suthanus::PhysicEngine>,std::shared_ptr<Athanah::Map> mapFolder);

    void update();
    void draw();
  private:
    std::shared_ptr<Athanah::Map>           _map        ;
    std::shared_ptr<Athanah::MapRenderer>   _mapRenderer;
    std::shared_ptr<Ahwassa::IMesh>         _mapMesh    ;
    Ahwassa::Window*                        _window     ;
    std::shared_ptr<Suthanus::PhysicEngine> _physic     ;
    std::shared_ptr<Suthanus::HeightMap>    _obj        ;
  };
}