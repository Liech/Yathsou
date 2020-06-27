#include "GameLobbyPage.h"

#include <iostream>

#include "YolonaOss/Drawables/Widgets/ListLayout.h"
#include "YolonaOss/Drawables/Widgets/Label.h"
#include "YolonaOss/Drawables/Widgets/LineEdit.h"

GameLobbyPage::GameLobbyPage(std::shared_ptr<ClientConfiguration> configuration, std::shared_ptr<ClientState> state) {
  _config = configuration;
  _state  = state;
}

void GameLobbyPage::load(YolonaOss::GL::DrawSpecification* spec) {
  _page = std::make_unique<DialogPage>(spec->width, spec->height);

  _page->layout().addLabel("Game Lobby Page");
  _startButton = _page->layout().addButton("Start Game", [this]() {
    startGame();
    });
  _startButton->setVisible(false);
  _participatorsLayout = _page->layout().addLayout();
  _participatorsLayout->addLabel("You are alone");
  _page->layout().addButton("Back", [this]() { goBack(); });
  setVisible(false);
}
 
void GameLobbyPage::draw() {
  if (_state) {
    std::unique_ptr<Vishala::GameLobbyStateUpdate> s = _state->getGameLobbyStateUpdate();
    if (s)
      updateGameLobbyState(std::move(s));
  }

  _page->draw();
}

void GameLobbyPage::updateGameLobbyState(std::unique_ptr<Vishala::GameLobbyStateUpdate> update){
  _participatorsLayout->clear();
  for (auto p : update->currentPlayers) {
    _participatorsLayout->addLabel(std::to_string(p.lobbyIdentification.id) + ": " + p.lobbyIdentification.name);
  }
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
  _status = GameLobbyPageStatus::StartGame;
}

void GameLobbyPage::reset() {
  _status = GameLobbyPageStatus::Pending;  
}

void GameLobbyPage::start() {
  _startButton->setVisible(_state->getStatus() == ClientStateStatus::Host);
}


