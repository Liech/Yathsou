#pragma once

#include <memory>

#include "AhwassaGraphicsLib/Drawables/Drawable.h"

#include "DialogPage.h"
#include "ClientConfiguration.h"

enum class JoinLobbyPageStatus {
  Pending, Back, Proceed
};

class JoinLobbyPage : public Ahwassa::Drawable {
public:
  JoinLobbyPage(std::shared_ptr<ClientConfiguration> config, Ahwassa::Window*);

  virtual void draw() override;
  void setVisible(bool visible);
  void reset();

  JoinLobbyPageStatus getStatus();
private:
  void goBack();
  void saveConfig();

  std::unique_ptr<DialogPage> _page;
  
  JoinLobbyPageStatus                  _status = JoinLobbyPageStatus::Pending;
  std::shared_ptr<ClientConfiguration> _config;
};