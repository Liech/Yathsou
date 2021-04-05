#include "LobbyPage.h"

#include <iostream>

#include "AhwassaGraphicsLib/Widgets/ListLayout.h"
#include "AhwassaGraphicsLib/Widgets/Label.h"
#include "AhwassaGraphicsLib/Widgets/LineEdit.h"
#include "AhwassaGraphicsLib/Core/Window.h"

LobbyPage::LobbyPage(std::shared_ptr<ClientConfiguration> configuration, std::shared_ptr<ClientState> state, Ahwassa::Window* w) : Ahwassa::Drawable(w) {
  _config = configuration;
  _state  = state;

  _page = std::make_unique<DialogPage>(w);
  _page->layout().setHorizontal(true);

  auto left = _page->layout().addLayout();
  left->addLabel ("Lobby Page");
  left->addButton("Host Game", [this]() { hostGame(); });
  left->addButton("Refresh", [this]() { refresh(); });
  left->addButton("Back", [this]() { goBack(); });

  _openGamesLayout = _page->layout().addLayout();
  _openGamesLayout->addButton("No Games Yet", []() {});
  _openGamesLayout->setMaximumSize(glm::vec2(0, w->getHeight() / 2));

  setVisible(false);
}

void LobbyPage::draw() {
  if (_state) {
    std::unique_ptr<Vishala::LobbyStateUpdate> s = _state->getLobbyStateUpdate();
    if (s)
      updateLobbyState(std::move(s));
  }
  _page->draw();
}

void LobbyPage::updateLobbyState(std::unique_ptr<Vishala::LobbyStateUpdate> update) {
  std::cout << "Lobby State update..." << std::endl;
  _openGamesLayout->clear();
  _openGamesLayout->setLocalPosition(Iyathuum::glmAABB<2>({ 0,0 }, { getWindow()->getWidth() / 4.0,getWindow()->getHeight() / 2.0 }));
  for (auto game : update->openGames) {
    std::string msg = game.name + " " + std::to_string(game.numberOfPlayers) + "/" + std::to_string(game.maxNumberOfPlayers);
    size_t gameID = game.gameID;
    _openGamesLayout->addButton(msg, [this,gameID]() {
        join(gameID);
      });
    std::cout << msg << std::endl;
  }
  if (update->openGames.size() == 0) {
    _openGamesLayout->addLabel("No Game Open");
  }
}

void LobbyPage::setVisible(bool visible) {
  _page->setVisible(visible);
}

LobbyPageStatus LobbyPage::getStatus() {
  return _status;
}

void LobbyPage::refresh() {
  std::cout << "Refresh send" << std::endl;
  _state->requestRefresh();
}

size_t LobbyPage::getGameID() {
  if (_status != LobbyPageStatus::Join)
    throw std::runtime_error("Not joinging and getGameID was called. wrong status");
  return _gameIDToJoin;
}

void LobbyPage::join(size_t gameID) {
  if (_status != LobbyPageStatus::Pending)
    throw std::runtime_error("wrong status");
  _gameIDToJoin = gameID;
  _status = LobbyPageStatus::Join;
}

void LobbyPage::goBack() {
  _status = LobbyPageStatus::Back;
}

void LobbyPage::hostGame() {
  _status = LobbyPageStatus::Host;
}

void LobbyPage::reset() {
  _status = LobbyPageStatus::Pending;
  _openGamesLayout->clear();
}


