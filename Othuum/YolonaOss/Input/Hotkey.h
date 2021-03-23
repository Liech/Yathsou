#pragma once

#include "YolonaOss/OpenGL/Updateable.h"
#include "IyathuumCoreLib/BaseTypes/Keys.h"
#include <functional>

namespace YolonaOss
{
  class Hotkey : public YolonaOss::GL::Updateable
  {
  public:
    Hotkey(Iyathuum::Key key, std::function<void()> onPress, std::function<void()> onRelease = []() {});

    virtual void load(YolonaOss::GL::DrawSpecification*) override;
    virtual void update() override;

  private:
    std::function<void()>             _onPress  ;
    std::function<void()>             _onRelease;
    Iyathuum::Key                _key      ;
    YolonaOss::GL::DrawSpecification* _spec     ;
    Iyathuum::KeyStatus          _old      = Iyathuum::KeyStatus::RELEASE;
  };
}