#pragma once

#include <glm/glm.hpp>
#include <string>
#include <memory>
#include <map>
#include <vector>
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "Graphic.h"

class ListSelection;

namespace Ahwassa {
  class Button;
  class Texture;
  class Window;
}
namespace Aezesel {
  class SCMAP;
}
namespace Athanah {
  class SupComModel;
  class Scenario;
  class MapFactory;
  class Gamedata;
}

class MapSelection {
public:
  MapSelection(std::string mapPath, Iyathuum::glmAABB<2> area, Graphic&, Athanah::Gamedata&);

  void update();
  void draw();

  void setVisible(bool value);
  bool isVisible();

private:
  Athanah::Gamedata& _gamedata;
                                      
  std::shared_ptr<Athanah::MapFactory> _factory;
  Graphic&                             _graphic;
  std::unique_ptr<ListSelection  >     _list = nullptr;
  Iyathuum::glmAABB<2>                 _area   ;
};