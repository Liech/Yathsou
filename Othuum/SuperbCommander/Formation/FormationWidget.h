#pragma once

#include <vector>
#include <memory>
#include "IyathuumCoreLib/lib/glm/glm.hpp"

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

    class FormationWidget {
    public:
      FormationWidget(Ahwassa::Window&);
      virtual ~FormationWidget() = default;

      void menu(const glm::ivec2&);
      void preDraw();

      void startCircle();

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