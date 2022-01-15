#pragma once

#include <vector>
#include <map>
#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"

#include "SelenNavigationLib/NavigationAgent.h"
#include "SelenNavigationLib/NavigationMap.h"
#include "SelenNavigationLib/Maps/PersonalSpaceMap.h"
#include "Unit/Unit.h"
#include "AthanahCommonLib/SupCom/Gamedata/Gamedata.h"

namespace Ahwassa {
  class Window;
}

namespace Suthanus {
  class PhysicEngine;
  class Box;
}

namespace Superb {
  class UnitsOld : public Selen::PersonalSpaceMap<3>::PersonalSpaceMapInterface{
  public:
    UnitsOld(Athanah::Gamedata& gamedata, std::shared_ptr<Suthanus::PhysicEngine> physic);

    std::vector<std::shared_ptr<Unit>> select(glm::vec3 pos, glm::vec3 dir);
    std::vector<std::shared_ptr<Unit>> selectCameraRect(glm::vec2 rectangleStart, glm::vec2 rectangleEnd, Ahwassa::Window& window);
    
    std::vector<std::shared_ptr<Unit>> getUnits() const;

    void update();
    void debugDraw();
    void spawnUnit(const glm::vec3& position);
    
    std::vector<glm::vec3> PersonalSpaceQuery(const glm::vec3&, float maxDistance) const override;
  private:

    std::map<std::shared_ptr<Suthanus::Box>,std::shared_ptr<Unit>> _units    ;
    std::shared_ptr<Suthanus::PhysicEngine>                        _selection;
    std::shared_ptr<Suthanus::PhysicEngine>                        _physic;
       
    Athanah::Gamedata& _gamedata;
  };
}