#pragma once

#include <vector>
#include <memory>
#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "IyathuumCoreLib/BaseTypes/Color.h"
#include "AhwassaGraphicsLib/Input/UIElement.h"

namespace Ahwassa {
  class Rendertarget;
  class Window;
  class BasicRectangleRenderer;
  class Background;
}

namespace Superb {
  namespace Formation {
    class FormationShape;
    class Selector;
    
    enum class FormationWidgetMode {
      None,
      PlaceObject,
      Rotate,
      Move,
      ResizeMM,
      ResizeMP,
      ResizePM,
      ResizePP
    };

    class FormationWidget : public Ahwassa::UIElement {
    public:
      FormationWidget(Ahwassa::Window&);
      virtual ~FormationWidget();

      void update();
      void menu(const glm::ivec2&);
      void preDraw();

      void startShape(std::shared_ptr<FormationShape>);

      virtual bool mouseEvent(const glm::vec2& localPosition, const Iyathuum::Key& button, const Iyathuum::KeyStatus& status);
      virtual bool mouseClickEvent(const glm::vec2& localPosition, const Iyathuum::Key& button) override;
      virtual bool mouseMoveEvent(const glm::vec2& current, const glm::vec2& movement);

    private:
      void drawHover();
      void drawSelection();
      std::shared_ptr<FormationShape> getHover();

      int _resolutionX = 400;
      int _resolutionY = 400;


      FormationWidgetMode _mode = FormationWidgetMode::None;
      glm::vec2           _moveOffset = glm::vec2(0, 0);

      Ahwassa::Window& _window;
      std::unique_ptr<Ahwassa::Rendertarget>           _canvas;
      std::unique_ptr<Ahwassa::BasicRectangleRenderer> _renderer;
      std::unique_ptr<Selector>                        _selector;
      glm::vec2 _mousePos;

      std::shared_ptr<FormationShape> _hover    = nullptr;
      std::shared_ptr<FormationShape> _selected = nullptr;
      std::vector<std::shared_ptr<FormationShape>> _shapes;
    };
  }
}