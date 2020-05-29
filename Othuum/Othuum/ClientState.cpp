#include "ClientState.h"

ClientState::ClientState(std::shared_ptr<ClientConfiguration> config) {
  _config = config;
}

ClientStateStatus ClientState::getStatus() {
  return _status;
}

void ClientState::connectToLobby() {
  if (_status != ClientStateStatus::Nothing)
    throw std::runtime_error("Wrong status in ClientState::connectToLobby");
  _status = ClientStateStatus::LobbyConnector;
  _lobbyConnector = std::make_unique<Vishala::Client::LobbyConnector>(_config->lobbyServerMyPort, _config->lobbyServerAdress,_config->lobbyServerTheirPort);
}

void ClientState::update() {
  if (_lobbyConnector && _status == ClientStateStatus::LobbyConnector) {
    if (_lobbyConnector->getStatus() == Vishala::Client::LobbyConnectorStatus::Waiting)
      _lobbyConnector->update();
    else if (_lobbyConnector->getStatus() == Vishala::Client::LobbyConnectorStatus::ConnectionEstablished) {
      _status = ClientStateStatus::Lobby;
      _lobbyClient = std::make_unique<Vishala::Client::LobbyClient>(std::move(_lobbyConnector->extractConnection()));
      _lobbyConnector = nullptr;
    }
    else if (_lobbyConnector->getStatus() == Vishala::Client::LobbyConnectorStatus::ConnectionFailed) {
      stop();
    }
  }
  if (_lobbyClient && _status == ClientStateStatus::Lobby) {
    _lobbyClient->update();
  }
}

void ClientState::stop() {
  _status = ClientStateStatus::Nothing;
  if (_lobbyConnector)
    _lobbyConnector->stop();
  if (_lobbyClient)
    _lobbyClient->stop();
  _lobbyConnector = nullptr;
  _lobbyClient    = nullptr;
}

void ClientState::host(Vishala::CreateGameRequest options) {
  if (_status == ClientStateStatus::LobbyConnector || _status == ClientStateStatus::Nothing)
    throw std::runtime_error("Wrong status");
  _status = ClientStateStatus::HostLoading;
  _lobbyClient->hostGame(options);
}