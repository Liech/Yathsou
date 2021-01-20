#pragma once

#include <memory>
#include "YolonaOss/OpenGL/Drawable.h"
#include "YolonaOss/OpenGL/Updateable.h"

namespace YolonaOss {
  namespace GL {
    class DrawableList;
    class UpdateableList;
  }
}

class MainCharacter;
class MainCharacterVisualization;

class Fervor : public YolonaOss::GL::Drawable, public YolonaOss::GL::Updateable
{
public:
  Fervor();
  virtual void load(YolonaOss::GL::DrawSpecification*) override;
  virtual void update() override;
  virtual void draw()   override;

private:
  std::shared_ptr<YolonaOss::GL::DrawableList>     _preDrawables ;
  std::shared_ptr<YolonaOss::GL::DrawableList>     _postDrawables;
  std::shared_ptr<YolonaOss::GL::UpdateableList>   _updateList   ;

  std::shared_ptr<MainCharacterVisualization     >      _mainCharVis;
  std::shared_ptr<MainCharacter                  >      _mainChar   ;

};