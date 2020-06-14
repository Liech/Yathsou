#include "LobbyPage.h"

#include <iostream>

#include "YolonaOss/Drawables/Widgets/ListLayout.h"
#include "YolonaOss/Drawables/Widgets/Label.h"
#include "YolonaOss/Drawables/Widgets/LineEdit.h"

LobbyPage::LobbyPage(std::shared_ptr<ClientConfiguration> configuration, std::shared_ptr<ClientState> state) {
  _config = configuration;
  _state  = state;
}

void LobbyPage::load(YolonaOss::GL::DrawSpecification* spec) {
  _page = std::make_unique<DialogPage>(spec->width, spec->height);
  _page->layout().setHorizontal(true);

  auto left = _page->layout().addLayout();
  left->addLabel ("Lobby Page");
  left->addButton("Host Game", [this]() { hostGame(); });
  left->addButton("Refresh", [this]() { refresh(); });
  left->addButton("Back", [this]() { goBack(); });

  _openGamesLayout = _page->layout().addLayout();
  _openGamesLayout->addButton("No Games Yet", []() {});
  _openGamesLayout->setMaximumSize(glm::vec2(0, spec->height / 2));

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
  for (auto game : update->openGames) {
    std::string msg = game.name + " " + std::to_string(game.numberOfPlayers) + "/" + std::to_string(game.maxNumberOfPlayers);
    size_t gameID = game.gameID;
    _openGamesLayout->addButton(msg, [this,gameID]() {
        join(gameID);      
      });
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
}


