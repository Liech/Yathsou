#pragma once

#include <memory>
#include <future>

#include "AhwassaGraphicsLib/Drawables/Drawable.h"

#include "DialogPage.h"

namespace Ahwassa {
  class Button;
}

enum class MainMenuPageStatus {
  Pending, Multiplayer, Options, SideProject
};

class MainMenuPage : public Ahwassa::Drawable {
public:
  MainMenuPage(Ahwassa::Window*);
  ~MainMenuPage();

  MainMenuPageStatus getStatus();
  virtual void       draw() override;
  
  void reset();
  void setVisible(bool vis);

private:
  void startLobbyJoin();
  void startOptions();
  void startSideProject();
  void startServer();

private:
  bool                             _serverStarted = false;
  std::shared_ptr<Ahwassa::Button> _startServerButton;
  std::future<void>                _serverThread;

  std::unique_ptr<DialogPage> _page  ;
  MainMenuPageStatus          _status = MainMenuPageStatus::Pending;
};