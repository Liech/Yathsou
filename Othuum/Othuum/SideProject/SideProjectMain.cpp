#include "SideProjectMain.h"

#include "YolonaOss/Drawables/FPS.h"
#include "YolonaOss/Drawables/Background.h"

namespace SideProject
{
  void SideProjectMain::load(YolonaOss::GL::DrawSpecification* spec)
  {
    _list = std::make_shared<YolonaOss::GL::DrawableList>();
    _list->addDrawable(std::make_shared<YolonaOss::Background>());
    _list->addDrawable(std::make_shared<YolonaOss::FPS>());
    _list->load(spec);    
  }

  void SideProjectMain::draw()
  {
    _list->draw();
  }
}