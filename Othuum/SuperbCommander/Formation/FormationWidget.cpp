#include "FormationWidget.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Uniforms/Rendertarget.h"
#include "AhwassaGraphicsLib/lib/DearIMGUI/imgui.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicRectangleRenderer.h"

namespace Superb {
  FormationWidget::FormationWidget(Ahwassa::Window& window) : _window(window) {
    _renderer = std::make_unique<Ahwassa::BasicRectangleRenderer>(&window);
  }
  
  void FormationWidget::menu() {
    ImVec2 canvas = ImGui::GetContentRegionAvail();
    _resolutionX = canvas.x;
    _resolutionY = canvas.y;
    ImGui::Image((void*)_canvas->getTextureID(), ImVec2(_resolutionX, _resolutionY-30));
  }

  void FormationWidget::preDraw() {
    glm::ivec2 res(_resolutionX, _resolutionY);
    if (!_canvas || _canvas->getResolution() != res) {
      _canvas = std::make_unique<Ahwassa::Rendertarget>("Canvas", _resolutionX, _resolutionY);
      _renderer->setResolution(res);
    }

    _canvas->start();
    _renderer->start();


    _renderer->drawRectangle(glm::vec2(0, 0), glm::vec2(40, 40), Iyathuum::Color(255, 0, 0));
    _renderer->drawLine(glm::vec2(40, 40), glm::vec2(_resolutionX-20, _resolutionY-20), 9, Iyathuum::Color(255, 255, 0));

    _renderer->end();
    _canvas->end();
  }
}