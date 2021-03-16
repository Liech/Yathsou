#include "StartGameLoadingPage.h"

#include <iostream>

#include "YolonaOss/Drawables/Widgets/ListLayout.h"
#include "YolonaOss/Drawables/Widgets/Label.h"
#include "YolonaOss/Drawables/Widgets/LineEdit.h"

#include "VishalaNetworkLib/Serializable/Client2LobbyMessage.h"

StartGameLoadingPage::StartGameLoadingPage(std::shared_ptr<ClientConfiguration> configuration, std::shared_ptr<ClientState> state) {
  _config = configuration;
  _state  = state;
}

void StartGameLoadingPage::load(YolonaOss::GL::DrawSpecification* spec) {
  _page = std::make_unique<DialogPage>(spec->width, spec->height);

  _page->layout().addLabel("Starting Game...");
  
  _page->layout().addButton("Cancel", [this]() { goBack(); });
  setVisible(false);
}

void StartGameLoadingPage::update() {
  if (_state->getStatus() == ClientStateStatus::Lobby)
    _status = StartGameLoadingPageStatus::Error;
  else if (_state->getStatus() == ClientStateStatus::GameRunning)
    finish();

  if (_state && _status == StartGameLoadingPageStatus::HostWait) {
    std::unique_ptr<Vishala::GameLobbyStateUpdate> s = _state->getGameLobbyStateUpdate();
    if (s)
    {
      if (s->gameStart)
      {
        _status = StartGameLoadingPageStatus::Pending;
        startLoading();
      }
    }
  }
}

void StartGameLoadingPage::draw() {
  _page->draw();
}

void StartGameLoadingPage::setVisible(bool visible) {
  _page->setVisible(visible);
}

StartGameLoadingPageStatus StartGameLoadingPage::getStatus() {
  return _status;
}

void StartGameLoadingPage::finish() {
  _status = StartGameLoadingPageStatus::Proceed;
}


void StartGameLoadingPage::goBack() {
  _status = StartGameLoadingPageStatus::Back;
}

void StartGameLoadingPage::reset() {
  _status = StartGameLoadingPageStatus::Pending;
}

void StartGameLoadingPage::LoadGame(){
  _status = StartGameLoadingPageStatus::Pending;
  startLoading();
}

void StartGameLoadingPage::HostWait() {
  _status = StartGameLoadingPageStatus::HostWait;
}

void StartGameLoadingPage::startLoading()
{
  std::cout << "Load Game" << std::endl;
  _status = StartGameLoadingPageStatus::Proceed;
}

void StartGameLoadingPage::setLoader()
{

}