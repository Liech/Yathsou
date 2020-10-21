#include "HeightMap.h"
#include "HeightMapBullet.h"
#include "lib/bullet/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"
namespace Suthanus
{
  namespace Bullet
  {
    HeightMapBullet::HeightMapBullet(btDiscreteDynamicsWorld* world, glm::vec2 cellSize, Iyathuum::MultiDimensionalArray<float, 2> content)
      :_cellSize(cellSize), 
       _content (content)
    {
      _world = world;
      //btHeightfieldTerrainShape* collsion = new btHeightfieldTerrainShape();
    }

    glm::vec3 HeightMapBullet::getPosition() const
    {
      return glm::vec3();
    }

    glm::mat4 HeightMapBullet::getTransformation() const
    {
      return glm::mat4();
    }

    glm::quat HeightMapBullet::getRotation() const
    {
      return glm::quat();
    }

    void HeightMapBullet::setVelocity(glm::vec3)
    {
    }

    void HeightMapBullet::setPosition(glm::vec3)
    {
    }

    void HeightMapBullet::setAngularVelocity(glm::vec3)
    {
    }

    void HeightMapBullet::setRotation(glm::quat)
    {
    }
  }
}