#include "ClientVisualization.h"

#include "glad/glad.h"
#include "UyanahGameServer/Client.h"
#include "UyanahGameServer/Scene.h"
#include "UyanahGameServer/Component.h"
#include "UyanahGameServer/Entity.h"
#include "UyanahGameServer/Components/Dot.h"
#include "UyanahGameServer/Components/Transform2D.h"
#include "YolonaOss/Renderer/RectangleRenderer.h"

void ClientVisualization::setClient(std::unique_ptr<Uyanah::Client> client) {
  _client = std::move(client);
}

void ClientVisualization::load(YolonaOss::GL::DrawSpecification*) {

}

void ClientVisualization::draw() {
  if (_client)
    _client->update();
  YolonaOss::RectangleRenderer::start();
  if (_client)
  for (auto ent : _client->getScene().objects) {
    for (auto comp : ent.components) {
      if (comp->ComponentName() == "Transform2D") {
        std::shared_ptr<Uyanah::Components::Transform2D> t = std::dynamic_pointer_cast<Uyanah::Components::Transform2D>(comp);
        YolonaOss::RectangleRenderer::drawRectangle(t->position-glm::vec2(5,5),glm::vec2(10,10),glm::vec3(1,0,0));
      }
    }
  }
  YolonaOss::RectangleRenderer::end();
}