#include "Label.h"

#include "glad/glad.h"
#include "../../Renderer/RectangleRenderer.h"
#include "../../Renderer/TextRenderer.h"
#include "structs/Database.h"

namespace YolonaOss {
  namespace Widgets {
    Label::Label() : Widget()
    {
      _name = "Def";
    }

    Label::Label(std::string name, BoundingBox2 position) : Widget(position) {
      _name = name;
    }


    Label::~Label()
    {
    }

    void Label::load(GL::DrawSpecification*)
    {

    }

    void Label::draw()
    {
      RectangleRenderer::start();
      RectangleRenderer::drawRectangle(getPosition(), glm::vec3(0.6f, 0.6f, 0.6f));
      RectangleRenderer::end();
      glm::vec2 textSize = TextRenderer::getTextSize(_name, 1);
      glm::vec2 spacing = (getPosition().size - textSize) / 2.0f;
      TextRenderer::start();
      glm::vec2 pos = getPosition().position + spacing;
      TextRenderer::drawText(_name, pos, 1, glm::vec3(0, 0, 0));
      TextRenderer::end();
    }
  }
}