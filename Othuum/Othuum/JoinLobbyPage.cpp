#include "JoinLobbyPage.h"

#include <iostream>

#include "YolonaOss/Drawables/Widgets/ListLayout.h"

JoinLobbyPage::JoinLobbyPage(std::shared_ptr<ClientConfiguration> configuration) {
  _config = configuration;
}

void JoinLobbyPage::load(YolonaOss::GL::DrawSpecification* spec) {
  _page = std::make_unique<DialogPage>(spec->width, spec->height);

  auto sub = _page->layout().addLayout();  

  sub->setHorizontal(true);
  //sub->addLabel("Name:");
  auto but = sub->addButton("emaN", []() {std::cout << "HUHU" << std::endl; });
  but->getPosition().setSize({ 250,50 });
  auto but2 = sub->addButton("eeeemaN", []() {std::cout << "HUHU" << std::endl; });
  but2->getPosition().setSize({ 250,50 });

  _page->layout().addButton("LOBBY", []() {std::cout << "Moin" << std::endl; });
  _page->layout().addButton("Back", [this]() { goBack(); });
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
