#include "Slider.h"

#include <sstream>
#include <iomanip>

#include "IyathuumCoreLib/Singleton/Database.h"
#include "Renderer/BasicRectangleRenderer.h"
#include "Renderer/BasicTextRenderer.h"
#include "Core/Window.h"
#include "Core/Renderer.h"
#include "Input/Input.h"

namespace Ahwassa {
  Slider::Slider(Window* w) : Drawable(w)
  {
  }

  Slider::Slider(Iyathuum::glmAABB<2> position, float min, float max, float startValue, std::function<void(float)> valueChangedCall, Window* w, UIElement* parent) : Drawable(w) {
    _valueChangedCall = valueChangedCall;
    _currentValue = startValue;
    _min = min;
    _max = max;
    setParent(parent);
    setLocalPosition(position);
    w->input().addUIElement(this);
  }

  Slider::~Slider()
  {
    getWindow()->input().removeUIElement(this);
    setVisible(false);
  }

  void Slider::draw()
  {
    if (!isVisible())
      return;
    getWindow()->renderer().rectangle().start();
    getWindow()->renderer().rectangle().drawRectangle(getGlobalPosition(), _hovered ? Iyathuum::Color(0.8f *255, 0.8f * 255, 0.8f * 255) : Iyathuum::Color(0.4f * 255, 0.4f * 255, 0.4f * 255));
    getWindow()->renderer().rectangle().drawRectangle(getBarLocation(), _hovered ? Iyathuum::Color(0.2f * 255, 0.2f * 255, 0.2f * 255) : Iyathuum::Color(0.0f * 255, 0.0f * 255, 0.0f * 255));
    getWindow()->renderer().rectangle().drawRectangle(getSliderLocation(), _hovered ? Iyathuum::Color(0.0f * 255, 0.8f * 255, 0.8f * 255) : Iyathuum::Color(0.0f * 255, 0.4f * 255, 0.4f * 255));

    getWindow()->renderer().rectangle().end();
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << _currentValue;
    std::string mystring = ss.str();
    glm::vec2 textSize = getWindow()->renderer().text().getTextSize(mystring, 1);
    glm::vec2 spacing = (getGlobalPosition().getSize() - textSize) / 2.0f;
    spacing[0] = 0;
    getWindow()->renderer().text().start();
    glm::vec2 pos = getGlobalPosition().getPosition() + spacing;

    getWindow()->renderer().text().drawText(mystring, pos, 1, Iyathuum::Color(0, 0, 0));
    getWindow()->renderer().text().end();
  }

  Iyathuum::glmAABB<2> Slider::getSliderLocation() {
    Iyathuum::glmAABB<2> result;
    Iyathuum::glmAABB<2> myPos = getGlobalPosition();
    float sliderW = myPos.getSize()[0] * sliderWidth;
    result.setPosition(myPos.getPosition() + glm::vec2( myPos.getSize()[0] * leftPad + (myPos.getSize()[0] * (1.0f - (leftPad + rightPad)) * (_currentValue - _min) / (_max - _min)), (1.0f - sliderHeight) * 0.5f * myPos.getSize()[1] ));
    result.setSize({ sliderW > minSliderWidth ? sliderW : minSliderWidth,myPos.getSize()[1] * sliderHeight });
    result.setPosition({ result.getPosition()[0] - sliderW * 0.5f,result.getPosition()[1] });
    return result;
  }

  Iyathuum::glmAABB<2> Slider::getBarLocation() {
    Iyathuum::glmAABB<2> result;
    Iyathuum::glmAABB<2> myPos = getGlobalPosition();
    float sliderW = myPos.getSize()[0] * sliderWidth;
    result.setPosition(myPos.getPosition() + glm::vec2(myPos.getSize()[0] * leftPad, (1.0f - barHeight) * 0.5f * myPos.getSize()[1] ));
    result.setSize({ myPos.getSize()[0] * (1.0f - (leftPad + rightPad)), barHeight * myPos.getSize()[1] });
    return result;
  }

  void Slider::mouseEnterEvent() {
    _hovered = true;
  };

  void Slider::mouseLeaveEvent() {
    _hovered = false;
  };

  bool Slider::mouseMoveEvent(const glm::vec2& current, const  glm::vec2& movement) {
    Iyathuum::glmAABB<2> myPos = getGlobalPosition();
    if (_pressed) {
      float min = leftPad * myPos.getSize()[0];
      float max = myPos.getSize()[0] - rightPad * myPos.getSize()[0];

      _currentValue = _min + ((current[0] - min) / (max - min)) * (_max - _min);
      if (_currentValue < _min) _currentValue = _min;
      if (_currentValue > _max) _currentValue = _max;
      _valueChangedCall(_currentValue);
    }
    return true;
  }

  bool Slider::mouseEvent(const glm::vec2& localPosition, const Iyathuum::Key& button, const Iyathuum::KeyStatus& status) {
    if (button == Iyathuum::Key::MOUSE_BUTTON_1 && isInside(getGlobalPosition().getPosition() + localPosition, Iyathuum::Key::MOUSE_BUTTON_1)) {
      if (status == Iyathuum::KeyStatus::PRESS && !_pressed) {
        Iyathuum::glmAABB<2> b = getSliderLocation();
        b.setPosition(b.getPosition() - getGlobalPosition().getPosition());
        if (b.isInside({ localPosition[0],localPosition[1] })) {
          _pressed = true;
          return true;
        }

      }
      if (status == Iyathuum::KeyStatus::RELEASE && _pressed) {
        _pressed = false;
        return true;
      }
    }

    Iyathuum::glmAABB<2> c = getLocalPosition();
    c.setPosition(c.getPosition() - getLocalPosition().getPosition());
    return isInside({ localPosition[0] ,localPosition[1] }, Iyathuum::Key::KEY_NONE);
  }

  void Slider::setValue(float value, bool emit) {
    _currentValue = value;
    if (emit)
      _valueChangedCall(value);
  }
}