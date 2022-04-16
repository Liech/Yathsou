#include "MainMenuPage.h"

#include <iostream>
#include <chrono>

#include "AhwassaGraphicsLib/Widgets/ListLayout.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "AhwassaGraphicsLib/Core/Window.h"

#include "VishalaNetworkLib/Serializable/ServerConfiguration.h"
#include "VishalaNetworkLib/Protocoll/Server/Lobby.h"

MainMenuPage::MainMenuPage(Ahwassa::Window* w) : Ahwassa::Drawable(w) {
  _page = std::make_unique<DialogPage>(w);
  
  _page->layout().addLabel("Main Menu Page");
  _page->layout().addButton("SideProject", [this]() { startSideProject();         });
  _startServerButton =
  _page->layout().addButton("Server"     , [this]() { if (!_serverStarted) startServer();         });
  _page->layout().addButton("Multiplayer", [this]() { startLobbyJoin();           });
  _page->layout().addButton("Options"    , [this]() { startOptions();             });
  _page->layout().addButton("Quit"       , [w]() { w->close(); });
}

MainMenuPage::~MainMenuPage(){
  if (_serverStarted)
  {
    _serverStarted = false;
    _serverThread.wait();
  }
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
    auto start = std::chrono::steady_clock::now();
    while (_serverStarted) {
      auto now = std::chrono::steady_clock::now();
      auto diff = now - start;
      auto end = now + std::chrono::milliseconds(16);
      s->update();
      std::this_thread::sleep_until(end);
    }
    });
}