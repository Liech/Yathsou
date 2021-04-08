#include "ClientVisualization.h"

#include "UyanahGameServer/Client.h"
#include "UyanahGameServer/Component.h"
#include "UyanahGameServer/Entity.h"
#include "UyanahGameServer/Components/Dot.h"
#include "UyanahGameServer/Components/Transform2D.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicRectangleRenderer.h"

ClientVisualization::ClientVisualization(std::shared_ptr<Uyanah::Scene>& scene, Ahwassa::Window* w)
: _scene(scene), Drawable(w){
  
}

void ClientVisualization::draw() {  
  getWindow()->renderer().rectangle().start();
  bool end = false;
  if (_scene)
  for (auto ent : _scene->objects) {
    auto comp = ent.getComponent("Transform2D");
    if (comp) {
      std::shared_ptr<Uyanah::Components::Transform2D> t = std::dynamic_pointer_cast<Uyanah::Components::Transform2D>(comp);
      getWindow()->renderer().rectangle().drawRectangle(t->position-glm::vec2(5,5),glm::vec2(10,10),Iyathuum::Color(255,0,0));
      end = true;
      break;
    }
  }
  getWindow()->renderer().rectangle().end();
}