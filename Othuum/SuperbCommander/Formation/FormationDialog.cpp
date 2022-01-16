#include "FormationDialog.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/lib/DearIMGUI/imgui.h"

namespace Superb {
  FormationDialog::FormationDialog(Ahwassa::Window& w) : _window(w){
  }

  void FormationDialog::menu() {
    
    if (ImGui::Button("Formation Dialog"))
      ImGui::OpenPopup("Formation");

    // Always center this window when appearing
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal("Formation", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
      menuContent();

      if (ImGui::Button("Close", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
      ImGui::EndPopup();
    }
  }  
 
  void FormationDialog::menuContent() {
    ImGui::Text("Formation can be edited here. Not yet implemented.\n\n");
    //ImGui::ImageButton(myImage, ImVec2(200.f, 200.f));
  }

}