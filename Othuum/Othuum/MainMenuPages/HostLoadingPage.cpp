#include "HostLoadingPage.h"

#include <iostream>

#include "YolonaOss/Drawables/Widgets/ListLayout.h"
#include "YolonaOss/Drawables/Widgets/Label.h"
#include "YolonaOss/Drawables/Widgets/LineEdit.h"

#include "VishalaNetworkLib/Serializable/Client2LobbyMessage.h"

HostLoadingPage::HostLoadingPage(std::shared_ptr<ClientConfiguration> configuration, std::shared_ptr<ClientState> state) {
  _config = configuration;
  _state  = state;
}

void HostLoadingPage::load(YolonaOss::GL::DrawSpecification* spec) {
  _page = std::make_unique<DialogPage>(spec->width, spec->height);

  _page->layout().addLabel("Host Loading Page");
  
  _page->layout().addButton("Cancel", [this]() { goBack(); });
  setVisible(false);
}

void HostLoadingPage::update() {
  if (_state->getStatus() == ClientStateStatus::Lobby) {
    _status = HostLoadingPageStatus::Error;
    return;
  }
  else if (_state->getStatus() == ClientStateStatus::Host) {
    finish();
    return;
  }
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