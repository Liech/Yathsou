#pragma once

#include <vector>
#include <memory>
#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "AhwassaGraphicsLib/Input/UIElement.h"

namespace Ahwassa {
  class Rendertarget;
  class Window;
  class BasicRectangleRenderer;
}

namespace Superb {
  namespace Formation {
    class FormationShape;
    enum class FormationWidgetMode {
      None,
      PlaceObject,
    };

    class FormationWidget : public Ahwassa::UIElement {
    public:
      FormationWidget(Ahwassa::Window&);
      virtual ~FormationWidget();

      void update();
      void menu(const glm::ivec2&);
      void preDraw();

      void startShape(std::unique_ptr<FormationShape>);

      virtual bool mouseClickEvent(glm::vec2 localPosition, Iyathuum::Key button) override;

    private:
      int _resolutionX = 400;
      int _resolutionY = 400;
      FormationWidgetMode _mode = FormationWidgetMode::None;

      Ahwassa::Window& _window;
      std::unique_ptr<Ahwassa::Rendertarget>      _canvas;
      std::unique_ptr<Ahwassa::BasicRectangleRenderer> _renderer;
      glm::vec2 _mousePos;

      std::vector<std::unique_ptr<FormationShape>> _shapes;
    };
  }
}