#include "MainMenuLogic.h"

#include <iostream>

#include "ClientConfiguration.h"
#include "ClientState.h"

#include "MainMenuPages/JoinLobbyPage.h"
#include "MainMenuPages/MainMenuPage.h"
#include "MainMenuPages/LobbyPage.h"
#include "MainMenuPages/HostGamePage.h"
#include "MainMenuPages/OptionsPage.h"
#include "MainMenuPages/ErrorPage.h"
#include "MainMenuPages/LobbyLoadingPage.h"
#include "MainMenuPages/HostLoadingPage.h"

#include "YolonaOss/OpenGL/Drawable.h"
#include "IyathuumCoreLib/Singleton/Database.h"


MainMenuLogic::MainMenuLogic(std::shared_ptr<ClientConfiguration> config, std::shared_ptr<ClientState> state) {
  _config     = config;
  _state      = state ;

  _mainMenuPage     = std::make_shared<MainMenuPage >();
  _joinLobbyPage    = std::make_shared<JoinLobbyPage>    (config);
  _hostPage         = std::make_shared<HostGamePage>     (config);
  _optionsPage      = std::make_shared<OptionsPage>      (config);
  _errorPage        = std::make_shared<ErrorPage>        (config);
  _lobbyPage        = std::make_shared<LobbyPage>        (config, state);
  _lobbyLoadingPage = std::make_shared<LobbyLoadingPage> (config, state);
  _hostLoadingPage  = std::make_shared<HostLoadingPage>  (config, state);
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_mainMenuPage    , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_joinLobbyPage   , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_lobbyPage       , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_hostPage        , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_optionsPage     , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_lobbyLoadingPage, { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_hostLoadingPage , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_errorPage       , { "Main" });
}

void MainMenuLogic::update() {
  if (_mainMenuPage->getStatus() == MainMenuPageStatus::Multiplayer && stat == status::MainMenu) {
    _mainMenuPage->reset();
    _mainMenuPage->setVisible(false);
    _joinLobbyPage->setVisible(true);
    stat = status::LobbyEntry;
  }
  else if (_mainMenuPage->getStatus() == MainMenuPageStatus::Options && stat == status::MainMenu) {
    _mainMenuPage->reset();
    _mainMenuPage->setVisible(false);
    _optionsPage->setVisible(true);
    stat = status::Options;
  }
  else if (_optionsPage->getStatus() == OptionsPageStatus::Back && stat == status::Options) {
    _optionsPage->setVisible(false);
    _mainMenuPage->setVisible(true);
    stat = status::MainMenu;
    if (_optionsPage->requiresRestart()) {
      showError("Some options may require a restart","Hint");
    }      
    _optionsPage->reset();
  }
  else if (_joinLobbyPage->getStatus() == JoinLobbyPageStatus::Back && stat == status::LobbyEntry) {
    _joinLobbyPage->setVisible(false);
    _mainMenuPage->setVisible(true);
    stat = status::MainMenu;
    _joinLobbyPage->reset();
  }
  else if (_joinLobbyPage->getStatus() == JoinLobbyPageStatus::Proceed && stat == status::LobbyEntry) {
    _joinLobbyPage->setVisible(false);
    _lobbyLoadingPage->setVisible(true);
    
    stat = status::LoadLobby;
    _joinLobbyPage->reset();
    _lobbyLoadingPage->start();
  }
  else if (_lobbyLoadingPage->getStatus() == LobbyLoadingPageStatus::Proceed && stat == status::LoadLobby) {
    _lobbyLoadingPage->setVisible(false);
    _lobbyPage->setVisible(true);
    stat = status::Lobby;
    _lobbyLoadingPage->reset();
  }
  else if (_lobbyLoadingPage->getStatus() == LobbyLoadingPageStatus::Back && stat == status::LoadLobby) {
    _lobbyLoadingPage->setVisible(false);
    _joinLobbyPage->setVisible(true);
    stat = status::LobbyEntry;
    _lobbyLoadingPage->reset();
    _state->stop();
  }
  else if (_lobbyLoadingPage->getStatus() == LobbyLoadingPageStatus::Error && stat == status::LoadLobby) {
    showError("Unable to connect to Lobby", "ERROR");
    _state->stop();
  }
  else if (stat == status::LoadLobby) {
    _lobbyLoadingPage->update();
  }
  else if (_lobbyPage->getStatus() == LobbyPageStatus::Back && stat == status::Lobby) {
    _lobbyPage->setVisible(false);
    _mainMenuPage->setVisible(true);
    stat = status::MainMenu;
    _lobbyPage->reset();
  }
  else if (_lobbyPage->getStatus() == LobbyPageStatus::Host && stat == status::Lobby) {
    _lobbyPage->setVisible(false);
    _hostPage->setVisible(true);
    stat = status::HostGame;
    _lobbyPage->reset();
  }
  else if (_hostPage->getStatus() == HostPageStatus::Back && stat == status::HostGame) {
    _hostPage->setVisible(false);
    _lobbyPage->setVisible(true);
    stat = status::Lobby;
    _hostPage->reset();
  }
  else if (_hostPage->getStatus() == HostPageStatus::Host && stat == status::HostGame) {
    _hostPage->setVisible(false);
    _hostLoadingPage->setVisible(true);
    stat = status::LoadHost;
    _hostLoadingPage->start(_hostPage->getResult());
    _hostPage->reset();
  }
  else if (_hostLoadingPage->getStatus() == HostLoadingPageStatus::Back && stat == status::LoadHost) {
    _hostLoadingPage->setVisible(false);
    _hostPage->setVisible(true);
    stat = status::HostGame;
    _hostLoadingPage->reset();
  }
  else if (_hostLoadingPage->getStatus() == HostLoadingPageStatus::Proceed && stat == status::LoadHost) {
    _hostLoadingPage->setVisible(true);
    throw std::runtime_error("SUCCESS: Game Lobby Open");
    stat = status::GameLobbyHost;
    _hostLoadingPage->reset();
  }
  else if (_hostLoadingPage->getStatus() == HostLoadingPageStatus::Error && stat == status::LoadHost) {
    showError("Error while hosting game", "ERROR");
  }
  else if (_errorPage->getStatus() == ErrorPageStatus::Back && stat == status::Error) {
    _errorPage->setVisible(false);
    _mainMenuPage->setVisible(true);
    stat = status::MainMenu;
    _mainMenuPage->reset();
  }
}

void MainMenuLogic::showError(std::string desc,std::string title) {
  stat = status::Error;
  _errorPage->setVisible(true);
  _mainMenuPage    ->setVisible(false);
  _joinLobbyPage   ->setVisible(false);
  _lobbyPage       ->setVisible(false);
  _hostPage        ->setVisible(false);
  _optionsPage     ->setVisible(false);
  _lobbyLoadingPage->setVisible(false);
  _hostLoadingPage->setVisible(false);
  _mainMenuPage    ->reset();
  _joinLobbyPage   ->reset();
  _lobbyPage       ->reset();
  _hostPage        ->reset();
  _optionsPage     ->reset();
  _lobbyLoadingPage->reset();
  _hostLoadingPage ->reset();
  _errorPage->setMessage(desc,title);

}