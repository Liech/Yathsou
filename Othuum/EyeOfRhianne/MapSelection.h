#pragma once

#include <IyathuumCoreLib/lib/glm/glm.hpp>
#include <string>
#include <memory>
#include <map>
#include <vector>
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "Graphic.h"

class ListSelection;

namespace Ahwassa {
  class Button;
  class Window;
}

namespace Athanah {
  class SupComModel;
  class Scenario;
}

class MapSelection {
public:
  MapSelection(std::string mapPath, Iyathuum::glmAABB<2> area, Graphic&);

  void update();
  void draw();

  void setVisible(bool value);
  bool isVisible();

private:
                                                            
  Graphic&                                                  _graphic;
  std::unique_ptr<ListSelection  >                          _list = nullptr;
  Iyathuum::glmAABB<2>                                      _area;
  std::map<std::string, std::shared_ptr<Athanah::Scenario>> _scenarios;
};