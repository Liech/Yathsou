#pragma once

#include "YolonaOss/OpenGL/Drawable.h"
#include "YolonaOss/OpenGL/Updateable.h"
#include "IyathuumCoreLib/lib/glm/vec3.hpp"
#include "YolonaOss/Util/getPosition.h"

namespace Fatboy
{
  class Protagonist : public YolonaOss::GL::Drawable, public YolonaOss::GL::Updateable, public YolonaOss::GetPosition
  {
  public:
    Protagonist();

    virtual void load(YolonaOss::GL::DrawSpecification*) override;
    virtual void draw()                                  override;
    virtual void update()                                override;

    glm::vec3 getPosition();

  private:
    void handleInput();

    glm::vec3 _pos = glm::vec3(0,2,0);
    YolonaOss::GL::DrawSpecification* _spec;
  };
}