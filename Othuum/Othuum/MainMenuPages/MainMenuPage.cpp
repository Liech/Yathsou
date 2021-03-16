#include "MainMenuPage.h"

#include <iostream>

#include "YolonaOss/OpenGL/Window.h"
#include "YolonaOss/Drawables/Widgets/ListLayout.h"
#include "YolonaOss/Drawables/Widgets/Button.h"

#include "VishalaNetworkLib/Serializable/ServerConfiguration.h"
#include "VishalaNetworkLib/Protocoll/Server/Lobby.h"

MainMenuPage::MainMenuPage(){

}

MainMenuPage::~MainMenuPage(){
  if (_serverStarted)
  {
    _serverStarted = false;
    _serverThread.wait();
  }
}

void MainMenuPage::load(YolonaOss::GL::DrawSpecification* spec) {
  _page = std::make_unique<DialogPage>(spec->width, spec->height);
  
  _page->layout().addLabel("Main Menu Page");
  _page->layout().addButton("SideProject", [this]() { startSideProject();         });
  _startServerButton =
    _page->layout().addButton("Server", [this]() { if (!_serverStarted) startServer();         });
  _page->layout().addButton("Multiplayer", [this]() { startLobbyJoin();           });
  _page->layout().addButton("Options"    , [this]() { startOptions();             });
  _page->layout().addButton("Quit"       , [spec]() { spec->getWindow()->close(); });
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

void MainMenuPage::startSideProject() {
  _status = MainMenuPageStatus::SideProject;
}

void MainMenuPage::startServer()
{
  _serverStarted = true;
  _startServerButton->setText("--Server Open--");

  std::cout << "LobbyServer::run()" << std::endl;
  Vishala::ServerConfiguration config;
  config.fromJsonFile("ServerConfiguration.json");
  std::cout << "Init Lobby" << std::endl;

  _serverThread = std::async(std::launch::async, [&config,this]() {
    auto s = std::make_unique<Vishala::Server::Lobby>(config);
    while (_serverStarted)
      s->update();
    });
}