#include "ErrorPage.h"

#include <iostream>

#include "YolonaOss/Drawables/Widgets/ListLayout.h"
#include "YolonaOss/Drawables/Widgets/LineEdit.h"

ErrorPage::ErrorPage(std::shared_ptr<ClientConfiguration> configuration) {
  _config = configuration;
}

void ErrorPage::load(YolonaOss::GL::DrawSpecification* spec) {
  _page = std::make_unique<DialogPage>(spec->width, spec->height);

  _title= _page->layout().addLabel("ERROR");
  _desc = _page->layout().addLabel("Description");
  _page->layout().addButton("OK", [this]() { goBack(); });
  setVisible(false);
}

void ErrorPage::draw() {
  _page->draw();
}

void ErrorPage::setVisible(bool visible) {
  _page->setVisible(visible);
}

ErrorPageStatus ErrorPage::getStatus() {
  return _status;
}

void ErrorPage::goBack() {
  _status = ErrorPageStatus::Back;
}

void ErrorPage::reset() {
  _status = ErrorPageStatus::Pending;
  setMessage("Unkown Error");
}

void ErrorPage::setMessage(std::string desc, std::string title) {
  _desc->setText(desc);
  _title->setText(title);
}


