#include "FormationWidget.h"

#include "Shapes/FormationShape.h"
#include "Selector.h"

#include "AhwassaGraphicsLib/Input/Input.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Uniforms/Rendertarget.h"
#include "AhwassaGraphicsLib/lib/DearIMGUI/imgui.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicRectangleRenderer.h"
#include "IyathuumCoreLib/lib/glm/gtx/vector_angle.hpp"


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
      _hover = getHover();
    }

    bool FormationWidget::mouseClickEvent(const glm::vec2& localPosition, const Iyathuum::Key& button) {
      if (FormationWidgetMode::PlaceObject == _mode) {
        if (button == Iyathuum::Key::MOUSE_BUTTON_LEFT) {
          _mode = FormationWidgetMode::None;
          _selected = _shapes.back();
          return true;
        }
      }
      else if (FormationWidgetMode::None == _mode) {
        if (button == Iyathuum::Key::MOUSE_BUTTON_LEFT && _selected != _hover) {
          _selected = _hover;
          return true;
        }        
      }
      return false;
    }

    bool FormationWidget::mouseEvent(const glm::vec2& localPosition, const Iyathuum::Key& button, const Iyathuum::KeyStatus& status) {
      if (FormationWidgetMode::None == _mode && _selected != nullptr) {
        Selector s;
        s.setPosition(_selected->getPosition());
        if (s.insideRotate(_mousePos) && button == Iyathuum::Key::MOUSE_BUTTON_LEFT && status == Iyathuum::KeyStatus::PRESS) {
          _mode = FormationWidgetMode::Rotate;
        }
      }
      else if (FormationWidgetMode::Rotate == _mode && button == Iyathuum::Key::MOUSE_BUTTON_LEFT && status == Iyathuum::KeyStatus::RELEASE) {
        _mode = FormationWidgetMode::None;
      }
      return false;
    }

    bool FormationWidget::mouseMoveEvent(const glm::vec2& current, const glm::vec2& movement) {      
      if (FormationWidgetMode::Rotate == _mode && _selected != nullptr) {
        glm::vec2 null(0, -1);
        glm::vec2 vec = glm::normalize(_mousePos - _selected->getPosition().getCenter());
        _selected->setRotation(glm::degrees(glm::orientedAngle(null,vec)));
      }
      return false;
    }

    void FormationWidget::menu(const glm::ivec2& size) {
      _resolutionX = std::max(100,size.x);
      _resolutionY = std::max(100,size.y);
      ImGui::ImageButton((void*)_canvas->getTextureID(), ImVec2(_resolutionX, _resolutionY),ImVec2(0,0),ImVec2(1,1),0);
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

      _renderer->drawRectangle(Iyathuum::glmAABB<2>(glm::vec2(0, 0), res), Iyathuum::Color(50, 50, 50)); //background

      //_renderer->drawRectangle(_mousePos, glm::vec2(4, 4), Iyathuum::Color(255, 0, 0));

      if (_hover != nullptr)
        drawHover();
      if (_selected != nullptr)
        drawSelection();
      if (FormationWidgetMode::Rotate == _mode && _selected != nullptr)
        _renderer->drawLine(_selected->getPosition().getCenter(), _mousePos, 1, Iyathuum::Color(255, 255, 255));

      for (auto& x : _shapes)
        x->draw(*_renderer);

      _renderer->end();
      _canvas->end();
    }

    void FormationWidget::startShape(std::shared_ptr<FormationShape> newObj){
      _mode = FormationWidgetMode::PlaceObject;
      newObj->setPosition(Iyathuum::glmAABB<2>(glm::vec2(0,0),glm::vec2(40,40)));
      _shapes.push_back(std::move(newObj));
    }

    void FormationWidget::drawHover() {
      Selector r;
      r.setPosition(_hover->getPosition());
      r.setColor(Iyathuum::Color(128,128,128));
      r.draw(*_renderer);
    }

    void FormationWidget::drawSelection() {
      Selector r;
      r.setPosition(_selected->getPosition());
      r.setColor(Iyathuum::Color(255,255,255));
      r.setSelected(true);
      r.draw(*_renderer);
    }

    std::shared_ptr<FormationShape> FormationWidget::getHover() {
      std::shared_ptr<FormationShape> bestResult = nullptr;
      for (auto& x : _shapes) {
        if (x->getPosition().isInside(_mousePos)){
          if (bestResult == nullptr)
            bestResult = x;
          else {
            float newCenter = glm::distance(x->getPosition().getCenter(),_mousePos);
            float oldCenter = glm::distance(bestResult->getPosition().getCenter(),_mousePos);
            if (newCenter < oldCenter)
              bestResult = x;
          }
        }
      }
      return bestResult;
    }
  }
}