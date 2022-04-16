#include "StartGameLoadingPage.h"

#include <iostream>

#include "AhwassaGraphicsLib/Widgets/ListLayout.h"
#include "AhwassaGraphicsLib/Widgets/Label.h"
#include "AhwassaGraphicsLib/Widgets/LineEdit.h"
#include "IyathuumCoreLib/Util/ContentLoader.h"
#include "VishalaNetworkLib/Serializable/Client2LobbyMessage.h"
#include "AhwassaGraphicsLib/Core/Window.h"

StartGameLoadingPage::StartGameLoadingPage(std::shared_ptr<ClientConfiguration> configuration, std::shared_ptr<ClientState> state, Ahwassa::Window* w) : Ahwassa::Drawable(w) {
  _config = configuration;
  _state  = state;

  _page = std::make_unique<DialogPage>(w);

  _text = _page->layout().addLabel("Starting Game...");
  
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

  if (_status == StartGameLoadingPageStatus::Pending && _loader) {
    _loader->update();
    _text->setText(std::to_string(_loader->getProgression() * 100));
    if (_loader->isFinished())
      _status = StartGameLoadingPageStatus::Proceed;
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
  if (_loader->isStarted())
    _loader->abort();
}

void StartGameLoadingPage::reset() {
  _status = StartGameLoadingPageStatus::Pending;
  _loader = nullptr;
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
  if (!_loader)
    throw std::runtime_error("StartGame Loading Page: No Loader");
  std::cout << "Load Game" << std::endl;
  _status = StartGameLoadingPageStatus::Pending;
  _loader->start();
}

void StartGameLoadingPage::setLoader(std::shared_ptr<Iyathuum::ContentLoader> loader)
{
  _loader = loader;
}