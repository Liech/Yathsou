#pragma once

#include <memory>

namespace Superb {
  class World;
  class Physic;
  class Database;
  
  class Terrain {
    public:
      Terrain(Physic&, Database&);
      virtual ~Terrain() = default;

      void menu();
      void update();

      World& world();
    private:
      std::unique_ptr<World> _world;

  };
}