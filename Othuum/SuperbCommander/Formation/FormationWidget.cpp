#include "FormationWidget.h"

#include "Shapes/FormationShape.h"

#include "AhwassaGraphicsLib/Input/Input.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Uniforms/Rendertarget.h"
#include "AhwassaGraphicsLib/lib/DearIMGUI/imgui.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicRectangleRenderer.h"

namespace Superb {
  namespace Formation {
    FormationWidget::FormationWidget(Ahwassa::Window& window) : _window(window) {
      _renderer = std::make_unique<Ahwassa::BasicRectangleRenderer>(&window);
      window.input().addUIElement(this);
    }

    FormationWidget::~FormationWidget() {
      _window.input().removeUIElement(this);
    }

    void FormationWidget::update() {
      if (FormationWidgetMode::PlaceObject == _mode) {
        auto aabb = _shapes.back()->getPosition();
        aabb.setCenter(_mousePos);
        _shapes.back()->setPosition(aabb);
      }
    }

    bool FormationWidget::mouseClickEvent(glm::vec2 localPosition, Iyathuum::Key button) {
      if (button == Iyathuum::Key::MOUSE_BUTTON_LEFT && FormationWidgetMode::PlaceObject == _mode) {
        _mode = FormationWidgetMode::None;
        return true;
      }
      return false;
    }

    void FormationWidget::menu(const glm::ivec2& size) {
      _resolutionX = std::max(100,size.x);
      _resolutionY = std::max(100,size.y);
      ImGui::Image((void*)_canvas->getTextureID(), ImVec2(_resolutionX, _resolutionY));
      auto y = _window.input().getCursorPos();
      auto x = ImGui::GetItemRectMin();
      _mousePos = glm::vec2(y[0] - x[0], _window.getHeight() - y[1] - x[1]);
      setLocalPosition(Iyathuum::glmAABB<2>(glm::vec2(x[0],x[1]),glm::vec2(_resolutionX,_resolutionY)));
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


      for (auto& x : _shapes)
        x->draw(*_renderer);

      _renderer->end();
      _canvas->end();
    }

    void FormationWidget::startShape(std::unique_ptr<FormationShape> newObj){
      _mode = FormationWidgetMode::PlaceObject;
      newObj->setPosition(Iyathuum::glmAABB<2>(glm::vec2(0,0),glm::vec2(40,40)));
      _shapes.push_back(std::move(newObj));
    }
  }
}