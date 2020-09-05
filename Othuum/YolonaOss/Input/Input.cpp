#include "Input.h"
#include "YolonaOss/Lib/gainput/gainput.h"

namespace YolonaOss
{
  Input::Input()
  {

  }

  bool Input::isButtonDown(Button b)
  {
    return _map->GetBoolWasDown(b);
  }

  void Input::load(GL::DrawSpecification* spec)
  {
    _manager = std::make_shared<gainput::InputManager>();
    _manager->SetDisplaySize(spec->width, spec->height);
    const gainput::DeviceId keyboardId = _manager->CreateDevice<gainput::InputDeviceKeyboard>();
    const gainput::DeviceId mouseId    = _manager->CreateDevice<gainput::InputDeviceMouse>();

    _map = std::make_shared<gainput::InputMap>(*_manager);
    _map->MapBool(ButtonConfirm, keyboardId, gainput::KeyReturn      );
    _map->MapBool(ButtonConfirm, mouseId   , gainput::MouseButtonLeft);
  }

  void Input::update()
  {
    _manager->Update();
  }
}