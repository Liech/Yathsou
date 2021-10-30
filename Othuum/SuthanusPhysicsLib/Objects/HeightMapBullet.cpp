#include "HeightMap.h"
#include "HeightMapBullet.h"
#include "SuthanusPhysicsLib/lib/bullet/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"
#include "SuthanusPhysicsLib/lib/bullet/btBulletDynamicsCommon.h"

namespace Suthanus
{
  namespace Bullet
  {
    HeightMapBullet::HeightMapBullet(btDiscreteDynamicsWorld* world,glm::vec3 pos, glm::vec2 cellSize, const Iyathuum::MultiDimensionalArray<unsigned short, 2>& content,float height)
      :_cellSize(cellSize)//, 
       //_content (content)
    {
      _world = world;
      
      size_t width  = content.getDimension(0);
      size_t length = content.getDimension(1);
      _fieldData.resize(width * length);

      for (size_t x = 0; x < width; x++)
        for (size_t y = 0; y < length; y++) {
          _fieldData[x + y * width] = height* ((double)content.getVal(x, y) / (double)std::numeric_limits<unsigned short>().max());
        }


      bool useFloatDatam = false;
      bool flipQuadEdges = false;
      int upIndex = 1;

      btHeightfieldTerrainShape* heightFieldShape = new btHeightfieldTerrainShape(width, length, _fieldData.data(), 1, 0, height, upIndex, PHY_ScalarType::PHY_DOUBLE, flipQuadEdges);

      btCollisionShape* colShape = heightFieldShape;
      heightFieldShape->setUseDiamondSubdivision(true);

      /// Create Dynamic Objects
      btTransform startTransform;
      startTransform.setIdentity();
      bool isDynamic = false;
      btScalar mass(1.f);
      if (!isDynamic)
        mass = 0;
      btVector3 localInertia(0, 0, 0);
      if (isDynamic)
        colShape->calculateLocalInertia(mass, localInertia);

      startTransform.setOrigin(btVector3(pos[0] + cellSize[0]  * ((float)width-1) / 2.0f, pos[1] + height/2.0f, pos[2] + cellSize[1] * ((float)length-1) / 2.0f));
      //startTransform.setOrigin(btVector3(pos[0], pos[1], pos[2]));
      _motionState = new btDefaultMotionState(startTransform);
      btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, _motionState, colShape, localInertia);

      _body = new btRigidBody(rbInfo);
      _body->setUserPointer(this);
      _world->addRigidBody(_body);
      _body->setCollisionFlags(_body->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
    }

    HeightMapBullet::~HeightMapBullet()
    {
      _world->removeRigidBody(_body);
      delete _motionState;
      delete _body;
    }

    glm::vec3 HeightMapBullet::getPosition() const
    {
      auto trans = _body->getWorldTransform().getOrigin();
      return glm::vec3(trans[0], trans[1], trans[2]);
    }

    glm::mat4 HeightMapBullet::getTransformation() const
    {
      glm::mat4 result;
      btTransform trans = _body->getWorldTransform();
      double mat[16];
      trans.getOpenGLMatrix(mat);
      return glm::make_mat4(mat);
    }

    glm::quat HeightMapBullet::getRotation() const
    {
      btTransform transform = _body->getCenterOfMassTransform();
      auto rot = transform.getRotation();
      return glm::quat(rot.x(), rot.y(), rot.z(), rot.w());
    }

    void HeightMapBullet::setVelocity(glm::vec3 pos)
    {
      _body->setLinearVelocity(btVector3(pos[0], pos[1], pos[2]));
    }

    void HeightMapBullet::setPosition(glm::vec3 pos)
    {
      btTransform transform = _body->getCenterOfMassTransform();
      transform.setOrigin(btVector3(pos[0], pos[1], pos[2]));
      _body->setCenterOfMassTransform(transform);
    }

    void HeightMapBullet::setAngularVelocity(glm::vec3 velocity)
    {
      _body->setAngularVelocity(btVector3(velocity[0], velocity[1], velocity[2]));
    }

    void HeightMapBullet::setRotation(glm::quat rot)
    {
      btTransform transform = _body->getCenterOfMassTransform();
      btQuaternion q;
      q.setX(rot.x);
      q.setY(rot.y);
      q.setZ(rot.z);
      q.setW(rot.w);
      transform.setRotation(btQuaternion());
      _body->setCenterOfMassTransform(transform);
    }

    HeightMap::Mesh HeightMapBullet::getMesh()
    {
      throw std::runtime_error("Not implemented yet");
      HeightMap::Mesh result;

      return result;
    }
  }
}