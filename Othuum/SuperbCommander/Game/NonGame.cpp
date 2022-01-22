#include "NonGame.h"

#include "Formation/FormationDialog.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/lib/DearIMGUI/imgui.h"

namespace Superb {
  NonGame::NonGame(Ahwassa::Window& window) : _window(window) {
  }

  void NonGame::menu() {
    ImGui::Checkbox("Show DearImGui Demo", &_dearIMGUIDemoWindow);
    if (_dearIMGUIDemoWindow)
      ImGui::ShowDemoWindow();
    _formationDialog->menu();

    ImGui::DragFloat("window scale", &_fontScale, 0.005f, 0.05, 4, "%.2f", ImGuiSliderFlags_AlwaysClamp);
    ImGui::SetWindowFontScale(_fontScale);
  }

  void NonGame::update() {
    _formationDialog->update();
  }

  void NonGame::preDraw() {
    _formationDialog->preDraw();
  }

  void NonGame::start() {
    _formationDialog = std::make_unique<Formation::FormationDialog>(_window);
  }

  void NonGame::save(nlohmann::json& output) {
    output["IMGUIDemo"]      = _dearIMGUIDemoWindow;
    output["IMGUIFontScale"] = _fontScale;
  }

  void NonGame::load(nlohmann::json& input) {
    _dearIMGUIDemoWindow = input["IMGUIDemo"];
    _fontScale           = input["IMGUIFontScale"];
  }
}