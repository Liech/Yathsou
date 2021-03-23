#include "Slider.h"

#include <sstream>
#include "glad/glad.h"
#include "../../Renderer/RectangleRenderer.h"
#include "../../Renderer/TextRenderer.h"
#include "IyathuumCoreLib/Singleton/Database.h"
#include "IyathuumCoreLib/Util/Geometry.h"
#include "Util/Util.h"

namespace YolonaOss {
  namespace Widgets {
    Slider::Slider() : Widget()
    {
    }
    Slider::Slider(Iyathuum::AABB<2> position, double min, double max, double startValue, std::function<void(double)> valueChangedCall) : Widget(position) {
      _valueChangedCall = valueChangedCall;
      _currentValue = startValue;
      _min = min;
      _max = max;
      setVisible(true);
    }

    Slider::~Slider()
    {
      setVisible(false);
    }

    void Slider::load(GL::DrawSpecification*)
    {

    }

    void Slider::draw()
    {
      if (!isVisible())
        return;
      RectangleRenderer::start();
      RectangleRenderer::drawRectangle(getPosition(), _hovered ? glm::vec3(0.8f, 0.8f, 0.8f) : glm::vec3(0.4f, 0.4f, 0.4f));
      RectangleRenderer::drawRectangle(getBarLocation(), _hovered ? glm::vec3(0.2f, 0.2f, 0.2f) : glm::vec3(0.0f, 0.0f, 0.0f));
      RectangleRenderer::drawRectangle(getSliderLocation(), _hovered ? glm::vec3(0.0f, 0.8f, 0.8f) : glm::vec3(0.0f, 0.4f, 0.4f));

      RectangleRenderer::end();
      std::stringstream ss;
      ss << std::fixed << std::setprecision(1) << _currentValue;
      std::string mystring = ss.str();
      glm::vec2 textSize = TextRenderer::getTextSize(mystring, 1);
      glm::vec2 spacing = (Util<2>::array2Vec(getPosition().getSize()) - textSize) / 2.0f;
      spacing[0] = 0;
      TextRenderer::start();
      glm::vec2 pos = Util<2>::array2Vec(getPosition().getPosition()) + spacing;

      TextRenderer::drawText(mystring, pos, 1, glm::vec3(0, 0, 0));
      TextRenderer::end();
    }

    Iyathuum::AABB<2> Slider::getSliderLocation() {
      Iyathuum::AABB<2> result;
      Iyathuum::AABB<2> myPos = getPosition();
      float sliderW = myPos.getSize()[0] * sliderWidth;
      result.setPosition(Iyathuum::Geometry<2>::add(myPos.getPosition() , {myPos.getSize()[0] * leftPad + (myPos.getSize()[0] * (1.0f - (leftPad + rightPad)) * (_currentValue - _min) / (_max - _min)), (1.0f - sliderHeight) * 0.5f * myPos.getSize()[1]}));
      result.setSize({ sliderW > minSliderWidth ? sliderW : minSliderWidth,myPos.getSize()[1] * sliderHeight });
      result.setPosition({ result.getPosition()[0] - sliderW * 0.5f,result.getPosition()[1] });
      return result;
    }

    Iyathuum::AABB<2> Slider::getBarLocation() {
      Iyathuum::AABB<2> result;
      Iyathuum::AABB<2> myPos = getPosition();
      float sliderW = myPos.getSize()[0] * sliderWidth;
      result.setPosition(Iyathuum::Geometry<2>::add(myPos.getPosition() , {myPos.getSize()[0] * leftPad, (1.0f - barHeight) * 0.5f * myPos.getSize()[1]}));
      result.setSize({ myPos.getSize()[0] * (1.0f - (leftPad + rightPad)), barHeight * myPos.getSize()[1] });
      return result;
    }

    void Slider::mouseEnter() {
      _hovered = true;
    };

    void Slider::mouseLeave() {
      _hovered = false;
    };

    void Slider::mouseMove(glm::vec2 position) {
      Iyathuum::AABB<2> myPos = getPosition();
      if (_pressed) {
        float min = leftPad * myPos.getSize()[0];
        float max = myPos.getSize()[0] - rightPad * myPos.getSize()[0];

        _currentValue = _min + ((position[0] - min) / (max-min)) * (_max - _min);
        if (_currentValue < _min) _currentValue = _min;
        if (_currentValue > _max) _currentValue = _max;
        _valueChangedCall(_currentValue);
      }
    }

    bool Slider::mouseStatusChanged(glm::vec2 position, Iyathuum::Key k, Iyathuum::KeyStatus status) {
      if (k == Iyathuum::Key::MOUSE_BUTTON_1) {
        if (status == Iyathuum::KeyStatus::PRESS && !_pressed) {
          Iyathuum::AABB<2> b = getSliderLocation();
          b.setPosition( Iyathuum::Geometry<2>::subtract(b.getPosition() , getPosition().getPosition()));
          if (b.isInside({ position[0],position[1] })) {
            _pressed = true;
            return true;
          }

        }
        if (status == Iyathuum::KeyStatus::RELEASE && _pressed) {
          _pressed = false;
          return true;
        }
      }

      Iyathuum::AABB<2> c = getPosition();
      c.setPosition(Iyathuum::Geometry<2>::subtract(c.getPosition(),getPosition().getPosition()));
      return c.isInside({ position[0] ,position[1]});
    }

    void Slider::setValue(double value, bool emit) { 
      _currentValue = value;
      if (emit)
        _valueChangedCall(value);
    }

    void Slider::setVisible(bool visible) {      
      if (visible && !isVisible())
        Iyathuum::Database<Widgets::Widget*>::add(this, { "MouseMove","MouseStatus" });
      else if (!visible && isVisible())
        Iyathuum::Database<Widgets::Widget*>::remove(this);
      Widget::setVisible(visible);
    }

  }
}