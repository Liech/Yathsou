#include "LobbyLoadingPage.h"

#include <iostream>

#include "AhwassaGraphicsLib/Widgets/ListLayout.h"
#include "AhwassaGraphicsLib/Widgets/Label.h"
#include "AhwassaGraphicsLib/Widgets/LineEdit.h"
#include "AhwassaGraphicsLib/Core/Window.h"

LobbyLoadingPage::LobbyLoadingPage(std::shared_ptr<ClientConfiguration> configuration, std::shared_ptr<ClientState> state, Ahwassa::Window* w) : Ahwassa::Drawable(w) {
  _config = configuration;
  _state  = state;

  _page = std::make_unique<DialogPage>(w);

  _page->layout().addLabel("Lobby Loading Page");
  
  _page->layout().addButton("Cancel", [this]() { goBack(); });
  setVisible(false);
}

void LobbyLoadingPage::update() {
  if (_state->getStatus() == ClientStateStatus::Nothing) {
    _status = LobbyLoadingPageStatus::Error;
    return;
  }
  else if (_state->getStatus() == ClientStateStatus::Lobby) {
    finish();
    return;
  }
}

void LobbyLoadingPage::draw() {
  _page->draw();
}

void LobbyLoadingPage::setVisible(bool visible) {
  _page->setVisible(visible);
}

LobbyLoadingPageStatus LobbyLoadingPage::getStatus() {
  return _status;
}

void LobbyLoadingPage::finish() {
  _status = LobbyLoadingPageStatus::Proceed;
}


void LobbyLoadingPage::goBack() {
  _status = LobbyLoadingPageStatus::Back;
}

void LobbyLoadingPage::reset() {
  _status = LobbyLoadingPageStatus::Pending;
}

void LobbyLoadingPage::start() {
  std::cout << "Connection to lobby starts" << std::endl;
  _state->connectToLobby();
}