#pragma once

#include <memory>

#include "ClientConfiguration.h"
#include "VishalaNetworkLib/Protocoll/Client/LobbyConnector.h"
#include "VishalaNetworkLib/Protocoll/Client/LobbyClient.h"
#include "VishalaNetworkLib/Serializable/LobbyStateUpdate.h"
#include "VishalaNetworkLib/Serializable/GameLobbyStateUpdate.h"

enum class ClientStateStatus {
  Nothing, LobbyConnector, Lobby, HostLoading, Host, JoinLoading, Joined
};

class ClientState {
public:
  ClientState(std::shared_ptr<ClientConfiguration> config);
  
  ClientStateStatus getStatus();

  void update();
  void connectToLobby();
  void stop();
  void closeGame();
  void host(Vishala::CreateGameRequest options);
  void join(size_t id);
  void requestRefresh();
  void startGame();

  std::unique_ptr<Vishala::LobbyStateUpdate>     getLobbyStateUpdate();
  std::unique_ptr<Vishala::GameLobbyStateUpdate> getGameLobbyStateUpdate();

private:
  ClientStateStatus _status = ClientStateStatus::Nothing;

  std::shared_ptr<ClientConfiguration>             _config                    ;
  std::unique_ptr<Vishala::Client::LobbyConnector> _lobbyConnector   = nullptr;
  std::unique_ptr<Vishala::Client::LobbyClient>    _lobbyClient      = nullptr;
};