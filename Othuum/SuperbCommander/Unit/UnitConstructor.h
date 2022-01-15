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
  class Blueprint;
}

namespace Superb {
  class UnitAgentInterface;

  class UnitConstructor {
  public:
    UnitConstructor(Athanah::Gamedata&);

    void setStartPosition(const glm::vec3& pos);
    void setId(const std::string& id);
    void setPhysic(std::shared_ptr<Suthanus::PhysicEngine>);
    void setSelection(std::shared_ptr<Suthanus::PhysicEngine>);

    std::shared_ptr<Suthanus::Box>            getPhysic()         const;
    std::shared_ptr<Suthanus::Box>            getSelector()       const;
    std::shared_ptr<const Athanah::Blueprint> getBlueprint()      const;
    std::string                               getId()             const;

    std::unique_ptr<UnitAgentInterface>       getAgent() const;

  private:
    float                                     _direction     = 0;
    glm::vec3                                 _groundNormal  = glm::vec3(1,0,0);
    glm::vec3                                 _startPosition;
    std::string                               _id           ;
    std::shared_ptr<Suthanus::PhysicEngine>   _physic       ;
    std::shared_ptr<Suthanus::PhysicEngine>   _selection    ;
    Athanah::Gamedata&                        _gamedata     ;
    std::shared_ptr<const Athanah::Blueprint> _blueprint    ;
  };
}