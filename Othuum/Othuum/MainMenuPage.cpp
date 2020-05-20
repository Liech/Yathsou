#include "MainMenuPage.h"

#include <iostream>

#include "YolonaOss/OpenGL/Window.h"

MainMenuPage::MainMenuPage(){
}

void MainMenuPage::load(YolonaOss::GL::DrawSpecification* spec) {
  _page = std::make_unique<DialogPage>(spec->width, spec->height);
  _page->addButton("Multiplayer", [this]() { startLobbyJoin(); });
  _page->addButton("Quit"       , [spec]() { spec->getWindow()->close(); });
}

void MainMenuPage::startLobbyJoin() {
  _status = MainMenuPageStatus::Multiplayer;
}

MainMenuPageStatus MainMenuPage::getStatus() {
  return _status;
}

void MainMenuPage::draw() {
  _page->draw();
}

void MainMenuPage::setVisible(bool vis) {
  _page->setVisible(vis);
}

void MainMenuPage::reset() {
  _status = MainMenuPageStatus::Pending;
}