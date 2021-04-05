#include "HostGamePage.h"

#include <iostream>

#include "AhwassaGraphicsLib/Widgets/ListLayout.h"
#include "AhwassaGraphicsLib/Widgets/Label.h"
#include "AhwassaGraphicsLib/Core/Window.h"

HostGamePage::HostGamePage(std::shared_ptr<ClientConfiguration> configuration, Ahwassa::Window* w) : Ahwassa::Drawable(w) {
  _config = configuration;

  _page = std::make_unique<DialogPage>(w);

  _page->layout().addLabel("Host Game Page");
  auto subPort = _page->layout().addLayout();
  subPort->setHorizontal(true);
  auto portLable = subPort->addLabel("Port:");
  portLable->setLocalPosition(Iyathuum::glmAABB<2>({ 0.0f,0.0f },{ w->getWidth() / 4.0, 50.0 }));
  auto portEdit = subPort->addLineEdit(std::to_string(_config->hostPort));
  portEdit->setLocalPosition(Iyathuum::glmAABB<2>({ 0.0f,0.0f }, { w->getWidth() / 4.0, 50.0 }));
  portEdit->setValidator(Ahwassa::LineEdit::integerValidator(0, 65535));

  auto subName = _page->layout().addLayout();
  subName->setHorizontal(true);
  auto nameLable = subName->addLabel("Name:");
  nameLable->setSize({ w->getWidth() / 4.0, 50.0 });
  _gameName = subName->addLineEdit(_config->lastGameName);
  _gameName->setSize({ w->getWidth() / 4.0, 50.0 });

  _page->layout().addButton("Host", [this]() { hostGame(); });
  _page->layout().addButton("Back", [this]() { goBack(); });
  setVisible(false);
}

void HostGamePage::draw() {
  _page->draw();
}

void HostGamePage::setVisible(bool visible) {
  _page->setVisible(visible);
}

HostPageStatus HostGamePage::getStatus() {
  return _status;
}

void HostGamePage::goBack() {
  _status = HostPageStatus::Back;
}

void HostGamePage::hostGame() {
  _status = HostPageStatus::Host;
}

void HostGamePage::reset() {
  _status = HostPageStatus::Pending;
}

Vishala::CreateGameRequest HostGamePage::getResult() {
  Vishala::CreateGameRequest result;
  result.gameName = _gameName->getText();
  result.serverPort = _config->gameServerPort;
  return result;
}

