#pragma once

#include <memory>

#include "YolonaOss/OpenGL/Drawable.h"

#include "DialogPage.h"
#include "ClientConfiguration.h"
#include "ClientState.h"

enum class GameLobbyPageStatus {
  Pending, Back
};

class GameLobbyPage : public YolonaOss::GL::Drawable {
public:
  GameLobbyPage(std::shared_ptr<ClientConfiguration> config, std::shared_ptr<ClientState> state);

  virtual void draw()                                  override;
  virtual void load(YolonaOss::GL::DrawSpecification*) override;
  void setVisible(bool visible);
  void reset();

  GameLobbyPageStatus getStatus();
private:
  void goBack();

  std::unique_ptr<DialogPage> _page;
  
  GameLobbyPageStatus                      _status = GameLobbyPageStatus::Pending;
  std::shared_ptr<ClientConfiguration> _config;
  std::shared_ptr<ClientState        > _state;
};