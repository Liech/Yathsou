#pragma once

#include <memory>
#include <set>
#include "YolonaOss/OpenGL/Drawable.h"
#include "YolonaOss/OpenGL/Updateable.h"
#include "YolonaOss/Util/getPosition.h"
namespace Suthanus
{
  class Vehicle;
  class PhysicObject;
}

namespace Fatboy
{
  class TankTower;
  class Context;

  class Tank : public YolonaOss::GL::Drawable, public YolonaOss::GL::Updateable, public YolonaOss::GetPosition
  {
  public:
    Tank(std::shared_ptr<Context>);
    virtual void load(YolonaOss::GL::DrawSpecification*) override;
    virtual void draw()                                  override;
    virtual void update()                                override;

    void fire();
    void setAcceleration(float value);
    void setSteering(float value);
    void setTarget(glm::vec3 pos);

    float maxAcceleration();
    float maxSteering();

    glm::vec3 getPosition();

  private:
    std::shared_ptr<Suthanus::Vehicle> _physBody ;
    std::shared_ptr<TankTower>         _tower    ;
    YolonaOss::GL::DrawSpecification*  _spec     ;
    std::shared_ptr<Context>           _context  ;
    glm::vec3                          _aimTarget;

    const float _firePower = 10.0f;
  };
}