#pragma once

#include "HeightMap.h"
#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"

class btRigidBody;
class btDiscreteDynamicsWorld;
class btDefaultMotionState;

namespace Suthanus
{
  class PhysicEngine;

  namespace Bullet
  {
    class HeightMapBullet : public HeightMap
    {
    public:
      HeightMapBullet(PhysicEngine& engine, btDiscreteDynamicsWorld* world, glm::vec3 pos, glm::vec2 cellSize, const Iyathuum::MultiDimensionalArray<unsigned short, 2>&,float height);//, Iyathuum::MultiDimensionalArray<float,2> content);
      ~HeightMapBullet();
      virtual glm::vec3       getPosition()                 const   override;
      virtual glm::mat4       getTransformation()           const   override;
      virtual glm::quat       getRotation()                 const   override;
      virtual void            setVelocity       (const glm::vec3&)  override;
      virtual void            setPosition       (const glm::vec3&)  override;
      virtual void            setAngularVelocity(const glm::vec3&)  override;
      virtual void            setRotation       (const glm::quat&)  override;
      virtual void      addForce(const glm::vec3& force, const glm::vec3& offset) override;

      virtual HeightMap::Mesh getMesh()                           override;
    private:
      glm::vec2                                 _cellSize   ;
      btDiscreteDynamicsWorld*                  _world      ;
      btRigidBody*                              _body       ;
      btDefaultMotionState*                     _motionState;
      std::vector<double>                       _fieldData;
    };
  }
}