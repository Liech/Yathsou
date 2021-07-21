#include "BoxVisualization.h"

#include "AhwassaGraphicsLib/BasicRenderer/BasicBoxRenderer.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "SuthanusPhysicsLib/Box.h"


namespace Athanah {
  BoxVisualization::BoxVisualization(std::shared_ptr<Suthanus::Box> target, Iyathuum::Color color, Ahwassa::Window* w) : Ahwassa::Drawable(w) {
    _target = target;
    _color  = color ;
    _box = std::make_shared<Ahwassa::BasicBoxRenderer>(w->camera());
  }

  void BoxVisualization::draw()
  {    
    _box->start();
    glm::mat4 transform = _target->getTransformation();
    transform = glm::scale      (transform, _target->getSize());
    transform = glm::translate  (transform, glm::vec3(-0.5, -0.5, -0.5));
    _box->draw(transform, _color);
    _box->end();
  }
}