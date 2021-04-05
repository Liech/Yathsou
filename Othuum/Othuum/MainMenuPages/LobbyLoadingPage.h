#pragma once

#include <memory>

#include "AhwassaGraphicsLib/Drawables/Drawable.h"

#include "DialogPage.h"
#include "ClientConfiguration.h"
#include "ClientState.h"

enum class LobbyLoadingPageStatus {
  Pending, Back, Proceed, Error
};

class LobbyLoadingPage : public Ahwassa::Drawable {
public:
  LobbyLoadingPage(std::shared_ptr<ClientConfiguration> config, std::shared_ptr<ClientState> state, Ahwassa::Window*);

  virtual void draw() override;
  void setVisible(bool visible);
  void reset();
  void start();
  void update();

  LobbyLoadingPageStatus getStatus();
private:
  void goBack();
  void finish();

  std::unique_ptr<DialogPage> _page;
  
  LobbyLoadingPageStatus               _status = LobbyLoadingPageStatus::Pending;
  std::shared_ptr<ClientConfiguration> _config;
  std::shared_ptr<ClientState        > _state ;
};