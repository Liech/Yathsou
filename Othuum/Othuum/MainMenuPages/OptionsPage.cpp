#include "OptionsPage.h"

#include <iostream>

#include "AhwassaGraphicsLib/Widgets/ListLayout.h"
#include "AhwassaGraphicsLib/Widgets/Label.h"
#include "AhwassaGraphicsLib/Widgets/LineEdit.h"
#include "AhwassaGraphicsLib/Core/Window.h"

OptionsPage::OptionsPage(std::shared_ptr<ClientConfiguration> configuration, Ahwassa::Window* w) : Ahwassa::Drawable(w) {
  _config = configuration;

  _page = std::make_unique<DialogPage>(w);
  _page->layout().addLabel("Options Page");
  
  auto subResolution = _page->layout().addLayout();
  subResolution->setHorizontal(true);
  auto resolutionLable = subResolution->addLabel("Resolution:");
  resolutionLable->setSize({ w->getWidth() / 6.0, 50.0 });
  auto resoXEdit = subResolution->addLineEdit(std::to_string(_config->resolution[0]));
  resoXEdit->setSize({ w->getWidth() / 6.0, 50.0 });
  resoXEdit->setValidator(Ahwassa::LineEdit::integerValidator(0, 5000));
  resoXEdit->setEditFinishedCallback([this](std::string content) 
    { 
      _config->resolution[0] = std::atoi(content.c_str()); 
      _requiresRestart = true;
    });
  auto resoYEdit = subResolution->addLineEdit(std::to_string(_config->resolution[1]));
  resoYEdit->setSize({ w->getWidth() / 6.0, 50.0 });
  resoYEdit->setValidator(Ahwassa::LineEdit::integerValidator(0, 5000));
  resoYEdit->setEditFinishedCallback([this](std::string content) 
    { 
      _config->resolution[1] = std::atoi(content.c_str()); 
      _requiresRestart = true;
    });

  auto subPort = _page->layout().addLayout();
  subPort->setHorizontal(true);
  auto portLable = subPort->addLabel("Port:");
  portLable->setSize({ w->getWidth() / 6.0, 50.0 });
  auto portEdit = subPort->addLineEdit(std::to_string(_config->lobbyServerMyPort));
  portEdit->setSize({ w->getWidth() / 6.0, 50.0 });
  portEdit->setValidator(Ahwassa::LineEdit::integerValidator(0, 500065535));
  portEdit->setEditFinishedCallback([this](std::string content)
    {
      _config->lobbyServerMyPort = std::atoi(content.c_str());
    });

  _page->layout().addButton("OK", [this]() { goBack(); });
  setVisible(false);
}

void OptionsPage::draw() {
  _page->draw();
}

void OptionsPage::setVisible(bool visible) {
  _page->setVisible(visible);
}

OptionsPageStatus OptionsPage::getStatus() {
  return _status;
}

void OptionsPage::goBack() {
  _status = OptionsPageStatus::Back;
}

void OptionsPage::reset() {
  _status = OptionsPageStatus::Pending;
  _requiresRestart = false;
}

bool OptionsPage::requiresRestart() {
  return _requiresRestart;
}
