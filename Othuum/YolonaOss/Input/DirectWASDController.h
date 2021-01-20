#pragma once

#include "WASDInputable.h"
#include "../OpenGL/Updateable.h"

namespace YolonaOss
{
  class DirectWASDController : public GL::Updateable
  {
  public:
    DirectWASDController(WASDInputable&);
    virtual void load(YolonaOss::GL::DrawSpecification*) override;
    virtual void update()                                override;

  private:
    WASDInputable&                    _target;
    YolonaOss::GL::DrawSpecification* _spec   = nullptr;

    bool _oldStatusUp        = false;
    bool _oldStatusDown      = false;
    bool _oldStatusLeft      = false;
    bool _oldStatusRight     = false;
    bool _oldStatusSpecial   = false;
    bool _oldStatusInteract  = false;
    bool _oldStatusInventory = false;

  };
}