#include "LineEdit.h"

#include <IyathuumCoreLib/Singleton/Database.h>
#include "AhwassaGraphicsLib/Renderer/Private/DirectRectangleRenderer.h"
#include "AhwassaGraphicsLib/Renderer/Private/DirectTextRenderer.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Input/Input.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"

namespace Ahwassa {
  LineEdit::LineEdit(Window* w) : Drawable(w)
  {
    _text = "Def";
  }

  LineEdit::LineEdit(std::string text, Iyathuum::glmAABB<2> position, Window* w, UIElement* parent) : Drawable(w),  
    _text          { ""   },
   _cursorPosition { 3    },
   _hasFocus       { false},
   _changed        { false},
    
   _textChangedCallback      {[](std::string s) {}},
   _finishedEditingCallback  {[](std::string s) {}},
   _validator                {defaultValidator()  }
  {
    _text = text;
    setParent(parent);
    setLocalPosition(position);    
    getWindow()->input().addUIElement(this);
  }


  LineEdit::~LineEdit()
  {
    setVisible(false);  
    getWindow()->input().removeUIElement(this);

  }

  void LineEdit::draw()
  {
    if (!isVisible())
      return;

    getWindow()->renderer().rectangle().start();
    if (_hasFocus)
      getWindow()->renderer().rectangle().drawRectangle(getGlobalPosition(), Iyathuum::Color(255*0.6f, 255 * 0.6f, 255 * 0.6f));
    else
      getWindow()->renderer().rectangle().drawRectangle(getGlobalPosition(), Iyathuum::Color(255 * 0.9f, 255 * 0.9f, 255 * 0.9f));
    getWindow()->renderer().rectangle().end();
    glm::vec2 textSize =  getWindow()->renderer().text().getTextSize(_text, 1);
    glm::vec2 spacing = (getGlobalPosition().getSize() - textSize) / 2.0f;
    spacing[0] = 0;
     getWindow()->renderer().text().start();
    glm::vec2 pos = getGlobalPosition().getPosition() + spacing;
     getWindow()->renderer().text().drawText(_text, pos, 1, Iyathuum::Color(0, 0, 0));
     getWindow()->renderer().text().end();
    getWindow()->renderer().rectangle().start();
    glm::vec2 cursorPos =  getWindow()->renderer().text().getTextSize(_text.substr(0, _cursorPosition), 1);
    Iyathuum::glmAABB<2> cursorRect = getGlobalPosition();
    cursorRect.setPosition({ cursorRect.getPosition()[0] + spacing[0] + cursorPos[0] - 1 , getGlobalPosition().getPosition()[1] });
    cursorRect.setSize({ 3,getGlobalPosition().getSize()[1] });
    if (_hasFocus)
      getWindow()->renderer().rectangle().drawRectangle(cursorRect, Iyathuum::Color(255 * 0.8f, 255 * 0.4f, 255 * 0.4f));
    getWindow()->renderer().rectangle().end();
  }

  void LineEdit::setText(std::string text) {
    _text = text;
  }

  std::string LineEdit::getText() {
    return _text;
  }

  bool LineEdit::mouseClickEvent(glm::vec2 position, Iyathuum::Key button) {
    getWindow()->input().setFocus(this);
    for (size_t i = 1; i < _text.length() + 1; i++) {
      std::string sub = _text.substr(0, i);
      glm::vec2 textSize =  getWindow()->renderer().text().getTextSize(sub, 1);
      Iyathuum::glmAABB<2> rect;
      rect.setPosition(glm::vec2(0, 0));
      rect.setSize(glm::vec2(textSize[0], getLocalPosition().getSize()[1]));
      if (rect.isInside(glm::vec2(position[0], position[1]))) {
        _cursorPosition = (int)i - 1;
        return true;
      }
    }
    _cursorPosition = (int)_text.length();
    return true;
  };

  bool LineEdit::focusKeyEvent(Iyathuum::Key key, Iyathuum::KeyStatus status) {
    auto left = Iyathuum::Key::KEY_LEFT;
    auto right = Iyathuum::Key::KEY_RIGHT;
    auto del = Iyathuum::Key::KEY_DELETE;
    auto remove = Iyathuum::Key::KEY_BACKSPACE;

    if (status == Iyathuum::KeyStatus::RELEASE)
      return true;

    if (key == del) {
      if (_cursorPosition < _text.size()) {
        _text = _text.substr(0, _cursorPosition) + _text.substr(_cursorPosition + 1);
        _changed = true;
        _textChangedCallback(_text);
      }
      return true;
    }
    if (key == remove) {
      if (_cursorPosition > 0) {
        _text = _text.substr(0, _cursorPosition - 1) + _text.substr(_cursorPosition);
        _cursorPosition--;
        _changed = true;
        _textChangedCallback(_text);
      }
      return true;
    }
    if (key == left) {
      if (_cursorPosition > 0)
        _cursorPosition--;
      return true;
    }
    if (key == right) {
      if (_cursorPosition < _text.size())
        _cursorPosition++;
      return true;
    }

    std::string newText = _text.substr(0, _cursorPosition) + (char)key + _text.substr(_cursorPosition);;

    if (!_validator(key, newText))
      return true;

    _text = newText;
    _cursorPosition++;
    _changed = true;
    _textChangedCallback(_text);
    return true;
  }

  void LineEdit::startFocusEvent() {
    _hasFocus = true;
    _changed = false;
  }

  void LineEdit::endFocusEvent() {
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

  void LineEdit::setValidator(std::function<bool(Iyathuum::Key, std::string)> validator) {
    _validator = validator;
  }

  std::function<bool(Iyathuum::Key, std::string full)> LineEdit::defaultValidator() {
    return [](Iyathuum::Key key, std::string full) -> bool {
      return Iyathuum::CharacterSets::AlphanumericKeys.count(key) != 0 ||
        Iyathuum::CharacterSets::InputExtraSymbols.count(key) != 0;
    };
  }

  std::function<bool(Iyathuum::Key, std::string full)> LineEdit::integerValidator(int min, int max) {
    return [min, max](Iyathuum::Key character, std::string newText) -> bool {
      bool numeric = Iyathuum::CharacterSets::Numeric.count(character) != 0;
      int  number = std::atoi(newText.c_str());
      return numeric && number > min && number < max;
    };
  }
}