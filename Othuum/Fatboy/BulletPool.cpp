#include "BulletPool.h"
#include "YolonaOss/Renderer/SphereRenderer.h"
#include "SuthanusPhysicsLib/Sphere.h"

namespace Fatboy
{
  void BulletPool::addBullet(std::shared_ptr<Suthanus::Sphere> obj)
  {
    _bullets.insert(obj);
  }

  void BulletPool::load(YolonaOss::GL::DrawSpecification* spec)
  {
    _spec = spec;
  }

  void BulletPool::draw()
  {
    YolonaOss::SphereRenderer::start();
    for (auto sphere : _bullets) {
      glm::mat4 transform = sphere->getTransformation();
      transform = glm::scale(transform, glm::vec3(sphere->getRadius(), sphere->getRadius(), sphere->getRadius()));
      YolonaOss::SphereRenderer::draw(transform, glm::vec4(1, 0.4, 1, 1));
    }
    YolonaOss::SphereRenderer::end();
  }
}