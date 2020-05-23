#include "JoinLobbyPage.h"

#include <iostream>

#include "YolonaOss/Drawables/Widgets/ListLayout.h"
#include "YolonaOss/Drawables/Widgets/Label.h"
#include "YolonaOss/Drawables/Widgets/LineEdit.h"

JoinLobbyPage::JoinLobbyPage(std::shared_ptr<ClientConfiguration> configuration) {
  _config = configuration;
}

void JoinLobbyPage::load(YolonaOss::GL::DrawSpecification* spec) {
  _page = std::make_unique<DialogPage>(spec->width, spec->height);

  _page->layout().addLabel("Join Lobby Page");
  auto sub = _page->layout().addLayout();  
  sub->setHorizontal(true);
  auto but = sub->addLabel("Nickname:");
  but->getPosition().setSize(std::array<double,2>{ spec->width / 4.0,50.0 });
  auto but2 = sub->addLineEdit(_config->playerName);
  but2->getPosition().setSize(std::array<double, 2>{ spec->width / 4.0,50.0 });
  but2->setEditFinishedCallback([this](std::string s) {
    _config->playerName = s;
    saveConfig();
  });

  _page->layout().addButton("Join Lobby", [this]() {
    _status = JoinLobbyPageStatus::Proceed;
  });
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

void JoinLobbyPage::saveConfig() {
  _config->toJsonFile("ClientConfiguration.json");
}

