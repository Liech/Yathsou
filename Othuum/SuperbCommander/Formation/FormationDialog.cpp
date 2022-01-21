#include "FormationDialog.h"

#include "FormationWidget.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/lib/DearIMGUI/imgui.h"

namespace Superb {
  namespace Formation {
    FormationDialog::FormationDialog(Ahwassa::Window& w) : _window(w) {
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
        bool circle = ImGui::Button("Circle");
        ImGui::Button("AAA");
        ImGui::Button("AAA");
        ImGui::Button("AAA");
        ImGui::Button("AAA");
        ImGui::Button("AAA");
        ImGui::EndGroup();

        if (circle)
          _canvas->startCircle();
      }
      ImGui::SameLine();

      ImVec2 canvas = ImGui::GetContentRegionAvail();
      _canvas->menu(glm::ivec2(canvas.x, canvas.y - 30));
    }

    void FormationDialog::preDraw() {
      _canvas->preDraw();
    }
  }
}