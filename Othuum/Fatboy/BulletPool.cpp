#include "BulletPool.h"
#include "Bullet.h"

namespace Fatboy
{
  void BulletPool::addBullet(std::shared_ptr<Bullet> obj)
  {
    _bullets.insert(obj);
    obj->load(_spec);
  }

  void BulletPool::load(YolonaOss::GL::DrawSpecification* spec)
  {
    _spec = spec;
  }

  void BulletPool::draw()
  {
    for (auto bullet : _bullets) {
      bullet->draw();
    }
  }
}