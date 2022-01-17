#include "FormationWidget.h"
#include "AhwassaGraphicsLib/Uniforms/Rendertarget.h"
#include "AhwassaGraphicsLib/lib/DearIMGUI/imgui.h"

namespace Superb {
  FormationWidget::FormationWidget() {
    _canvas = std::make_unique<Ahwassa::Rendertarget>("Canvas", _resolutionX, _resolutionY);
  }
  
  void FormationWidget::menu() {    
    ImGui::ImageButton((void*)_canvas->getTextureID(), ImVec2(_resolutionX, _resolutionY));
  }

  void FormationWidget::preDraw() {
    _canvas->start();

    _canvas->end();
  }
}