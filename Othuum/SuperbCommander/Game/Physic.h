#pragma once

#include <memory>
#include "AezeselFileIOLib/lib/json.hpp"

namespace Suthanus {
  class PhysicEngine;
}

namespace Superb {
  class Physic {
  public:
    Physic();
    virtual ~Physic() = default;

    void menu();
    void update();
    void save(nlohmann::json&);
    void load(nlohmann::json&);
    void start();

    std::shared_ptr<Suthanus::PhysicEngine> physic();
  private:
    std::shared_ptr<Suthanus::PhysicEngine> _physic;

    bool _freezePhysic = false;
  };
}