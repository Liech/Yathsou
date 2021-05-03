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
  class Texture;
  class Window;
}
namespace Aezesel {
  class SCMAP;
}
namespace Athanah {
  class SupComModel;
  class Scenario;
}

struct map {
  std::shared_ptr<Athanah::Scenario> scenario;
  std::shared_ptr<Ahwassa::Texture>  preview ;
  std::shared_ptr<Aezesel::SCMAP>    map;
  std::string name;
};

class MapSelection {
public:
  MapSelection(std::string mapPath, Iyathuum::glmAABB<2> area, Graphic&);

  void update();
  void draw();

  void setVisible(bool value);
  bool isVisible();

private:
                                                      
  std::shared_ptr<Ahwassa::Texture> _previewImage{ nullptr };
  Graphic&                                                  _graphic;
  std::unique_ptr<ListSelection  >                          _list = nullptr;
  Iyathuum::glmAABB<2>                                      _area;
  std::map<std::string, map> _scenarios;
};