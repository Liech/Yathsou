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
      Iyathuum::Database<Widgets::Widget*>::add(this, { "MouseClick","KeyboardInput" });     
    }

    LineEdit::LineEdit(std::string text, Iyathuum::AABB<2> position) : Widget(position) {
      _text = text;
      Iyathuum::Database<Widgets::Widget*>::add(this, { "MouseClick","KeyboardInput" });
    }


    LineEdit::~LineEdit()
    {
      Iyathuum::Database<Widgets::Widget*>::remove(this);
    }

    void LineEdit::load(GL::DrawSpecification*)
    {

    }

    void LineEdit::draw()
    {
      RectangleRenderer::start();
      if (YolonaOss::GL::InputHandling::getInstance().getCurrentFocus() == this)
        RectangleRenderer::drawRectangle(getPosition(), glm::vec3(0.6f, 0.6f, 0.6f));
      else
        RectangleRenderer::drawRectangle(getPosition(), glm::vec3(0.9f, 0.9f, 0.9f));
      RectangleRenderer::end();
      glm::vec2 textSize = TextRenderer::getTextSize(_text, 1);
      glm::vec2 spacing = (Util<2>::array2Vec(getPosition().getSize()) - textSize) / 2.0f;
      spacing[0] = 0;
      TextRenderer::start();
      glm::vec2 pos = Util<2>::array2Vec(getPosition().getPosition()) + spacing;
      TextRenderer::drawText(_text, pos, 1, glm::vec3(0, 0, 0));
      TextRenderer::end();
      RectangleRenderer::start();
      glm::vec2 cursorPos = TextRenderer::getTextSize(_text.substr(0,_cursorPosition), 1);
      Iyathuum::AABB<2> cursorRect = getPosition();
      cursorRect.setPosition({ cursorRect.getPosition()[0]+spacing[0]+cursorPos[0]-1 , getPosition().getPosition()[1] });
      cursorRect.setSize({3,getPosition().getSize()[1]});
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
      std::cout << position[0] << "/" << position[1] << std::endl;
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
        }
        return;
      }
      if (key == remove) {
        if (_cursorPosition > 0) {
          _text = _text.substr(0, _cursorPosition - 1) + _text.substr(_cursorPosition);
          _cursorPosition--;
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

      if (!YolonaOss::GL::CharacterSets::AlphanumericKeys.contains(key) &&
        !YolonaOss::GL::CharacterSets::InputExtraSymbols.contains(key))
        return;

      _text = _text.substr(0, _cursorPosition) + (char)key + _text.substr(_cursorPosition);
      _cursorPosition++;
      return;
    }

  }
}