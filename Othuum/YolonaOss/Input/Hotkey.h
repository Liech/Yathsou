#pragma once

#include "YolonaOss/OpenGL/Updateable.h"
#include "YolonaOss/OpenGL/Keys.h"
#include <functional>

namespace YolonaOss
{
  class Hotkey : public YolonaOss::GL::Updateable
  {
  public:
    Hotkey(YolonaOss::GL::Key key, std::function<void()> onPress, std::function<void()> onRelease = []() {});

    virtual void load(YolonaOss::GL::DrawSpecification*) override;
    virtual void update() override;

  private:
    std::function<void()>             _onPress  ;
    std::function<void()>             _onRelease;
    YolonaOss::GL::Key                _key      ;
    YolonaOss::GL::DrawSpecification* _spec     ;
    YolonaOss::GL::KeyStatus          _old      = YolonaOss::GL::KeyStatus::RELEASE;
  };
}