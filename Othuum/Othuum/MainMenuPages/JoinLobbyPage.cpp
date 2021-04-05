#include "JoinLobbyPage.h"

#include <iostream>

#include "AhwassaGraphicsLib/Widgets/ListLayout.h"
#include "AhwassaGraphicsLib/Widgets/Label.h"
#include "AhwassaGraphicsLib/Widgets/LineEdit.h"
#include "AhwassaGraphicsLib/Core/Window.h"

JoinLobbyPage::JoinLobbyPage(std::shared_ptr<ClientConfiguration> configuration, Ahwassa::Window* w) : Ahwassa::Drawable(w) {
  _config = configuration;

  _page = std::make_unique<DialogPage>(w);

  _page->layout().addLabel("Join Lobby Page");


  auto sub = _page->layout().addLayout();  
  sub->setHorizontal(true);
  auto but = sub->addLabel("Nickname:");
  but->setSize({ w->getWidth()  / 4.0,50.0 });
  auto but2 = sub->addLineEdit(_config->playerName);
  but2->setSize({ w->getWidth() / 4.0,50.0 });
  but2->setEditFinishedCallback([this](std::string s) {
    _config->playerName = s;
    saveConfig();
  });

  auto subAdress = _page->layout().addLayout();
  subAdress->setHorizontal(true);
  auto adressLabel = subAdress->addLabel("Server:");
  adressLabel->setSize({ w->getWidth() / 4.0, 50.0 });
  auto adressLine = subAdress->addLineEdit(_config->lobbyServerAdress);
  adressLine->setSize({ w->getWidth() / 4.0, 50.0 });
  adressLine->setEditFinishedCallback([this](std::string s) {
    _config->lobbyServerAdress = s;
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

