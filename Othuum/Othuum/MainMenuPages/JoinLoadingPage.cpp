#include "JoinLoadingPage.h"

#include <iostream>

#include "YolonaOss/Drawables/Widgets/ListLayout.h"
#include "YolonaOss/Drawables/Widgets/Label.h"
#include "YolonaOss/Drawables/Widgets/LineEdit.h"

#include "VishalaNetworkLib/Serializable/Client2LobbyMessage.h"

JoinLoadingPage::JoinLoadingPage(std::shared_ptr<ClientConfiguration> configuration, std::shared_ptr<ClientState> state) {
  _config = configuration;
  _state  = state;
}

void JoinLoadingPage::load(YolonaOss::GL::DrawSpecification* spec) {
  _page = std::make_unique<DialogPage>(spec->width, spec->height);

  _page->layout().addLabel("Join Loading Page");
  
  _page->layout().addButton("Cancel", [this]() { goBack(); });
  setVisible(false);
}

void JoinLoadingPage::update() {
  if (_state->getStatus() == ClientStateStatus::Lobby)
    _status = JoinLoadingPageStatus::Error;
  else if (_state->getStatus() == ClientStateStatus::Joined)
    finish();
}

void JoinLoadingPage::draw() {
  _page->draw();
}

void JoinLoadingPage::setVisible(bool visible) {
  _page->setVisible(visible);
}

JoinLoadingPageStatus JoinLoadingPage::getStatus() {
  return _status;
}

void JoinLoadingPage::finish() {
  _status = JoinLoadingPageStatus::Proceed;
}


void JoinLoadingPage::goBack() {
  _status = JoinLoadingPageStatus::Back;
}

void JoinLoadingPage::reset() {
  _status = JoinLoadingPageStatus::Pending;
}

void JoinLoadingPage::start(size_t gameID) {
  std::cout << "join game starts "<< gameID << std::endl;
  _state->join(gameID);
}