#include "Database.h"

#include "AthanahCommonLib/SupCom/Gamedata/Gamedata.h"
#include <imgui.h>
#include <imgui_stdlib.h>
#include <IMGUIFileDialog/ImGuiFileDialog.h>

namespace Superb {
  Database::Database() {

  }

  void Database::menu() {
    ImGui::Checkbox("Use SCD Data", &_useSCDData);

    ImGui::InputText("SCFA Path", &_supComPath);
    ImGui::SameLine();
    // open Dialog Simple
    if (ImGui::Button("..."))
      ImGuiFileDialog::Instance()->OpenDialog("SCFAPath", "Choose SupComPath",nullptr, ".");
    if (ImGuiFileDialog::Instance()->Display("SCFAPath"))
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

  void Database::save(nlohmann::json& output) {
    output["SupComPath"] = _supComPath;
    output["UseSCD"]     = _useSCDData;
  }

  void Database::load(nlohmann::json& input) {
    _supComPath = input["SupComPath"];
    _useSCDData = input["UseSCD"];
  }

  void Database::start() {
    _gamedata = std::make_unique<Athanah::Gamedata>(_supComPath, _useSCDData);
  }
}