#include "MainMenuPage.h"

#include <iostream>

#include "YolonaOss/OpenGL/Window.h"
#include "YolonaOss/Drawables/Widgets/ListLayout.h"

MainMenuPage::MainMenuPage(){
}

void MainMenuPage::load(YolonaOss::GL::DrawSpecification* spec) {
  _page = std::make_unique<DialogPage>(spec->width, spec->height);
  
  _page->layout().addLabel("Main Menu Page");
  _page->layout().addButton("Multiplayer", [this]() { startLobbyJoin();           });
  _page->layout().addButton("Options"    , [this]() { startOptions();             });
  _page->layout().addButton("ScrollDown", [this]() { _page->layout().setCurrentScroll(_page->layout().getCurrentScroll() + 1);  });
  _page->layout().addButton("Quit"       , [spec]() { spec->getWindow()->close(); });
  _page->layout().setMaximumSize(glm::vec2(1000, 170));
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

void MainMenuPage::startOptions() {
  _status = MainMenuPageStatus::Options;
}