#pragma once

#include <IyathuumCoreLib/lib/glm/glm.hpp>
#include <string>
#include <memory>
#include <vector>
#include <functional>
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"

class ListSelection;
class AnimationSelection;

namespace Ahwassa {
  class Window;
  class Button;
}
namespace Athanah {
  class SupComModelFactory;
  class BlueprintFactory;
  class SupComModel;
}

class Graphic;

class UnitModelSelection {
public:
  UnitModelSelection(const std::string path, Iyathuum::glmAABB<2> area,std::function<void()> disableAllCall, Graphic&);

  void setVisible(bool value);
  bool isVisible();
  void draw();
  void update();

  std::shared_ptr<Athanah::SupComModel> getCurrentModel();

  std::vector<std::string> getNames();

private:
  Graphic&                                      _graphic;
  std::unique_ptr<ListSelection>                _list;
  std::string                                   _currentID = "";
  std::shared_ptr< Athanah::SupComModelFactory> _factory   ;
  std::shared_ptr< Athanah::BlueprintFactory  > _blueprints;
  std::function<void()>                         _disableAllCall;

};