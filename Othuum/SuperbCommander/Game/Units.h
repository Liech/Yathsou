#pragma once

#include <memory>
#include "AezeselFileIOLib/lib/json.hpp"

namespace Superb {
  class UnitsOld;
  class Physic;
  class Database;

  class Units {
  public:
    Units(Physic&, Database&);
    virtual ~Units() = default;

    void update();
    void save(nlohmann::json&);
    void load(nlohmann::json&);
    void start();

    UnitsOld& units();

  private:
    Physic&   _physic;
    Database& _database;
    std::unique_ptr<UnitsOld> _units;
  };
}