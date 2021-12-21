#include "Physic.h"

#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "AhwassaGraphicsLib/lib/DearIMGUI/imgui.h"

namespace Superb {
  Physic::Physic() {
    _physic = std::make_shared<Suthanus::PhysicEngine>();
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
}