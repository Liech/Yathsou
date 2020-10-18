#include "Bullet.h"

#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "SuthanusPhysicsLib/Sphere.h"
#include "YolonaOss/Renderer/SphereRenderer.h"
#include "Context.h"

namespace Fatboy
{
  Bullet::Bullet(std::shared_ptr<Context> context, glm::vec3 position, glm::vec3 velocity)
  {
    _context = context;

    _physicObject = _context->physic()->newSphere(position, 0.1f, true);
    _physicObject->setVelocity(velocity);
    std::weak_ptr<Suthanus::Sphere> b = _physicObject;
    _physicObject->setCollisionCallback([this, b](std::weak_ptr < Suthanus::PhysicObject > other)
      {
        if (std::shared_ptr<Suthanus::Sphere> lock = b.lock())
        {
          std::shared_ptr<Suthanus::PhysicObject> lOther = other.lock();
          //if (!std::dynamic_pointer_cast<Suthanus::Sphere>(lOther))
          //  _bullets.erase(lock);
        }
      });

  }
  
  void Bullet::load(YolonaOss::GL::DrawSpecification* spec)
  {
  }

  void Bullet::draw()
  {
    YolonaOss::SphereRenderer::start();
    glm::mat4 transform = _physicObject->getTransformation();
    transform = glm::scale(transform, glm::vec3(_physicObject->getRadius(), _physicObject->getRadius(), _physicObject->getRadius()));
    YolonaOss::SphereRenderer::draw(transform, glm::vec4(1, 0.4, 1, 1));
    YolonaOss::SphereRenderer::end();
  }
}