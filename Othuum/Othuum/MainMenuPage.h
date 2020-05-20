#pragma once

#include <memory>

#include "YolonaOss/OpenGL/Drawable.h"

#include "DialogPage.h"

namespace YolonaOss {
  namespace GL {
    class DrawSpecification;
  }
}

enum class MainMenuPageStatus {
  Pending, Multiplayer
};

class MainMenuPage : public YolonaOss::GL::Drawable {
public:
  MainMenuPage();

  MainMenuPageStatus getStatus();
  virtual void       draw()                                  override;
  virtual void       load(YolonaOss::GL::DrawSpecification*) override;
  
  void reset();
  void setVisible(bool vis);

private:
  void startLobbyJoin();

private:
  std::unique_ptr<DialogPage> _page  ;
  MainMenuPageStatus          _status = MainMenuPageStatus::Pending;
};