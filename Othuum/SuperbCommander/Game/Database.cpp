#include "Database.h"

#include "AthanahCommonLib/SupCom/Gamedata/Gamedata.h"
#include "AhwassaGraphicsLib/lib/DearIMGUI/imgui.h"

namespace Superb {
  Database::Database() {
    _gamedata = std::make_unique<Athanah::Gamedata>(_supComPath, _useSCDData);

  }

  void Database::menu() {
    ImGui::Checkbox("Use SCD Data", &_useSCDData);

  }

  Athanah::Gamedata& Database::gamedata() {
    return *_gamedata;
  }

}