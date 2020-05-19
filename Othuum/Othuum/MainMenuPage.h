#pragma once

#include <memory>

#include "YolonaOss/OpenGL/Drawable.h"

class DialogPage;

namespace YolonaOss {
  namespace GL {
    class DrawSpecification;
  }
}

class MainMenuPage : public YolonaOss::GL::Drawable {
public:
  MainMenuPage(int resolutionX, int resolutionY);

  virtual void draw()                   override;
  virtual void load(YolonaOss::GL::DrawSpecification*) override {};


private:
  std::unique_ptr<DialogPage> _page;

};