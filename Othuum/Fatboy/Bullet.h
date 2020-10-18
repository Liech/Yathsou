#pragma once

#include <memory>
#include "YolonaOss/OpenGL/Drawable.h"
#include "IyathuumCoreLib/lib/glm/vec3.hpp"

namespace Suthanus
{
  class Sphere;
}

namespace Fatboy
{
  class Context;

  class Bullet : public YolonaOss::GL::Drawable
  {
  public:
    Bullet(std::shared_ptr<Context>, glm::vec3 position, glm::vec3 velocity);
    virtual void load(YolonaOss::GL::DrawSpecification*) override;
    virtual void draw() override;
  private:
    std::shared_ptr<Suthanus::Sphere> _physicObject;
    std::shared_ptr<Context>          _context     ;

  };
}