#pragma once

#include <memory>
#include <vector>
#include <set>

#include "YolonaOss/OpenGL/Drawable.h"
#include "YolonaOss/OpenGL/Updateable.h"
#include "IyathuumCoreLib/lib/glm/vec3.hpp"
#include "YolonaOss/Util/getPosition.h"

namespace Suthanus
{
  class PhysicEngine;
  class Vehicle;
  class Sphere;
}

namespace Fatboy
{
  class TankTower;

  class Protagonist : public YolonaOss::GL::Drawable, public YolonaOss::GL::Updateable, public YolonaOss::GetPosition
  {
  public:
    Protagonist(std::shared_ptr<Suthanus::PhysicEngine>);

    virtual void load(YolonaOss::GL::DrawSpecification*) override;
    virtual void draw()                                  override;
    virtual void update()                                override;

    glm::vec3 getPosition();

  private:
    glm::vec3 getStartPos() { return glm::vec3(0, 2, 0); }
    void handleInput();
    void handlePicking();

    YolonaOss::GL::DrawSpecification*           _spec    ;
    std::shared_ptr<Suthanus::PhysicEngine>     _physic  ;
    std::shared_ptr<Suthanus::Vehicle>          _physBody;
    std::set<std::shared_ptr<Suthanus::Sphere>> _bullets ;
    std::shared_ptr<TankTower>                  _tower   ;
    glm::vec3 _lastPickedPosition;

    const float firePower = 10;

    bool _pressed = false;
  };
}