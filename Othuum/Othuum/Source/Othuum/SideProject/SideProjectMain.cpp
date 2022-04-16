#include "SideProjectMain.h"

#include "AhwassaGraphicsLib/Drawables/FPS.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"

namespace SideProject
{
  SideProjectMain::SideProjectMain(Ahwassa::Window* w) : Ahwassa::Drawable(w){
   _list.push_back(std::make_shared<Ahwassa::Background>(w));
   _list.push_back(std::make_shared<Ahwassa::FPS>(w));
  }

  void SideProjectMain::draw()
  {
    for (auto x : _list)
      x->draw();
  }

  void SideProjectMain::load() {

  }
}