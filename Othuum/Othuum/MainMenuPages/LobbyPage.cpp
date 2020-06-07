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

  _page->layout().addLabel ("Lobby Page");
  _page->layout().addButton("Host Game", [this]() { hostGame(); });
  _page->layout().addButton("Refresh", [this]() { refresh(); });
  _page->layout().addButton("Back", [this]() { goBack(); });
  setVisible(false);
}

void LobbyPage::draw() {
  if (_state) {
    auto s = _state->getLobbyStateUpdate();
    if (s) {
      std::cout << "LOBBY STATE UPDATE" << std::endl;
    }
  }
  _page->draw();
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

void LobbyPage::goBack() {
  _status = LobbyPageStatus::Back;
}

void LobbyPage::hostGame() {
  _status = LobbyPageStatus::Host;
}

void LobbyPage::reset() {
  _status = LobbyPageStatus::Pending;
}


