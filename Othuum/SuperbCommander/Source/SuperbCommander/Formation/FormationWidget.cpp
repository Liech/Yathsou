#include "FormationWidget.h"

#include "Shapes/FormationShape.h"
#include "Selector.h"

#include <imgui.h>
#include <glm/gtx/vector_angle.hpp>

#include "AhwassaGraphicsLib/Input/Input.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Uniforms/Rendertarget.h"
#include "AhwassaGraphicsLib/Renderer/BasicRectangleRenderer.h"


namespace Superb {
  namespace Formation {
    FormationWidget::FormationWidget(Ahwassa::Window& window) : _window(window) {
      _renderer = std::make_unique<Ahwassa::BasicRectangleRenderer>(&window);
      window.input().addUIElement(this);
      _selector = std::make_unique<Selector>();
      _selector->setColor(Iyathuum::Color(255, 255, 255));
      _selector->setSelected(true);
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
        _selector->setPosition(_selected->getPosition());
        _selector->setRotation(_selected->getRotation());
        auto edge = _selector->getSelectedEdge(_mousePos);
        if (_selector->insideRotate(_mousePos) && button == Iyathuum::Key::MOUSE_BUTTON_LEFT && status == Iyathuum::KeyStatus::PRESS) {
          _mode = FormationWidgetMode::Rotate;
          return true;
        }
        else if (_selector->insideSelect(_mousePos) && button == Iyathuum::Key::MOUSE_BUTTON_LEFT) {
          _mode = FormationWidgetMode::Move;
          _moveOffset = _selected->getPosition().getCenter() - _mousePos;
          return true;
        }
        else if (edge != SelectedEdge::None && button == Iyathuum::Key::MOUSE_BUTTON_LEFT) {
          if (edge == SelectedEdge::MM)
            _mode = FormationWidgetMode::ResizeMM;
          else if (edge == SelectedEdge::PM)
            _mode = FormationWidgetMode::ResizePM;
          else if (edge == SelectedEdge::MP)
            _mode = FormationWidgetMode::ResizeMP;
          else if (edge == SelectedEdge::PP)
            _mode = FormationWidgetMode::ResizePP;
        }
        //else if (_selector->insideSelect(_mousePos) && button == Iyathuum::Key::MOUSE_BUTTON_RIGHT) {
        //  _mode = FormationWidgetMode::ContextMenu;
        //  _contextMenuPosition = _window.input().getCursorPos();
        //  return true;
        //}
      }
      else if (FormationWidgetMode::Rotate == _mode && button == Iyathuum::Key::MOUSE_BUTTON_LEFT && status == Iyathuum::KeyStatus::RELEASE) {
        _mode = FormationWidgetMode::None;
        return true;
      }
      else if (FormationWidgetMode::Move == _mode && button == Iyathuum::Key::MOUSE_BUTTON_LEFT && status == Iyathuum::KeyStatus::RELEASE) {
        _mode = FormationWidgetMode::None;
        return true;
      }
      else if ((FormationWidgetMode::ResizeMM == _mode || FormationWidgetMode::ResizePM == _mode || FormationWidgetMode::ResizeMP == _mode || FormationWidgetMode::ResizePP == _mode )
        && button == Iyathuum::Key::MOUSE_BUTTON_LEFT && status == Iyathuum::KeyStatus::RELEASE) {
        _mode = FormationWidgetMode::None;
        return true;
      }
      return false;
    }

    bool FormationWidget::mouseMoveEvent(const glm::vec2& current, const glm::vec2& movement) {
      if (FormationWidgetMode::Rotate == _mode && _selected != nullptr) {
        glm::vec2 null(0, -1);
        glm::vec2 vec = glm::normalize(_mousePos - _selected->getPosition().getCenter());
        _selected->setRotation(glm::degrees(glm::orientedAngle(null, vec)));
        return true;
      }
      else if (FormationWidgetMode::Move == _mode && _selected != nullptr){
        auto pos = _selected->getPosition();
        pos.setCenter(_mousePos + _moveOffset);
        _selected->setPosition(pos);
        return true;
      }
      else if (FormationWidgetMode::ResizeMM == _mode) {
        auto newPos = _selector->setEdge(_mousePos, SelectedEdge::MM);
        _selected->setPosition(newPos);
      }
      else if (FormationWidgetMode::ResizeMP == _mode) {
        auto newPos = _selector->setEdge(_mousePos, SelectedEdge::MP);
        _selected->setPosition(newPos);
      }
      else if (FormationWidgetMode::ResizePM == _mode) {
        auto newPos = _selector->setEdge(_mousePos, SelectedEdge::PM);
        _selected->setPosition(newPos);
      }
      else if (FormationWidgetMode::ResizePP == _mode) {
        auto newPos = _selector->setEdge(_mousePos, SelectedEdge::PP);
        _selected->setPosition(newPos);
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

      bool canBeOpened = _mode == FormationWidgetMode::None && _selected != nullptr && _selector->insideSelect(_mousePos);
      if ((canBeOpened || _mode == FormationWidgetMode::ContextMenu) && ImGui::BeginPopupContextItem())
      {
        _mode = FormationWidgetMode::ContextMenu;
        contextMenu();
        ImGui::EndPopup();
      }
      else if (_mode == FormationWidgetMode::ContextMenu)
        _mode = FormationWidgetMode::None;       
    }

    void FormationWidget::contextMenu() {
      int groupNumber = _selected->getGroup();
      ImGui::InputInt("Group", &groupNumber);
      _selected->setGroup(groupNumber);
      
      bool directed  = _selected->getGradientType() == FormationShapeGradientType::Directed;
      bool spherical = _selected->getGradientType() == FormationShapeGradientType::Spherical;

      if (ImGui::BeginCombo("Gradient Type", FormationShape::ShapeGradientType2String(_selected->getGradientType()).c_str(), 0))
      {
        if (ImGui::Selectable(FormationShape::ShapeGradientType2String(FormationShapeGradientType::Directed).c_str(), directed))
          _selected->setGradientType(FormationShapeGradientType::Directed);
        if (directed)
          ImGui::SetItemDefaultFocus();
        
        if (ImGui::Selectable(FormationShape::ShapeGradientType2String(FormationShapeGradientType::Spherical).c_str(), spherical))
          _selected->setGradientType(FormationShapeGradientType::Spherical);
        if (spherical)
          ImGui::SetItemDefaultFocus();

          // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
        ImGui::EndCombo();
      }
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
      r.setRotation(_hover->getRotation());
      r.setColor(Iyathuum::Color(128, 128, 128));
      r.draw(*_renderer);
    }

    void FormationWidget::drawSelection() {
      Selector r;
      _selector->setPosition(_selected->getPosition());
      _selector->setRotation(_selected->getRotation());
      _selector->draw(*_renderer);
    }

    std::shared_ptr<FormationShape> FormationWidget::getHover() {
      std::shared_ptr<FormationShape> bestResult = nullptr;
      for (auto& x : _shapes) {
        Selector r;
        r.setPosition(x->getPosition());
        r.setRotation(x->getRotation());
        if (r.insideSelect(_mousePos)){
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