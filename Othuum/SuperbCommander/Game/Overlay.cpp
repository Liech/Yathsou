#include "Overlay.h"

#include "AhwassaGraphicsLib/lib/DearIMGUI/imgui.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Input/Input.h"
#include "AhwassaGraphicsLib/Drawables/FPS.h"

namespace Superb{
  Overlay::Overlay(Ahwassa::Window& w) : _window(w){  
  }

  void Overlay::menu() {
    ImGui::Checkbox("Show FPS", &_showFps);
  }

  void Overlay::drawLastLayer() {
    if (_showFps)
      _fps->draw();
  }

  void Overlay::drawFirstLayer() {
  }

  void Overlay::save(nlohmann::json& output) {
    output["ShowFPS"] = _showFps;
  }

  void Overlay::load(nlohmann::json& input) {
    _showFps = input["ShowFPS"];
  }

  void Overlay::start() {
    _fps = std::make_unique<Ahwassa::FPS>(&_window);
  }
}