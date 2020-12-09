#include "LineEdit.h"

#include <iostream>

#include "glad/glad.h"
#include "../../Renderer/RectangleRenderer.h"
#include "../../Renderer/TextRenderer.h"
#include "IyathuumCoreLib/Singleton/Database.h"
#include "Util/Util.h"
#include "OpenGL/InputHandling.h"

namespace YolonaOss {
  namespace Widgets {
    LineEdit::LineEdit() : Widget()
    {
      _text = "Def";
      setVisible(true);
    }

    LineEdit::LineEdit(std::string text, Iyathuum::AABB<2> position, Widget* parent) : Widget(position, parent) {
      _text = text;
      setVisible(true);
    }


    LineEdit::~LineEdit()
    {
      setVisible(false);
    }

    void LineEdit::load(GL::DrawSpecification*)
    {

    }

    void LineEdit::draw()
    {
      if (!isVisible())
        return;

      RectangleRenderer::start();
      if (_hasFocus)
        RectangleRenderer::drawRectangle(getGlobalPosition(), glm::vec3(0.6f, 0.6f, 0.6f));
      else
        RectangleRenderer::drawRectangle(getGlobalPosition(), glm::vec3(0.9f, 0.9f, 0.9f));
      RectangleRenderer::end();
      glm::vec2 textSize = TextRenderer::getTextSize(_text, 1);
      glm::vec2 spacing = (Util<2>::array2Vec(getGlobalPosition().getSize()) - textSize) / 2.0f;
      spacing[0] = 0;
      TextRenderer::start();
      glm::vec2 pos = Util<2>::array2Vec(getGlobalPosition().getPosition()) + spacing;
      TextRenderer::drawText(_text, pos, 1, glm::vec3(0, 0, 0));
      TextRenderer::end();
      RectangleRenderer::start();
      glm::vec2 cursorPos = TextRenderer::getTextSize(_text.substr(0,_cursorPosition), 1);
      Iyathuum::AABB<2> cursorRect = getGlobalPosition();
      cursorRect.setPosition({ cursorRect.getPosition()[0]+spacing[0]+cursorPos[0]-1 , getGlobalPosition().getPosition()[1] });
      cursorRect.setSize({3,getGlobalPosition().getSize()[1]});
      if (_hasFocus)
        RectangleRenderer::drawRectangle(cursorRect, glm::vec3(0.8f, 0.4f, 0.4f));
      RectangleRenderer::end();
    }

    void LineEdit::setText(std::string text) {
      _text = text;
    }

    std::string LineEdit::getText() {
      return _text;
    }

    bool LineEdit::mouseClick(glm::vec2 position, GL::Key k) {
      //std::cout << position[0] << "/" << position[1] << std::endl;
      
      for (size_t i = 1; i < _text.length()+1; i++) {
        std::string sub = _text.substr(0, i);
        glm::vec2 textSize = TextRenderer::getTextSize(sub, 1);
        Iyathuum::AABB<2> rect;
        rect.setPosition(std::array<double, 2>{0, 0});
        rect.setSize(std::array<double, 2>{textSize[0], getPosition().getSize()[1]});
        if (rect.isInside(std::array<double, 2>{position[0], position[1]})){
          _cursorPosition = i-1;
          return true;
        }
      }
      _cursorPosition = _text.length();
      return true;
    };

    void LineEdit::focusedKeyboardInput(YolonaOss::GL::Key key, YolonaOss::GL::KeyStatus status) {
      auto left   = YolonaOss::GL::Key::KEY_LEFT;
      auto right  = YolonaOss::GL::Key::KEY_RIGHT;
      auto del    = YolonaOss::GL::Key::KEY_DELETE;
      auto remove = YolonaOss::GL::Key::KEY_BACKSPACE;

      if (status == YolonaOss::GL::KeyStatus::RELEASE)
        return;

      if (key == del) {
        if (_cursorPosition < _text.size()) {
          _text = _text.substr(0, _cursorPosition) + _text.substr(_cursorPosition + 1);
          _changed = true;
          _textChangedCallback(_text);
        }
        return;
      }
      if (key == remove) {
        if (_cursorPosition > 0) {
          _text = _text.substr(0, _cursorPosition - 1) + _text.substr(_cursorPosition);
          _cursorPosition--;
          _changed = true;
          _textChangedCallback(_text);
        }
        return;
      }
      if (key == left) {
        if (_cursorPosition > 0)
          _cursorPosition--;
        return;
      }
      if (key == right){
        if(_cursorPosition < _text.size())
          _cursorPosition++;
        return;
      }

      std::string newText = _text.substr(0, _cursorPosition) + (char)key + _text.substr(_cursorPosition);;

      if (!_validator(key,newText))
        return;

      _text = newText;
      _cursorPosition++;
      _changed = true;
      _textChangedCallback(_text);
      return;
    }

    void LineEdit::setVisible(bool visible) {
      if (visible && !isVisible())
        Iyathuum::Database<Widgets::Widget*>::add(this, { "MouseClick","KeyboardInput" });
      else if (!visible && isVisible())
        Iyathuum::Database<Widgets::Widget*>::remove(this);

      Widget::setVisible(visible);
    }

    void LineEdit::focusStart() { 
      _hasFocus = true;
      _changed = false;
    }

    void LineEdit::focusEnd() { 
      _hasFocus = false;
      _cursorPosition = 0;
      if (_changed)
        _finishedEditingCallback(_text);
      _changed = false;
    }

    void LineEdit::setTextChangedCallback(std::function<void(std::string)> callback) {
      _textChangedCallback = callback;
    }

    void LineEdit::setEditFinishedCallback(std::function<void(std::string)> callback) {
      _finishedEditingCallback = callback;
    }

    void LineEdit::setValidator(std::function<bool(YolonaOss::GL::Key,std::string)> validator) {
      _validator = validator;
    }

    std::function<bool(YolonaOss::GL::Key, std::string full)> LineEdit::defaultValidator() {
      return [](YolonaOss::GL::Key key, std::string full) -> bool {
        return YolonaOss::GL::CharacterSets::AlphanumericKeys.count(key)!=0 ||
          YolonaOss::GL::CharacterSets::InputExtraSymbols.count(key) != 0;
      };
    }

    std::function<bool(YolonaOss::GL::Key, std::string full)> LineEdit::integerValidator(int min, int max) {
      return [min,max](YolonaOss::GL::Key character, std::string newText) -> bool{
        bool numeric = YolonaOss::GL::CharacterSets::Numeric.count(character) != 0;
        int  number = std::atoi(newText.c_str());
        return numeric && number > min && number < max;
      };
    }

  }
}