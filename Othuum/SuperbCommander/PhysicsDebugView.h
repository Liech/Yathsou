#pragma once

#include <memory>
#include "IyathuumCoreLib/BaseTypes/Keys.h"

namespace Ahwassa {
  class Window;
}

namespace Suthanus {
  class PhysicEngine;
}

namespace Athanah {
  class BulletDebugDrawer;
}

namespace Superb {
  class PhysicsDebugView {
  public:
    PhysicsDebugView(std::shared_ptr<Suthanus::PhysicEngine>, Ahwassa::Window*, Iyathuum::Key = Iyathuum::Key::KEY_F1);

    void update();
    void draw();
  private:
    Ahwassa::Window*                            _window;
    std::shared_ptr<Athanah::BulletDebugDrawer> _debug;
    std::shared_ptr<Suthanus::PhysicEngine>     _physic;
    Iyathuum::Key                               _key;
    bool                                        _active = false;
    bool                                        _pressed = false;
  };
}