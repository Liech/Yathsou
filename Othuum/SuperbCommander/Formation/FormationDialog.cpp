#include "FormationDialog.h"

#include "FormationWidget.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/lib/DearIMGUI/imgui.h"

namespace Superb {
  FormationDialog::FormationDialog(Ahwassa::Window& w) : _window(w){
    _canvas = std::make_unique<FormationWidget>(_window);
  }

  void FormationDialog::menu() {    
    if (ImGui::Button("Formation Dialog"))
      ImGui::OpenPopup("Formation");

    // Always center this window when appearing
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal("Formation", NULL, 0))
    {
      menuContent();

      if (ImGui::Button("Close", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
      ImGui::EndPopup();
    }
  }  
 
  void FormationDialog::menuContent() {
    {
      ImGui::BeginGroup();
      ImGui::Button("AAA");
      ImGui::Button("AAA");
      ImGui::Button("AAA");
      ImGui::Button("AAA");
      ImGui::Button("AAA");
      ImGui::Button("AAA");
      ImGui::EndGroup();
    }
    ImGui::SameLine();
    _canvas->menu();

  }

  void FormationDialog::preDraw() {
    _canvas->preDraw();
  }
}