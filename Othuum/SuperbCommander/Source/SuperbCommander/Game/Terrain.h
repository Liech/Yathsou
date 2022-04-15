#pragma once

#include <memory>
#include <nlohmann/json.hpp>

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
      void save(nlohmann::json&);
      void load(nlohmann::json&);
      void start();

      World& world();
    private:
      Physic&   _physic;
      Database& _database;

      std::unique_ptr<World> _world;

      std::string _mapPath = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Supreme Commander Forged Alliance\\maps\\SCMP_009";
  };
}