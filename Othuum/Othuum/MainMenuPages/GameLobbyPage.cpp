#include "GameLobbyPage.h"

#include <iostream>

#include "AhwassaGraphicsLib/Widgets/ListLayout.h"
#include "AhwassaGraphicsLib/Widgets/Label.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "AhwassaGraphicsLib/Widgets/LineEdit.h"

GameLobbyPage::GameLobbyPage(std::shared_ptr<ClientConfiguration> configuration, std::shared_ptr<ClientState> state, Ahwassa::Window* w) : Ahwassa::Drawable(w) {
  _config = configuration;
  _state  = state;  
  _page = std::make_unique<DialogPage>(w);

  std::shared_ptr<Ahwassa::Label> title = std::make_shared<Ahwassa::Label>("Game Lobby Page", Iyathuum::glmAABB<2>{ {0,0},{100,50} },w);

  _page->layout().addElement(title);
  _startButton = _page->layout().addButton("Start Game", [this]() {
    startGame();
  });
  _startButton->setVisible(false);
  _participatorsLayout = _page->layout().addLayout();
  _participatorsLayout->addLabel("You are alone");
  _page->layout().addButton("Back", [this]() { goBack(); });
  setVisible(false);
}
 
void GameLobbyPage::update(){
  if (_state) {
    std::unique_ptr<Vishala::GameLobbyStateUpdate> s = _state->getGameLobbyStateUpdate();
    if (s)
      updateGameLobbyState(std::move(s));
  }
}

void GameLobbyPage::draw() {
  _page->draw();
}

void GameLobbyPage::updateGameLobbyState(std::unique_ptr<Vishala::GameLobbyStateUpdate> update){
  _participatorsLayout->clear();
  for (auto p : update->currentPlayers) {
    _participatorsLayout->addLabel(std::to_string(p.lobbyIdentification.id) + ": " + p.lobbyIdentification.name);
  }
  if (update->gameStart)
    _status = GameLobbyPageStatus::StartGame;
  _port = update->gameServerPort;
  _ip = update->gameServerIP;
}

void GameLobbyPage::setVisible(bool visible) {
  _page->setVisible(visible);
}

GameLobbyPageStatus GameLobbyPage::getStatus() {
  return _status;
}

void GameLobbyPage::goBack() {
  _status = GameLobbyPageStatus::Back;
}

void GameLobbyPage::startGame() {
  _status = GameLobbyPageStatus::WaitForStartGame;
  std::cout << "GameLobbyPage::startGame" << std::endl;
}

void GameLobbyPage::reset() {
  _status = GameLobbyPageStatus::Pending;  
}

void GameLobbyPage::start() {
  _startButton->setVisible(_state->getStatus() == ClientStateStatus::Host);
}

std::string GameLobbyPage::getGameIP() {
  return _ip;
}

int GameLobbyPage::getGamePort() {
  return _port;
}
