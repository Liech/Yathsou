#pragma once

#include <string>
#include <memory>
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "Graphic.h"
#include "EyeOfRhianneConfiguration.h"

namespace Ahwassa {
  class Window;
}

namespace Athanah {
  class Gamedata;
}

class UnitModelSelection;
class AnimationSelection;
class SkyBoxSelection;
class ListSelection;
class RendererSelection;
class MapSelection;
class ScriptSelection;
class SoundSelection;
class Graphic;

class AssetSelection {
public:
  AssetSelection(EyeOfRhianneConfiguration&, Iyathuum::glmAABB<2> area,Graphic&);
  virtual ~AssetSelection() = default;

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
  std::unique_ptr<Athanah::Gamedata>  _gamedata;

  std::shared_ptr<UnitModelSelection > _units     ;
  std::shared_ptr<AnimationSelection > _animation ;
  std::shared_ptr<SkyBoxSelection    > _skyBox    ;
  std::shared_ptr<RendererSelection  > _renderer  ;
  std::shared_ptr<MapSelection       > _maps      ;
  std::shared_ptr<ScriptSelection    > _scripts   ;
  std::shared_ptr<SoundSelection     > _sounds    ;
 
  EyeOfRhianneConfiguration& _config;
};