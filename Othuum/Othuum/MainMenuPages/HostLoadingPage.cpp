#include "HostLoadingPage.h"

#include <iostream>

#include "AhwassaGraphicsLib/Widgets/ListLayout.h"
#include "AhwassaGraphicsLib/Widgets/Label.h"
#include "AhwassaGraphicsLib/Widgets/LineEdit.h"
#include "AhwassaGraphicsLib/Core/Window.h"

#include "VishalaNetworkLib/Serializable/Client2LobbyMessage.h"

HostLoadingPage::HostLoadingPage(std::shared_ptr<ClientConfiguration> configuration, std::shared_ptr<ClientState> state, Ahwassa::Window* w) : Ahwassa::Drawable(w) {
  _config = configuration;
  _state  = state;

  _page = std::make_unique<DialogPage>(w);

  _page->layout().addLabel("Host Loading Page");
  
  _page->layout().addButton("Cancel", [this]() { goBack(); });
  setVisible(false);
}

void HostLoadingPage::update() {
  if (_state->getStatus() == ClientStateStatus::Lobby)
    _status = HostLoadingPageStatus::Error;
  else if (_state->getStatus() == ClientStateStatus::Host)
    finish();
}

void HostLoadingPage::draw() {
  _page->draw();
}

void HostLoadingPage::setVisible(bool visible) {
  _page->setVisible(visible);
}

HostLoadingPageStatus HostLoadingPage::getStatus() {
  return _status;
}

void HostLoadingPage::finish() {
  _status = HostLoadingPageStatus::Proceed;
}


void HostLoadingPage::goBack() {
  _status = HostLoadingPageStatus::Back;
}

void HostLoadingPage::reset() {
  _status = HostLoadingPageStatus::Pending;
}

void HostLoadingPage::start(Vishala::CreateGameRequest request) {
  std::cout << "host game starts" << std::endl;

  _state->host(request);
  
}