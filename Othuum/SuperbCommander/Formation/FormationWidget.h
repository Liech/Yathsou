#pragma once

#include <vector>
#include <memory>
#include "IyathuumCoreLib/lib/glm/glm.hpp"
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

      void startShape(std::shared_ptr<FormationShape>);

      virtual bool mouseClickEvent(const glm::vec2& localPosition, const Iyathuum::Key& button) override;

    private:
      void drawHover(const Iyathuum::glmAABB<2>&);
      std::shared_ptr<FormationShape> getHover();

      int _resolutionX = 400;
      int _resolutionY = 400;
      FormationWidgetMode _mode = FormationWidgetMode::None;

      Ahwassa::Window& _window;
      std::unique_ptr<Ahwassa::Rendertarget>           _canvas;
      std::unique_ptr<Ahwassa::BasicRectangleRenderer> _renderer;
      glm::vec2 _mousePos;

      std::shared_ptr<FormationShape> _hover = nullptr;
      std::vector<std::shared_ptr<FormationShape>> _shapes;
    };
  }
}