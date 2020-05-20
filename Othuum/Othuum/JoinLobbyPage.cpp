#include "JoinLobbyPage.h"

#include <iostream>


void JoinLobbyPage::load(YolonaOss::GL::DrawSpecification* spec) {
  _page = std::make_unique<DialogPage>(spec->width, spec->height);
  _page->addButton("LOBBY", []() {std::cout << "Moin" << std::endl; });
  _page->addButton("Back", [this]() { goBack(); });
  setVisible(false);
}

void JoinLobbyPage::draw() {
  _page->draw();
}

void JoinLobbyPage::setVisible(bool visible) {
  _page->setVisible(visible);
}

JoinLobbyPageStatus JoinLobbyPage::getStatus() {
  return _status;
}

void JoinLobbyPage::goBack() {
  _status = JoinLobbyPageStatus::Back;
}

void JoinLobbyPage::reset() {
  _status = JoinLobbyPageStatus::Pending;
}
