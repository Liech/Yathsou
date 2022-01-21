#include "FormationWidget.h"

#include "Shapes/FormationShape.h"
#include "Shapes/CircleShape.h"

#include "AhwassaGraphicsLib/Input/Input.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Uniforms/Rendertarget.h"
#include "AhwassaGraphicsLib/lib/DearIMGUI/imgui.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicRectangleRenderer.h"

namespace Superb {
  namespace Formation {
    FormationWidget::FormationWidget(Ahwassa::Window& window) : _window(window) {
      _renderer = std::make_unique<Ahwassa::BasicRectangleRenderer>(&window);
    }

    void FormationWidget::menu(const glm::ivec2& size) {
      _resolutionX = std::max(100,size.x);
      _resolutionY = std::max(100,size.y);
      ImGui::Image((void*)_canvas->getTextureID(), ImVec2(_resolutionX, _resolutionY));
      auto y = _window.input().getCursorPos();
      auto x = ImGui::GetItemRectMin();
      _mousePos = glm::vec2(y[0] - x[0], _window.getHeight() - y[1] - x[1]);
    }

    void FormationWidget::preDraw() {
      glm::ivec2 res(_resolutionX, _resolutionY);
      if (!_canvas || _canvas->getResolution() != res) {
        _canvas = std::make_unique<Ahwassa::Rendertarget>("Canvas", _resolutionX, _resolutionY);
        _renderer->setResolution(res);
      }

      _canvas->start();
      _renderer->start();

      _renderer->drawRectangle(_mousePos, glm::vec2(4, 4), Iyathuum::Color(255, 0, 0));
      //glm::vec2(_resolutionX - 20, _resolutionY - 20)
      //_renderer->drawLine(glm::vec2(40, 40), _mousePos, 9, Iyathuum::Color(255, 255, 0));

      if (FormationWidgetMode::PlaceObject == _mode) {
        auto aabb = _shapes.back()->getPosition();
        aabb.setCenter(_mousePos);
        _shapes.back()->setPosition(aabb);
      }

      for (auto& x : _shapes)
        x->draw(*_renderer);

      _renderer->end();
      _canvas->end();
    }

    void FormationWidget::startCircle() {
      _mode = FormationWidgetMode::PlaceObject;
      std::unique_ptr<CircleShape> newObj = std::make_unique<CircleShape>();
      newObj->setPosition(Iyathuum::glmAABB<2>(glm::vec2(0,0),glm::vec2(40,40)));
      _shapes.push_back(std::move(newObj));
    }
  }
}