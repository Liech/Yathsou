#pragma once

#include <IyathuumCoreLib/lib/glm/glm.hpp>
#include <string>
#include <memory>
#include <map>
#include <functional>
#include <vector>
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "Graphic.h"

class ListSelection;

namespace Ahwassa {
  class Button;
  class Texture;
  class Window;
  class Box;
  class Dot;
  class BoxRenderer;
}
namespace Aezesel {
  class SCMAP;
}
namespace Athanah {
  class SupComModel;
  class Scenario;
  class MapFactory;
}

class MapTextureSelection {
public:
  MapTextureSelection(Iyathuum::glmAABB<2> area, Graphic&);

  void update();
  void draw();

  void setVisible(bool value);
  bool isVisible();

private:
  void setImage(std::string);
  void setGeometry(int width, int height, std::function<float(int x, int y)>);

  Graphic&                                   _graphic;
  std::unique_ptr<ListSelection  >           _list = nullptr;
  Iyathuum::glmAABB<2>                       _area   ;
  std::vector<std::shared_ptr<Ahwassa::Box>> _boxes;
  std::vector<std::shared_ptr<Ahwassa::Dot>> _dots;

};