#include "Database.h"

#include "AthanahCommonLib/SupCom/Gamedata/Gamedata.h"
#include "AhwassaGraphicsLib/lib/DearIMGUI/imgui.h"
#include "AhwassaGraphicsLib/lib/DearIMGUI/imgui_stdlib.h"
#include "AhwassaGraphicsLib/lib/IMGUIFileDialog/ImGuiFileDialog.h"

namespace Superb {
  Database::Database() {
    _gamedata = std::make_unique<Athanah::Gamedata>(_supComPath, _useSCDData);

  }

  void Database::menu() {
    ImGui::Checkbox("Use SCD Data", &_useSCDData);

    ImGui::InputText("SCFA Path", &_supComPath);
    ImGui::SameLine();
    // open Dialog Simple
    if (ImGui::Button("..."))
      ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File",nullptr, ".");
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
    {
      if (ImGuiFileDialog::Instance()->IsOk())
      {
        _supComPath = ImGuiFileDialog::Instance()->GetCurrentPath();
      }
      ImGuiFileDialog::Instance()->Close();
    }

  }

  Athanah::Gamedata& Database::gamedata() {
    return *_gamedata;
  }

  std::string Database::supComPath() {
    return _supComPath;
  }

}