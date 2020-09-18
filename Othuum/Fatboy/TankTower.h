#pragma once

#include <memory>

#include "YolonaOss/OpenGL/Drawable.h"
#include "YolonaOss/OpenGL/Updateable.h"
#include "IyathuumCoreLib/lib/glm/vec3.hpp"
#include "SuthanusPhysicsLib/PhysicObject.h"

namespace Fatboy
{
  class TankTower : public YolonaOss::GL::Drawable, public YolonaOss::GL::Updateable
  {
  public:
    TankTower(Suthanus::PhysicObject& attachTo, glm::vec3 offset);

    virtual void load(YolonaOss::GL::DrawSpecification*) override;
    virtual void draw()                                  override;
    virtual void update()                                override;
  private:
    glm::vec3               _offset    ;
    Suthanus::PhysicObject& _attachedTo;
  };
}