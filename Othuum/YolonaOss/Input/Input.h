#pragma once

#include <memory>
#include "YolonaOss/OpenGL/Loadable.h"
#include "YolonaOss/OpenGL/Updateable.h"
namespace gainput
{
  class InputManager;
  class InputMap;
}

namespace YolonaOss
{
  enum Button
  {
    ButtonConfirm
  };

  class Input : public GL::Loadable, public GL::Updateable
  {
  public:
    Input();

    bool isButtonDown(Button b);

    virtual void update() override;
    void load(GL::DrawSpecification*) override;
  private:
    std::shared_ptr<gainput::InputManager> _manager;
    std::shared_ptr<gainput::InputMap>     _map    ;
  };
}