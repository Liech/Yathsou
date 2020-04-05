#include "Slider.h"

#include <sstream>
#include "glad/glad.h"
#include "../../Renderer/RectangleRenderer.h"
#include "../../Renderer/TextRenderer.h"
#include "structs/Database.h"

namespace YolonaOss {
  namespace Widgets {
    Slider::Slider() : Widget()
    {
    }
    Slider::Slider(BoundingBox2 position, double min, double max, double startValue, std::function<void(double)> valueChangedCall) : Widget(position) {
      _valueChangedCall = valueChangedCall;
      _currentValue = startValue;
      _min = min;
      _max = max;
      Database<Widgets::Widget*>::add(this, { "MouseMove","MouseStatus" });
    }

    Slider::~Slider()
    {
      Database<Widgets::Widget*>::remove(this);
    }

    void Slider::load(GL::DrawSpecification*)
    {

    }

    void Slider::draw()
    {
      RectangleRenderer::start();
      RectangleRenderer::drawRectangle(getPosition(), _hovered ? glm::vec3(0.8f, 0.8f, 0.8f) : glm::vec3(0.4f, 0.4f, 0.4f));
      RectangleRenderer::drawRectangle(getBarLocation(), _hovered ? glm::vec3(0.2f, 0.2f, 0.2f) : glm::vec3(0.0f, 0.0f, 0.0f));
      RectangleRenderer::drawRectangle(getSliderLocation(), _hovered ? glm::vec3(0.0f, 0.8f, 0.8f) : glm::vec3(0.0f, 0.4f, 0.4f));

      RectangleRenderer::end();
      std::stringstream ss;
      ss << std::fixed << std::setprecision(1) << _currentValue;
      std::string mystring = ss.str();
      glm::vec2 textSize = TextRenderer::getTextSize(mystring, 1);
      glm::vec2 spacing = (getPosition().size - textSize) / 2.0f;
      spacing[0] = 0;
      TextRenderer::start();
      glm::vec2 pos = getPosition().position + spacing;

      TextRenderer::drawText(mystring, pos, 1, glm::vec3(0, 0, 0));
      TextRenderer::end();
    }

    BoundingBox2 Slider::getSliderLocation() {
      BoundingBox2 result;
      BoundingBox2 myPos = getPosition();
      float sliderW = myPos.size[0] * sliderWidth;
      result.position = myPos.position + glm::vec2(myPos.size[0] * leftPad + (myPos.size[0] * (1.0f - (leftPad + rightPad)) * (_currentValue-_min) / (_max-_min)) ,(1.0f - sliderHeight)* 0.5f * myPos.size[1]);
      result.size     = glm::vec2(sliderW > minSliderWidth?sliderW:minSliderWidth,myPos.size[1] * sliderHeight);
      result.position[0] -= sliderW * 0.5f;
      return result;
    }

    BoundingBox2 Slider::getBarLocation() {
      BoundingBox2 result;
      BoundingBox2 myPos = getPosition();
      float sliderW = myPos.size[0] * sliderWidth;
      result.position = myPos.position + glm::vec2(myPos.size[0] * leftPad , (1.0f - barHeight) * 0.5f * myPos.size[1]);
      result.size = glm::vec2(myPos.size[0] * (1.0f - (leftPad + rightPad)), barHeight * myPos.size[1]);
      return result;
    }

    void Slider::mouseEnter() {
      _hovered = true;
    };

    void Slider::mouseLeave() {
      _hovered = false;
    };

    void Slider::mouseMove(glm::vec2 position) {
      BoundingBox2 myPos = getPosition();
      if (_pressed) {
        float min = leftPad * myPos.size[0];
        float max = myPos.size[0] - rightPad * myPos.size[0];

        _currentValue = _min + ((position[0] - min) / (max-min)) * (_max - _min);
        if (_currentValue < _min) _currentValue = _min;
        if (_currentValue > _max) _currentValue = _max;
        _valueChangedCall(_currentValue);
      }
    }

    bool Slider::mouseStatusChanged(glm::vec2 position, GL::Key k, GL::KeyStatus status) {
      if (k == GL::Key::MOUSE_BUTTON_1) {
        if (status == GL::KeyStatus::PRESS && !_pressed) {
          BoundingBox2 b = getSliderLocation();
          b.position -= getPosition().position;
          if (b.inside(position)) {
            _pressed = true;
            return true;
          }

        }
        if (status == GL::KeyStatus::RELEASE && _pressed) {
          _pressed = false;
          return true;
        }
      }

      BoundingBox2 c = getPosition();
      c.position -= getPosition().position;
      return c.inside(position);
    }

  }
}