#pragma once

#include <memory>

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

    std::shared_ptr<Suthanus::PhysicEngine> physic();
  private:
    std::shared_ptr<Suthanus::PhysicEngine> _physic;

    bool _freezePhysic = false;
  };
}