#include "Spheres.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Renderer/SphereRenderer.h"
#include "AhwassaGraphicsLib/Renderer/Sphere.h"
#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "SuthanusPhysicsLib/Objects/Sphere.h"

namespace Superb {
  Spheres::Spheres(Ahwassa::Window* window, std::shared_ptr<Suthanus::PhysicEngine> physic) {
    _window = window;
    _physic = physic;
    _renderer = std::make_shared<Ahwassa::SphereRenderer>(window->camera());
  }

  void Spheres::addSphere(glm::vec3 position, float size, Iyathuum::Color clr) {
    _spheres.push_back(sphere());
    auto& s = _spheres[_spheres.size() - 1];
    s.graphic = _renderer->newSphere(position, size, clr);
    s.physic = _physic->newSphere(position, size, true);
  }

  void Spheres::draw() {
    _renderer->draw();
  }

  void Spheres::update() {
    for (size_t i = 0; i < _spheres.size(); i++)
      _spheres[i].graphic->setPosition(_spheres[i].physic->getPosition());
  }
}