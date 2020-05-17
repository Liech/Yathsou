#include "LineEdit.h"

#include "glad/glad.h"
#include "../../Renderer/RectangleRenderer.h"
#include "../../Renderer/TextRenderer.h"
#include "IyathuumCoreLib/Singleton/Database.h"
#include "Util/Util.h"

namespace YolonaOss {
  namespace Widgets {
    LineEdit::LineEdit() : Widget()
    {
      _text = "Def";
      Iyathuum::Database<Widgets::Widget*>::add(this, { "MouseClick" });
    }

    LineEdit::LineEdit(std::string text, Iyathuum::AABB<2> position) : Widget(position) {
      _text = text;
      Iyathuum::Database<Widgets::Widget*>::add(this, { "MouseClick" });
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
      RectangleRenderer::drawRectangle(getPosition(), glm::vec3(0.9f, 0.9f, 0.9f));
      RectangleRenderer::end();
      glm::vec2 textSize = TextRenderer::getTextSize(_text, 1);
      glm::vec2 spacing = (Util<2>::array2Vec(getPosition().getSize()) - textSize) / 2.0f;
      TextRenderer::start();
      glm::vec2 pos = Util<2>::array2Vec(getPosition().getPosition()) + spacing;
      TextRenderer::drawText(_text, pos, 1, glm::vec3(0, 0, 0));
      TextRenderer::end();
      RectangleRenderer::start();
      glm::vec2 cursorPos = TextRenderer::getTextSize(_text.substr(0,_cursorPosition), 1);
      Iyathuum::AABB<2> cursorRect = getPosition();
      cursorRect.setPosition({ cursorRect.getPosition()[0]+cursorPos[0]-1 , cursorRect.getPosition()[1] });
      cursorRect.setSize({3,getPosition().getSize()[1]});
      RectangleRenderer::drawRectangle(cursorRect, glm::vec3(0.2f, 0.2f, 0.2f));
      RectangleRenderer::end();
    }

    void LineEdit::setText(std::string text) {
      _text = text;
    }

    std::string LineEdit::getText() {
      return _text;
    }

    bool LineEdit::mouseClick(glm::vec2 position, GL::Key k) {
      
      return true;
    };
  }
}