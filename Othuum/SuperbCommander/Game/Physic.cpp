#include "Physic.h"

#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "AhwassaGraphicsLib/lib/DearIMGUI/imgui.h"

namespace Superb {
  Physic::Physic() {
  }

  std::shared_ptr<Suthanus::PhysicEngine> Physic::physic() {
    return _physic;
  }

  void Physic::menu() {
    ImGui::Checkbox("Pause Physic", &_freezePhysic);
  }

  void Physic::update() {
    if (!_freezePhysic)
      _physic->update();
  }

  void Physic::save(nlohmann::json& output) {

  }

  void Physic::load(nlohmann::json& input) {

  }

  void Physic::start() {
    _physic = std::make_shared<Suthanus::PhysicEngine>();
  }
}