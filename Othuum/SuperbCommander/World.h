#pragma once

#include <string>
#include <memory>

namespace Athanah {
  class Map;
  class MapRenderer;
}

namespace Ahwassa {
  class Window;
  class IMesh;
}

namespace Superb {
  class World {
  public:
    World(Ahwassa::Window*,std::shared_ptr<Athanah::Map> mapFolder);

    void update();
    void draw();
  private:
    std::shared_ptr<Athanah::Map>         _map        ;
    std::shared_ptr<Athanah::MapRenderer> _mapRenderer;
    std::shared_ptr<Ahwassa::IMesh>       _mapMesh    ;
    Ahwassa::Window*                      _window     ;
  };
}