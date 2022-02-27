#include "BoxVisualization.h"

#include "AhwassaGraphicsLib/Renderer/BasicBoxRenderer.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "SuthanusPhysicsLib/Objects/Box.h"


namespace Athanah {
  BoxVisualization::BoxVisualization(std::shared_ptr<Suthanus::Box> target, Iyathuum::Color color, Ahwassa::Window* w) : Ahwassa::Drawable(w) {
    _target = target;
    _color  = color ;
    _box    = std::make_shared<Ahwassa::BasicBoxRenderer>(w->camera());
    _window = w;
  }

  void BoxVisualization::draw()
  {    
    _box->start();
    draw(_target, _color,_window);
    _box->end();
  }

  void BoxVisualization::draw(std::shared_ptr<Suthanus::Box> target, Iyathuum::Color color, Ahwassa::Window* w) {
    
    glm::mat4 transform = target->getTransformation();
    transform = glm::scale(transform, target->getSize());
    transform = glm::translate(transform, glm::vec3(-0.5, -0.5, -0.5));
    w->renderer().box().draw(transform, color);
  }

}