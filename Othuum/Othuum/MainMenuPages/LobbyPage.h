#pragma once

#include <memory>

#include "YolonaOss/OpenGL/Drawable.h"

#include "DialogPage.h"
#include "ClientConfiguration.h"
#include "ClientState.h"

enum class LobbyPageStatus {
  Pending, Back, Host, Join
};

class LobbyPage : public YolonaOss::GL::Drawable {
public:
  LobbyPage(std::shared_ptr<ClientConfiguration> config, std::shared_ptr<ClientState> state);

  virtual void draw()                                  override;
  virtual void load(YolonaOss::GL::DrawSpecification*) override;
  void setVisible(bool visible);
  void reset();

  size_t getGameID();

  LobbyPageStatus getStatus();
private:
  void goBack  ();
  void hostGame();
  void refresh ();
  void join    (size_t gameID);
  void updateLobbyState(std::unique_ptr<Vishala::LobbyStateUpdate>);

  std::unique_ptr<DialogPage>                     _page;
  std::shared_ptr<YolonaOss::Widgets::ListLayout> _openGamesLayout;
  
  size_t _gameIDToJoin = 0;

  LobbyPageStatus                      _status = LobbyPageStatus::Pending;
  std::shared_ptr<ClientConfiguration> _config;
  std::shared_ptr<ClientState        > _state;
};