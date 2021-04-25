#pragma once

#include <string>
#include <memory>
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "Graphic.h"

namespace Ahwassa {
  class Window;
}

class UnitModelSelection;
class AnimationSelection;
class ListSelection;
class Graphic;

class AssetSelection {
public:
  AssetSelection(const std::string& path, Iyathuum::glmAABB<2> area,Graphic&);


  void setVisible(bool);
  bool isVisible();

  void draw();
  void update();
private:
  void unitVisibility(std::string);
  void hideAll();
  void addSelections();

  std::string                         _current;
  std::unique_ptr<ListSelection>      _list;
  std::string                         _path;
  Graphic&                            _graphic;
  std::shared_ptr<UnitModelSelection> _units;
  std::shared_ptr<AnimationSelection> _animation;
  Iyathuum::glmAABB<2>                _area;
};