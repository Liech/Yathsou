#include "ListLayout.h"
#include "../../Renderer/RectangleRenderer.h"
#include "IyathuumCoreLib/Util/Geometry.h"
#include "Drawables/Widgets/Button.h"

namespace YolonaOss {
  namespace Widgets {
    ListLayout::ListLayout(Iyathuum::AABB<2> position) : Widget(position) {

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
        offset += glm::vec2(0,_widgets[0]->getPosition().getSize()[1]);

      for (auto w : _widgets) {
        Iyathuum::AABB<2> pos = w->getPosition();
        pos.setPosition(Iyathuum::Geometry<2>::add(Iyathuum::Geometry<2>::add(getPosition().getPosition() , {0, getPosition().getSize()[1]}) ,{offset[0], -offset[1]}));
      
        if (_horizontal)
          offset += glm::vec2(pos.getSize()[0] + spacing, 0);
        else
          offset += glm::vec2(0, pos.getSize()[1] + spacing);
        w->setPosition(pos);
        w->draw();
      }
    }
    
    void ListLayout::setHorizontal(bool horizontal) {
      _horizontal = horizontal;
    }

    std::shared_ptr<Widgets::Button> ListLayout::addButton(std::string name, std::function<void()> onClicked, Iyathuum::AABB<2> size) {
      std::shared_ptr<Widgets::Button> b = std::make_shared<Widgets::Button>(name, Iyathuum::AABB<2>(std::array<double, 2>{ 0.0, 0.0 }, std::array<double, 2>{ getPosition().getSize()[0], 50.0 }), [onClicked]() { onClicked(); });
      addWidget(b);
      return b;
    }
  }
}