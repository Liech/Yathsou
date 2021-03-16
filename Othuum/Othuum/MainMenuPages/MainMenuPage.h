#pragma once

#include <memory>
#include <future>

#include "YolonaOss/OpenGL/Drawable.h"

#include "DialogPage.h"

namespace YolonaOss {
  namespace GL {
    class DrawSpecification;
  }
  namespace Widgets
  {
    class Button;
  }
}

enum class MainMenuPageStatus {
  Pending, Multiplayer, Options, SideProject
};

class MainMenuPage : public YolonaOss::GL::Drawable {
public:
  MainMenuPage();
  ~MainMenuPage();

  MainMenuPageStatus getStatus();
  virtual void       draw()                                  override;
  virtual void       load(YolonaOss::GL::DrawSpecification*) override;
  
  void reset();
  void setVisible(bool vis);

private:
  void startLobbyJoin();
  void startOptions();
  void startSideProject();
  void startServer();

private:
  bool                                        _serverStarted = false;
  std::shared_ptr<YolonaOss::Widgets::Button> _startServerButton;
  std::future<void>                           _serverThread;

  std::unique_ptr<DialogPage> _page  ;
  MainMenuPageStatus          _status = MainMenuPageStatus::Pending;
};