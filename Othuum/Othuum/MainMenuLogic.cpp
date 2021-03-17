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
#include "MainMenuPages/GameLobbyPage.h"
#include "MainMenuPages/JoinLoadingPage.h"
#include "MainMenuPages/StartGameLoadingPage.h"

#include "SideProject/SideProjectMain.h"

#include "YolonaOss/OpenGL/Drawable.h"
#include "YolonaOss/OpenGL/Window.h"
#include "IyathuumCoreLib/Singleton/Database.h"
#include <thread>
#include "IyathuumCoreLib/Util/ContentLoader.h"
#include "UyanahGameServer/DedicatedServerConfiguration.h"
#include "UyanahGameServer/ClientConfiguration.h"

MainMenuLogic::MainMenuLogic(YolonaOss::GL::Window& window,std::shared_ptr<ClientConfiguration> config, std::shared_ptr<ClientState> state) 
  : _window(window)
{
  _config     = config;
  _state      = state ;

  _mainMenuPage         = std::make_shared<MainMenuPage >();
  _joinLobbyPage        = std::make_shared<JoinLobbyPage>       (config);
  _hostPage             = std::make_shared<HostGamePage>        (config);
  _optionsPage          = std::make_shared<OptionsPage>         (config);
  _errorPage            = std::make_shared<ErrorPage>           (config);
  _sideProject          = std::make_shared<SideProject::SideProjectMain> ();
  _lobbyPage            = std::make_shared<LobbyPage>           (config, state);
  _gameLobbyPage        = std::make_shared<GameLobbyPage>       (config, state);
  _lobbyLoadingPage     = std::make_shared<LobbyLoadingPage>    (config, state);
  _hostLoadingPage      = std::make_shared<HostLoadingPage>     (config, state);
  _joinLoadingPage      = std::make_shared<JoinLoadingPage>     (config, state);
  _startGameLoadingPage = std::make_shared<StartGameLoadingPage>(config, state);
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_mainMenuPage         , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_joinLobbyPage        , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_lobbyPage            , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_hostPage             , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_optionsPage          , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_lobbyLoadingPage     , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_hostLoadingPage      , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_errorPage            , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_gameLobbyPage        , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_joinLoadingPage      , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_startGameLoadingPage , { "Main" });
}

void MainMenuLogic::update() {
  if (_extracted)
    throw std::runtime_error("Main Menu Logic was already extracted");
  if (_stat == status::MainMenu) {
    if (_mainMenuPage->getStatus() == MainMenuPageStatus::Multiplayer) {
      _mainMenuPage->reset();
      _mainMenuPage->setVisible(false);
      _joinLobbyPage->setVisible(true);
      _stat = status::LobbyEntry;
    }
    else if (_mainMenuPage->getStatus() == MainMenuPageStatus::Options && _stat == status::MainMenu) {
      _mainMenuPage->reset();
      _mainMenuPage->setVisible(false);
      _optionsPage->setVisible(true);
      _stat = status::Options;
    }
    else if (_mainMenuPage->getStatus() == MainMenuPageStatus::SideProject && _stat == status::MainMenu) {
      _mainMenuPage->reset();
      _mainMenuPage->setVisible(false);
      Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_sideProject, { "Main" });
      _sideProject->load(_window.getSpec());
      _stat = status::SideProject;
    }
  }
  else if (_stat == status::Options) {
    if (_optionsPage->getStatus() == OptionsPageStatus::Back) {
      _optionsPage->setVisible(false);
      _mainMenuPage->setVisible(true);
      _stat = status::MainMenu;
      if (_optionsPage->requiresRestart()) {
        showError("Some options may require a restart", "Hint");
      }
      _optionsPage->reset();
    }
  }
  else if (_stat == status::LobbyEntry) {
    if (_joinLobbyPage->getStatus() == JoinLobbyPageStatus::Back) {
      _joinLobbyPage->setVisible(false);
      _mainMenuPage->setVisible(true);
      _stat = status::MainMenu;
      _joinLobbyPage->reset();
    }
    else if (_joinLobbyPage->getStatus() == JoinLobbyPageStatus::Proceed) {
      _joinLobbyPage->setVisible(false);
      _lobbyLoadingPage->setVisible(true);

      _stat = status::LoadLobby;
      _joinLobbyPage->reset();
      _lobbyLoadingPage->start();
    }
  }
  else if (_stat == status::LoadLobby){
    _lobbyLoadingPage->update();
    if (_lobbyLoadingPage->getStatus() == LobbyLoadingPageStatus::Proceed) {
      _lobbyLoadingPage->setVisible(false);
      _lobbyPage->setVisible(true);
      _stat = status::Lobby;
      _lobbyLoadingPage->reset();
    }
    else if (_lobbyLoadingPage->getStatus() == LobbyLoadingPageStatus::Back) {
      _lobbyLoadingPage->setVisible(false);
      _joinLobbyPage->setVisible(true);
      _stat = status::LobbyEntry;
      _lobbyLoadingPage->reset();
      _state->stop();
    }
    else if (_lobbyLoadingPage->getStatus() == LobbyLoadingPageStatus::Error) {
      showError("Unable to connect to Lobby", "ERROR");
      _state->stop();
    }
  }
  else if (_stat == status::Lobby) {
    if (_lobbyPage->getStatus() == LobbyPageStatus::Back) {
      _lobbyPage->setVisible(false);
      _mainMenuPage->setVisible(true);
      _stat = status::MainMenu;
      _state->stop();
      _lobbyPage->reset();
    }
    else if (_lobbyPage->getStatus() == LobbyPageStatus::Host) {
      _lobbyPage->setVisible(false);
      _hostPage->setVisible(true);
      _stat = status::AdjustHostOptions;
      _lobbyPage->reset();
    }
    else if (_lobbyPage->getStatus() == LobbyPageStatus::Join) {
      _lobbyPage->setVisible(false);
      _joinLoadingPage->setVisible(true);
      _stat = status::LoadJoin;
      _joinLoadingPage->start(_lobbyPage->getGameID());
      _lobbyPage->reset();
    }
  }
  else if (_stat == status::AdjustHostOptions) {
    if (_hostPage->getStatus() == HostPageStatus::Back && _stat == status::AdjustHostOptions) {
      _hostPage->setVisible(false);
      _lobbyPage->setVisible(true);
      _stat = status::Lobby;
      _hostPage->reset();
    }
    else if (_hostPage->getStatus() == HostPageStatus::Host) {
      _hostPage->setVisible(false);
      _hostLoadingPage->setVisible(true);
      _stat = status::LoadHost;
      _hostLoadingPage->start(_hostPage->getResult());
      _hostPage->reset();
    }
  }
  else if (_stat == status::LoadHost) {
    _hostLoadingPage->update();
    if (_hostLoadingPage->getStatus() == HostLoadingPageStatus::Back) {
      _hostLoadingPage->setVisible(false);
      _hostPage->setVisible(true);
      _stat = status::AdjustHostOptions;
      _hostLoadingPage->reset();
      _server = nullptr;
    }
    else if (_hostLoadingPage->getStatus() == HostLoadingPageStatus::Proceed) {
      _hostLoadingPage->setVisible(false);
      _gameLobbyPage->setVisible(true);
      _stat = status::GameLobbyHost;
      _hostLoadingPage->reset();
      _gameLobbyPage->start();
      createServer();
    }
    else if (_hostLoadingPage->getStatus() == HostLoadingPageStatus::Error) {
      showError("Error while hosting game", "ERROR");
    }
  }
  else if (_stat == status::LoadJoin) {
  _joinLoadingPage->update();
  if (_joinLoadingPage->getStatus() == JoinLoadingPageStatus::Back) {
    _joinLoadingPage->setVisible(false);
    _lobbyPage->setVisible(true);
    _stat = status::Lobby;
    _joinLoadingPage->reset();
  }
  else if (_joinLoadingPage->getStatus() == JoinLoadingPageStatus::Proceed) {
    _joinLoadingPage->setVisible(false);
    _gameLobbyPage->setVisible(true);
    _stat = status::GameLobbyClient;
    _joinLoadingPage->reset();
    _gameLobbyPage->start();
  }
  else if (_joinLoadingPage->getStatus() == JoinLoadingPageStatus::Error) {
    showError("Error while joining game", "ERROR");
  }
  }
  else if (_stat == status::GameLobbyHost|| _stat == status::GameLobbyClient) {
    _gameLobbyPage->update();
    if (_gameLobbyPage->getStatus() == GameLobbyPageStatus::Back) {
      _gameLobbyPage->setVisible(false);
      _lobbyPage->setVisible(true);
      _stat = status::Lobby;  
      _state->closeGame();
      _gameLobbyPage->reset();
      _server = nullptr;
    }
    else if (_gameLobbyPage->getStatus() == GameLobbyPageStatus::WaitForStartGame) {
      _gameLobbyPage->setVisible(false);
      _gameLobbyPage->reset();
      _state->startGame();
      _startGameLoadingPage->setVisible(true);
      setLoader();
      _startGameLoadingPage->HostWait();
      _stat = status::HostWaitStartGame;
      _clientConfig.serverIP   = _gameLobbyPage->getGameIP();
      _clientConfig.serverPort = _gameLobbyPage->getGamePort();
      _clientConfig.myPort     = _config->myGameClientPort;
      createClient();
    }
    else if (_gameLobbyPage->getStatus() == GameLobbyPageStatus::StartGame) {
      _gameLobbyPage->setVisible(false);
      setLoader();
      _startGameLoadingPage->setVisible(true);
      _startGameLoadingPage->LoadGame();
      _stat = status::GameLoading;
      std::cout << "Game started" << std::endl;
      _clientConfig.serverIP   = _gameLobbyPage->getGameIP();
      _clientConfig.serverPort = _gameLobbyPage->getGamePort();
      _clientConfig.myPort = _config->myGameClientPort;
      createClient();
      _gameLobbyPage->reset();
    }
  }
  else if (_stat == status::HostWaitStartGame || _stat == status::GameLoading)
  {
    _startGameLoadingPage->update();
    if (_startGameLoadingPage->getStatus() == StartGameLoadingPageStatus::Back) {
      _startGameLoadingPage->setVisible(false);
      _lobbyPage->setVisible(true);
      _stat = status::Lobby;
      _state->closeGame();
      _startGameLoadingPage->reset();
      _server = nullptr;
      std::cout << "StartGameLoadingPageStatus::Back" << std::endl;
    }
    else if (_startGameLoadingPage->getStatus() == StartGameLoadingPageStatus::Error) {
      showError("Error while loading game", "ERROR");
    }
    else if (_startGameLoadingPage->getStatus() == StartGameLoadingPageStatus::Proceed) {
      _startGameLoadingPage->setVisible(false); 
      _startGameLoadingPage->reset();
      _stat = status::GameRunning;
      std::cout << "StartGameLoadingPageStatus::Proceed" << std::endl;
    }
  }
  else if (_stat == status::Error) {
    if (_errorPage->getStatus() == ErrorPageStatus::Back) {
      _errorPage->setVisible(false);
      _mainMenuPage->setVisible(true);
      _stat = status::MainMenu;
      _mainMenuPage->reset();
    }
  }
}

void MainMenuLogic::setContentLoaderCreater(std::function<std::shared_ptr<Iyathuum::ContentLoader>()> c){
  _contentCreator = c;
}

void MainMenuLogic::setLoader() {
  _startGameLoadingPage->setLoader(_contentCreator());
}

void MainMenuLogic::showError(std::string desc,std::string title) {
  _stat = status::Error;
  _errorPage           ->setVisible(true);
  _mainMenuPage        ->setVisible(false);
  _joinLobbyPage       ->setVisible(false);
  _lobbyPage           ->setVisible(false);
  _hostPage            ->setVisible(false);
  _optionsPage         ->setVisible(false);
  _lobbyLoadingPage    ->setVisible(false);
  _hostLoadingPage     ->setVisible(false);
  _gameLobbyPage       ->setVisible(false);
  _joinLoadingPage     ->setVisible(false);
  _startGameLoadingPage->setVisible(false);
  _mainMenuPage        ->reset();
  _joinLobbyPage       ->reset();
  _lobbyPage           ->reset();
  _hostPage            ->reset();
  _optionsPage         ->reset();
  _lobbyLoadingPage    ->reset();
  _hostLoadingPage     ->reset();
  _gameLobbyPage       ->reset();
  _joinLoadingPage     ->reset();
  _startGameLoadingPage->reset();
  _server = nullptr;
  _client = nullptr;
  _errorPage->setMessage(desc,title);
  _state->stop();
}

void MainMenuLogic::createClient() {
  _client = std::make_unique<Uyanah::Client>();
  _client->setConfig(_clientConfig);
  _client->start();
}

void MainMenuLogic::createServer() {
  _server = std::make_unique<Uyanah::DedicatedServer>();
  Uyanah::DedicatedServerConfiguration config;
  config.welcomePort = _config->gameServerPort;
  _server->setConfig(config);
  _server->start();
}

std::unique_ptr<MainMenuLogicResult> MainMenuLogic::extractResult(){
  if (getStatus() != status::GameRunning)
    throw std::runtime_error("Wrong status");
  std::unique_ptr < MainMenuLogicResult> result = std::make_unique<MainMenuLogicResult>();
  if (_server)
    result->_server = std::move(_server);
  if (_client)
    result->_client = std::move(_client);
  _extracted = true;
  return std::move(result);
}