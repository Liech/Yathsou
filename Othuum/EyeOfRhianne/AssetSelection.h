#pragma once

#include <string>
#include <memory>
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "Graphic.h"
#include "EyeOfRhianneConfiguration.h"

namespace Ahwassa {
  class Window;
}

class UnitModelSelection;
class AnimationSelection;
class SkyBoxSelection;
class ListSelection;
class RendererSelection;
class MapSelection;
class MapTextureSelection;
class Graphic;

class AssetSelection {
public:
  AssetSelection(EyeOfRhianneConfiguration&, Iyathuum::glmAABB<2> area,Graphic&);


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
  Graphic&                            _graphic;
  Iyathuum::glmAABB<2>                _area;

  std::shared_ptr<UnitModelSelection > _units     ;
  std::shared_ptr<AnimationSelection > _animation ;
  std::shared_ptr<SkyBoxSelection    > _skyBox    ;
  std::shared_ptr<RendererSelection  > _renderer  ;
  std::shared_ptr<MapSelection       > _maps      ;
  std::shared_ptr<MapTextureSelection> _mapTexture;
  EyeOfRhianneConfiguration& _config;
};