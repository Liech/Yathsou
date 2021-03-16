#pragma once

#include <memory>

#include "YolonaOss/OpenGL/Drawable.h"

#include "DialogPage.h"
#include "ClientConfiguration.h"
#include "ClientState.h"
#include "VishalaNetworkLib/Serializable/GameLobbyStateUpdate.h"

enum class GameLobbyPageStatus {
  Pending, Back, WaitForStartGame, StartGame
};

class GameLobbyPage : public YolonaOss::GL::Drawable {
public:
  GameLobbyPage(std::shared_ptr<ClientConfiguration> config, std::shared_ptr<ClientState> state);

  void update();
  virtual void draw()                                  override;
  virtual void load(YolonaOss::GL::DrawSpecification*) override;
  void setVisible(bool visible);
  void reset();
  void start();

  GameLobbyPageStatus getStatus();
private:
  void goBack();
  void startGame();
  void updateGameLobbyState(std::unique_ptr<Vishala::GameLobbyStateUpdate> update);
  std::unique_ptr<DialogPage> _page;
  
  GameLobbyPageStatus                      _status = GameLobbyPageStatus::Pending;
  std::shared_ptr<ClientConfiguration> _config;
  std::shared_ptr<ClientState        > _state; 
  std::shared_ptr<YolonaOss::Widgets::ListLayout> _participatorsLayout;
  std::shared_ptr<YolonaOss::Widgets::Button>     _startButton;
};