#include "TankTower.h"
#include "YolonaOss/Renderer/BoxRenderer.h"

namespace Fatboy
{
  TankTower::TankTower(Suthanus::PhysicObject& attachTo, glm::vec3 offset)
    : _attachedTo(attachTo), _offset(offset)
  {
  }

  void TankTower::load(YolonaOss::GL::DrawSpecification*)
  {

  }

  void TankTower::update()
  {

  }

  void TankTower::draw()
  {
    YolonaOss::BoxRenderer::start();
    glm::vec4 offsetTransformed = _attachedTo.getTransformation()*glm::vec4(_offset, 1);
    glm::vec3 drawPos = glm::vec3(offsetTransformed.x, offsetTransformed.y, offsetTransformed.z);
    YolonaOss::BoxRenderer::drawDot(drawPos, glm::vec3(0.05f), glm::vec4(1, 1, 0, 1));
    YolonaOss::BoxRenderer::end();
  }
}