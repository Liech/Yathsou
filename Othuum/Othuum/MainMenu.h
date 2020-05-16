#pragma once

#include <memory>
#include <functional>

#include "YolonaOss/OpenGL/Drawable.h"
#include "IyathuumCoreLib/BaseTypes/AABB.h"
#include "YolonaOss/Drawables/Widgets/Button.h"

namespace YolonaOss {
  namespace Widgets {
    class ListLayout;
  }
}

class MainMenu : public YolonaOss::GL::Drawable {
public:
  MainMenu(int width, int height);

  virtual void load(YolonaOss::GL::DrawSpecification*)             override;
  virtual void draw()                                              override;
          void addButton(std::string name, std::function<void()> onClicked);

private:
  Iyathuum::AABB<2> getAABB();
  const int buttonWidth = 500;
  const int buttonHeight = 100;  

  std::unique_ptr<YolonaOss::Widgets::ListLayout>          _layout    ;
  int                                                      _width  = 0;
  int                                                      _height = 0;
  std::vector<std::shared_ptr<YolonaOss::Widgets::Button>> _buttons   ;

};