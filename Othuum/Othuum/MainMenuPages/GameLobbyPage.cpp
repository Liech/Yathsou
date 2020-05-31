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
  _page->layout().addLabel("You are alone");
  _page->layout().addButton("Back", [this]() { goBack(); });
  setVisible(false);
}

void GameLobbyPage::draw() {
  _page->draw();
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

void GameLobbyPage::reset() {
  _status = GameLobbyPageStatus::Pending;
}


