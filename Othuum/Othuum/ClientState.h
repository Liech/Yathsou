#pragma once

#include <memory>

#include "ClientConfiguration.h"
#include "VishalaNetworkLib/Protocoll/Client/LobbyConnector.h"
#include "VishalaNetworkLib/Protocoll/Client/LobbyClient.h"
#include "VishalaNetworkLib/Serializable/LobbyStateUpdate.h"

enum class ClientStateStatus {
  Nothing, LobbyConnector, Lobby, HostLoading, Host
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
  void requestRefresh();

  std::unique_ptr<Vishala::LobbyStateUpdate> getLobbyStateUpdate();

private:
  ClientStateStatus _status = ClientStateStatus::Nothing;

  std::shared_ptr<ClientConfiguration>             _config                    ;
  std::unique_ptr<Vishala::Client::LobbyConnector> _lobbyConnector   = nullptr;
  std::unique_ptr<Vishala::Client::LobbyClient>    _lobbyClient      = nullptr;
};