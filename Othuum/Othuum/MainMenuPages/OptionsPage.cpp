#include "OptionsPage.h"

#include <iostream>

#include "YolonaOss/Drawables/Widgets/ListLayout.h"
#include "YolonaOss/Drawables/Widgets/Label.h"
#include "YolonaOss/Drawables/Widgets/LineEdit.h"

OptionsPage::OptionsPage(std::shared_ptr<ClientConfiguration> configuration) {
  _config = configuration;
}

void OptionsPage::load(YolonaOss::GL::DrawSpecification* spec) {
  _page = std::make_unique<DialogPage>(spec->width, spec->height);
  _page->layout().addLabel("Options Page");
  
  auto subResolution = _page->layout().addLayout();
  subResolution->setHorizontal(true);
  auto resolutionLable = subResolution->addLabel("Resolution:");
  resolutionLable->getPosition().setSize({ spec->width / 6.0, 50.0 });
  auto resoXEdit = subResolution->addLineEdit(std::to_string(_config->resolution[0]));
  resoXEdit->getPosition().setSize({ spec->width / 6.0, 50.0 });
  resoXEdit->setValidator(YolonaOss::Widgets::LineEdit::integerValidator(0, 5000));
  resoXEdit->setEditFinishedCallback([this](std::string content) 
    { 
      _config->resolution[0] = std::atoi(content.c_str()); 
      _requiresRestart = true;
    });
  auto resoYEdit = subResolution->addLineEdit(std::to_string(_config->resolution[1]));
  resoYEdit->getPosition().setSize({ spec->width / 6.0, 50.0 });
  resoYEdit->setValidator(YolonaOss::Widgets::LineEdit::integerValidator(0, 5000));
  resoYEdit->setEditFinishedCallback([this](std::string content) 
    { 
      _config->resolution[1] = std::atoi(content.c_str()); 
      _requiresRestart = true;
    });

  auto subPort = _page->layout().addLayout();
  subPort->setHorizontal(true);
  auto portLable = subPort->addLabel("Port:");
  portLable->getPosition().setSize({ spec->width / 6.0, 50.0 });
  auto portEdit = subPort->addLineEdit(std::to_string(_config->lobbyServerMyPort));
  portEdit->getPosition().setSize({ spec->width / 6.0, 50.0 });
  portEdit->setValidator(YolonaOss::Widgets::LineEdit::integerValidator(0, 500065535));
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
