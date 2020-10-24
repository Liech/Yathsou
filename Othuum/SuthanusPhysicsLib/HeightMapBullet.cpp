#include "HeightMap.h"
#include "HeightMapBullet.h"
#include "lib/bullet/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"
#include "lib/bullet/btBulletDynamicsCommon.h"

namespace Suthanus
{
  namespace Bullet
  {
    HeightMapBullet::HeightMapBullet(btDiscreteDynamicsWorld* world,glm::vec3 pos, glm::vec2 cellSize)//, Iyathuum::MultiDimensionalArray<float, 2> content)
      :_cellSize(cellSize)//, 
       //_content (content)
    {
      _world = world;

      int width  = 10;
      int length = 10;
      float* heightfieldData = new float[width * length];
      {
        for (int i = 0; i < width * length; i++)
        {
          heightfieldData[i] = 0;
        }
      }
      heightfieldData[3] = 0;
      heightfieldData[4] = 0.1;
      heightfieldData[5] = 1;
      heightfieldData[6] = 10;
      //const char* filename = "heightfield128x128.raw";
      //FILE* heightfieldFile = fopen(filename, "r");
      //if (!heightfieldFile)
      //{
      //  filename = "heightfield128x128.raw";
      //  heightfieldFile = fopen(filename, "r");
      //}
      //if (heightfieldFile)
      //{
      //  int numBytes = fread(heightfieldData, 1, width * length, heightfieldFile);
      //  //btAssert(numBytes);
      //  if (!numBytes)
      //  {
      //    printf("couldn't read heightfield at %s\n", filename);
      //  }
      //  fclose(heightfieldFile);
      //}

      bool useFloatDatam = false;
      bool flipQuadEdges = false;
      int upIndex = 1;

      //btHeightfieldTerrainShape * heightFieldShape = new btHeightfieldTerrainShape(width, length, heightfieldData, maxHeight, upIndex, useFloatDatam, flipQuadEdges);
      btHeightfieldTerrainShape* heightFieldShape = new btHeightfieldTerrainShape(width, length, heightfieldData, 1,0,1,upIndex,PHY_ScalarType::PHY_FLOAT, flipQuadEdges);
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

      startTransform.setOrigin(btVector3(pos[0], pos[1], pos[2]));
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
      float mat[16];
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
  }
}