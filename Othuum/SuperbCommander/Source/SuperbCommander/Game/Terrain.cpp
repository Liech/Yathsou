#include "Terrain.h"

#include <imgui.h>
#include <imgui_stdlib.h>
#include <IMGUIFileDialog/ImGuiFileDialog.h>
#include "Database.h"
#include "Physic.h"

#include "SuperbCommander/World.h"
#include "AthanahCommonLib/Map/Map.h"


namespace Superb {
  Terrain::Terrain(Physic& physic, Database& database) :_physic(physic),_database(database) {

  }

  void Terrain::menu() {
    ImGui::InputText("Map Path", &_mapPath);
    ImGui::SameLine();
    // open Dialog Simple
    if (ImGui::Button("Select Map"))
      ImGuiFileDialog::Instance()->OpenDialog("Map", "Choose Map", nullptr, ".");
    if (ImGuiFileDialog::Instance()->Display("Map"))
    {
      if (ImGuiFileDialog::Instance()->IsOk())
      {
        _mapPath = ImGuiFileDialog::Instance()->GetCurrentPath();
      }
      ImGuiFileDialog::Instance()->Close();
    }
  }

  void Terrain::update() {
    _world->update();
  }

  World& Terrain::world() {
    return *_world;
  }

  void Terrain::save(nlohmann::json& output) {
    output["MapPath"] = _mapPath;
  }

  void Terrain::load(nlohmann::json& input) {
    _mapPath = input["MapPath"];
  }

  void Terrain::start() {
    int lastSeperator = _mapPath.find_last_of('\\');
    std::string directory = _mapPath.substr(0, lastSeperator);
    std::string mapName = _mapPath.substr(lastSeperator + 1);
    auto map = std::make_shared<Athanah::Map>(directory,mapName);
    _world   = std::make_unique<Superb::World>(_physic.physic(), map, _database.gamedata());
  }
}