#pragma once

#include <memory>
#include <vector>
#include <IyathuumCoreLib/lib/glm/glm.hpp>
#include "IyathuumCoreLib/BaseTypes/Color.h"

namespace Ahwassa {
  class Window;
  class SphereRenderer;
  class Sphere;
}

namespace Suthanus {
  class PhysicEngine;
  class Sphere;
}

namespace Superb {
  class Spheres {
  public:
    Spheres(Ahwassa::Window*, std::shared_ptr<Suthanus::PhysicEngine> physic);

    void addSphere(glm::vec3 position, float size, Iyathuum::Color clr);
    void draw();
    void update();

  private:
    struct sphere {
      std::shared_ptr<Suthanus::Sphere> physic ;
      std::shared_ptr<Ahwassa::Sphere > graphic;
    };

    Ahwassa::Window*                         _window  ;
    std::shared_ptr<Suthanus::PhysicEngine>  _physic  ;
    std::vector<sphere>                      _spheres ;
    std::shared_ptr<Ahwassa::SphereRenderer> _renderer;
  };
}