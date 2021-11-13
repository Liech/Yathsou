#pragma once

#include <memory>
#include <string>
#include "IyathuumCoreLib/lib/glm/glm.hpp"

#include "AthanahCommonLib/SupCom/Gamedata/Gamedata.h"

namespace Suthanus {
  class Box;
  class PhysicEngine;
}

namespace Athanah {
  class Gamedata;
}

namespace Superb {

  class UnitConstructor {
  public:
    UnitConstructor(Athanah::Gamedata&);

    void setStartPosition(const glm::vec3& pos);
    void setId(const std::string& id);
    void setPhysic(std::shared_ptr<Suthanus::PhysicEngine>);
    void setSelection(std::shared_ptr<Suthanus::PhysicEngine>);

    std::shared_ptr<Suthanus::Box> getPhysic()   const;
    std::shared_ptr<Suthanus::Box> getSelector() const;
  private:
    glm::vec3                                _startPosition;
    std::string                              _id           ;
    std::shared_ptr<Suthanus::PhysicEngine>  _physic       ;
    std::shared_ptr<Suthanus::PhysicEngine>  _selection    ;
    Athanah::Gamedata&                       _gamedata     ;
  };
}