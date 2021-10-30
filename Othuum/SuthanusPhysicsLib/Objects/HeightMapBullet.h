#pragma once

#include "HeightMap.h"
#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"

class btRigidBody;
class btDiscreteDynamicsWorld;
class btDefaultMotionState;

namespace Suthanus
{
  namespace Bullet
  {
    class HeightMapBullet : public HeightMap
    {
    public:
      HeightMapBullet(btDiscreteDynamicsWorld* world, glm::vec3 pos, glm::vec2 cellSize, const Iyathuum::MultiDimensionalArray<unsigned short, 2>&,float height);//, Iyathuum::MultiDimensionalArray<float,2> content);
      ~HeightMapBullet();
      virtual glm::vec3       getPosition()                 const override;
      virtual glm::mat4       getTransformation()           const override;
      virtual glm::quat       getRotation()                 const override;
      virtual void            setVelocity(glm::vec3)              override;
      virtual void            setPosition(glm::vec3)              override;
      virtual void            setAngularVelocity(glm::vec3)       override;
      virtual void            setRotation(glm::quat)              override;
      virtual HeightMap::Mesh getMesh()                           override;
    private:
      glm::vec2                                 _cellSize   ;
      //Iyathuum::MultiDimensionalArray<float, 2> _content    ;
      btDiscreteDynamicsWorld*                  _world      ;
      btRigidBody*                              _body       ;
      btDefaultMotionState*                     _motionState;
      std::vector<double>                       _fieldData;
    };
  }
}