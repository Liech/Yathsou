#include "ListLayout.h"
#include "../../Renderer/RectangleRenderer.h"

namespace YolonaOss {
  namespace Widgets {
    ListLayout::ListLayout(BoundingBox2 position) : Widget(position) {

    }

    int  ListLayout::addWidget(std::shared_ptr<Widget> w) {
      _widgets.push_back(w);
      return (int)(_widgets.size() - 1);
    }

    void ListLayout::removeWidget(int w) {
      _widgets.erase(_widgets.begin() + w);
    }

    void ListLayout::draw() {
      RectangleRenderer::start();
      RectangleRenderer::drawRectangle(getPosition(), glm::vec3(0.7f, 0.7f, 0.7f));
      RectangleRenderer::end();

      glm::vec2 offset(0.0);
      if (_widgets.size() > 0)
        offset += glm::vec2(0,_widgets[0]->getPosition().size[1]);

      for (auto w : _widgets) {
        BoundingBox2 pos = w->getPosition();
        pos.position = getPosition().position + glm::vec2(0,getPosition().size[1]) + glm::vec2(offset[0],-offset[1]);
        if (_horizontal)
          offset += glm::vec2(pos.size[0] + spacing, 0);
        else
          offset += glm::vec2(0, pos.size[1] + spacing);
        w->setPosition(pos);
        w->draw();
      }
    }
    
    void ListLayout::setHorizontal(bool horizontal) {
      _horizontal = horizontal;
    }
  }
}