#include "Label.h"

#include "glad/glad.h"
#include "../../Renderer/RectangleRenderer.h"
#include "../../Renderer/TextRenderer.h"
#include "IyathuumCoreLib/Singleton/Database.h"
#include "Util/Util.h"

namespace YolonaOss {
  namespace Widgets {
    Label::Label() : Widget()
    {
      _name = "Def";
      setVisible(true);
    }

    Label::Label(std::string name, Iyathuum::AABB<2> position, Widget* parent) : Widget(position, parent) {
      _name = name;
      setVisible(true);
    }


    Label::~Label()
    {
    }

    void Label::load(GL::DrawSpecification*)
    {

    }

    void Label::draw()
    {
      if (!isVisible())
        return;

      RectangleRenderer::start();
      RectangleRenderer::drawRectangle(getGlobalPosition(), glm::vec3(0.6f, 0.6f, 0.6f));
      RectangleRenderer::end();
      glm::vec2 textSize = TextRenderer::getTextSize(_name, 1);
      glm::vec2 spacing = (Util<2>::array2Vec(getGlobalPosition().getSize()) - textSize) / 2.0f;
      TextRenderer::start();
      glm::vec2 pos = Util<2>::array2Vec(getGlobalPosition().getPosition()) + spacing;
      TextRenderer::drawText(_name, pos, 1, glm::vec3(0, 0, 0));
      TextRenderer::end();
    }
  }
}