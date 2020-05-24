#include "LobbyLoadingPage.h"

#include <iostream>

#include "YolonaOss/Drawables/Widgets/ListLayout.h"
#include "YolonaOss/Drawables/Widgets/Label.h"
#include "YolonaOss/Drawables/Widgets/LineEdit.h"

LobbyLoadingPage::LobbyLoadingPage(std::shared_ptr<ClientConfiguration> configuration) {
  _config = configuration;
}

void LobbyLoadingPage::load(YolonaOss::GL::DrawSpecification* spec) {
  _page = std::make_unique<DialogPage>(spec->width, spec->height);

  _page->layout().addLabel("Lobby Loading Page");
  
  _page->layout().addButton("Cancel", [this]() { goBack(); });
  setVisible(false);
}

void LobbyLoadingPage::draw() {
  _page->draw();
}

void LobbyLoadingPage::setVisible(bool visible) {
  _page->setVisible(visible);
}

LobbyLoadingPageStatus LobbyLoadingPage::getStatus() {
  return _status;
}

void LobbyLoadingPage::goBack() {
  _status = LobbyLoadingPageStatus::Back;
}

void LobbyLoadingPage::reset() {
  _status = LobbyLoadingPageStatus::Pending;
}

