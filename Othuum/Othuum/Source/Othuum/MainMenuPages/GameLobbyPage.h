#pragma once

#include <memory>

#include "AhwassaGraphicsLib/Drawables/Drawable.h"

#include "DialogPage.h"
#include "ClientConfiguration.h"
#include "ClientState.h"
#include "VishalaNetworkLib/Serializable/GameLobbyStateUpdate.h"


namespace Ahwassa {
  class Button;
}

enum class GameLobbyPageStatus {
  Pending, Back, WaitForStartGame, StartGame
};

class GameLobbyPage : public Ahwassa::Drawable {
public:
  GameLobbyPage(std::shared_ptr<ClientConfiguration> config, std::shared_ptr<ClientState> state, Ahwassa::Window*);

  void         update();
  virtual void draw()                                  override;
  void         setVisible(bool visible);
  void         reset();
  void         start();

  std::string getGameIP();
  int         getGamePort();

  GameLobbyPageStatus getStatus();
private:
  void goBack();
  void startGame();
  void updateGameLobbyState(std::unique_ptr<Vishala::GameLobbyStateUpdate> update);
  std::unique_ptr<DialogPage> _page;
  
  GameLobbyPageStatus                      _status = GameLobbyPageStatus::Pending;
  std::shared_ptr<ClientConfiguration> _config;
  std::shared_ptr<ClientState        > _state; 
  std::shared_ptr<Ahwassa::ListLayout> _participatorsLayout;
  std::shared_ptr<Ahwassa::Button>     _startButton;

  int         _port;
  std::string _ip;
};