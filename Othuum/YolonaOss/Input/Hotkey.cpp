#include "Hotkey.h"

#include "OpenGL/InputHandling.h"
#include "OpenGL/Window.h"

namespace YolonaOss {
  YolonaOss::Hotkey::Hotkey(Iyathuum::Key key, std::function<void()> onPress, std::function<void()> onRelease) {
    _key = key;
    _onPress = onPress;
    _onRelease = onRelease;
  }

  void YolonaOss::Hotkey::load(YolonaOss::GL::DrawSpecification* spec) {
    _spec = spec;
  }

  void YolonaOss::Hotkey::update() {
    if (GL::InputHandling::getInstance().getCurrentFocus() != nullptr)
      return;
    Iyathuum::KeyStatus status = _spec->getWindow()->getKeyStatus(_key);
    if (status == Iyathuum::KeyStatus::PRESS && _old != status)
      _onPress();
    else if (status == Iyathuum::KeyStatus::RELEASE && _old != status)
      _onRelease();
    else if (status == Iyathuum::KeyStatus::REPEAT)
      throw std::runtime_error("Unexpected behavior");
    _old = status;
  }
}