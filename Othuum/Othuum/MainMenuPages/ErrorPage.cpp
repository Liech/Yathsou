#include "ErrorPage.h"

#include <iostream>

#include "AhwassaGraphicsLib/Widgets/ListLayout.h"
#include "AhwassaGraphicsLib/Widgets/LineEdit.h"

ErrorPage::ErrorPage(std::shared_ptr<ClientConfiguration> configuration, Ahwassa::Window* w) : Ahwassa::Drawable(w) {
  _config = configuration;
  _page = std::make_unique<DialogPage>(w);

  _title = std::make_shared<Ahwassa::Label>("ERROR", Iyathuum::glmAABB<2>{ {0, 0}, { 100,50 } }, w);
  _page->layout().addElement(_title);
  _desc = std::make_shared<Ahwassa::Label>("Description", Iyathuum::glmAABB<2>{ {0, 0}, { 100,50 } }, w);
  _page->layout().addElement(_desc);
  _page->layout().addButton("OK", [this]() { goBack(); }, Iyathuum::glmAABB<2>({ 0, 0 }, { 100,50 }));
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


