#pragma once

#include "YolonaOss/OpenGL/Drawable.h"
#include "YolonaOss/OpenGL/Updateable.h"
#include "IyathuumCoreLib/lib/glm/vec3.hpp"
#include "YolonaOss/Util/getPosition.h"

namespace Suthanus
{
  class PhysicTest;
  class Vehicle;
}

namespace Fatboy
{
  class Protagonist : public YolonaOss::GL::Drawable, public YolonaOss::GL::Updateable, public YolonaOss::GetPosition
  {
  public:
    Protagonist(std::shared_ptr<Suthanus::PhysicTest>);

    virtual void load(YolonaOss::GL::DrawSpecification*) override;
    virtual void draw()                                  override;
    virtual void update()                                override;

    glm::vec3 getPosition();

  private:
    glm::vec3 getStartPos() { return glm::vec3(0, 2, 0); }
    void handleInput();

    YolonaOss::GL::DrawSpecification* _spec;
    std::shared_ptr<Suthanus::PhysicTest> _physic;
    std::shared_ptr<Suthanus::Vehicle> _physBody;
  };
}