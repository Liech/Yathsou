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
  _gameLobbyPage    = std::make_shared<GameLobbyPage>    (config, state);
  _lobbyLoadingPage = std::make_shared<LobbyLoadingPage> (config, state);
  _hostLoadingPage  = std::make_shared<HostLoadingPage>  (config, state);
  _joinLoadingPage  = std::make_shared<JoinLoadingPage>  (config, state);
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_mainMenuPage    , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_joinLobbyPage   , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_lobbyPage       , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_hostPage        , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_optionsPage     , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_lobbyLoadingPage, { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_hostLoadingPage , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_errorPage       , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_gameLobbyPage   , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_joinLoadingPage , { "Main" });
}

void MainMenuLogic::update() {
  if (stat == status::MainMenu) {
    if (_mainMenuPage->getStatus() == MainMenuPageStatus::Multiplayer) {
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
  }
  else if (stat == status::Options) {
    if (_optionsPage->getStatus() == OptionsPageStatus::Back) {
      _optionsPage->setVisible(false);
      _mainMenuPage->setVisible(true);
      stat = status::MainMenu;
      if (_optionsPage->requiresRestart()) {
        showError("Some options may require a restart", "Hint");
      }
      _optionsPage->reset();
    }
  }
  else if (stat == status::LobbyEntry) {
    if (_joinLobbyPage->getStatus() == JoinLobbyPageStatus::Back) {
      _joinLobbyPage->setVisible(false);
      _mainMenuPage->setVisible(true);
      stat = status::MainMenu;
      _joinLobbyPage->reset();
    }
    else if (_joinLobbyPage->getStatus() == JoinLobbyPageStatus::Proceed) {
      _joinLobbyPage->setVisible(false);
      _lobbyLoadingPage->setVisible(true);

      stat = status::LoadLobby;
      _joinLobbyPage->reset();
      _lobbyLoadingPage->start();
    }
  }
  else if (stat == status::LoadLobby){
    _lobbyLoadingPage->update();
    if (_lobbyLoadingPage->getStatus() == LobbyLoadingPageStatus::Proceed) {
      _lobbyLoadingPage->setVisible(false);
      _lobbyPage->setVisible(true);
      stat = status::Lobby;
      _lobbyLoadingPage->reset();
    }
    else if (_lobbyLoadingPage->getStatus() == LobbyLoadingPageStatus::Back) {
      _lobbyLoadingPage->setVisible(false);
      _joinLobbyPage->setVisible(true);
      stat = status::LobbyEntry;
      _lobbyLoadingPage->reset();
      _state->stop();
    }
    else if (_lobbyLoadingPage->getStatus() == LobbyLoadingPageStatus::Error) {
      showError("Unable to connect to Lobby", "ERROR");
      _state->stop();
    }
  }
  else if (stat == status::Lobby) {
    if (_lobbyPage->getStatus() == LobbyPageStatus::Back) {
      _lobbyPage->setVisible(false);
      _mainMenuPage->setVisible(true);
      stat = status::MainMenu;
      _state->stop();
      _lobbyPage->reset();
    }
    else if (_lobbyPage->getStatus() == LobbyPageStatus::Host) {
      _lobbyPage->setVisible(false);
      _hostPage->setVisible(true);
      stat = status::AdjustHostOptions;
      _lobbyPage->reset();
    }
    else if (_lobbyPage->getStatus() == LobbyPageStatus::Join) {
      _lobbyPage->setVisible(false);
      _joinLoadingPage->setVisible(true);
      stat = status::LoadJoin;
      _joinLoadingPage->start(_lobbyPage->getGameID());
      _lobbyPage->reset();
    }
  }
  else if (stat == status::AdjustHostOptions) {
    if (_hostPage->getStatus() == HostPageStatus::Back && stat == status::AdjustHostOptions) {
      _hostPage->setVisible(false);
      _lobbyPage->setVisible(true);
      stat = status::Lobby;
      _hostPage->reset();
    }
    else if (_hostPage->getStatus() == HostPageStatus::Host) {
      _hostPage->setVisible(false);
      _hostLoadingPage->setVisible(true);
      stat = status::LoadHost;
      _hostLoadingPage->start(_hostPage->getResult());
      _hostPage->reset();
    }
  }
  else if (stat == status::LoadHost) {
    _hostLoadingPage->update();
    if (_hostLoadingPage->getStatus() == HostLoadingPageStatus::Back) {
      _hostLoadingPage->setVisible(false);
      _hostPage->setVisible(true);
      stat = status::AdjustHostOptions;
      _hostLoadingPage->reset();
    }
    else if (_hostLoadingPage->getStatus() == HostLoadingPageStatus::Proceed) {
      _hostLoadingPage->setVisible(false);
      _gameLobbyPage->setVisible(true);
      stat = status::GameLobbyHost;
      _hostLoadingPage->reset();
    }
    else if (_hostLoadingPage->getStatus() == HostLoadingPageStatus::Error) {
      showError("Error while hosting game", "ERROR");
    }
  }
  else if (stat == status::LoadJoin) {
  _joinLoadingPage->update();
  if (_joinLoadingPage->getStatus() == JoinLoadingPageStatus::Back) {
    _joinLoadingPage->setVisible(false);
    _lobbyPage->setVisible(true);
    stat = status::Lobby;
    _joinLoadingPage->reset();
  }
  else if (_joinLoadingPage->getStatus() == JoinLoadingPageStatus::Proceed) {
    _joinLoadingPage->setVisible(false);
    _gameLobbyPage->setVisible(true);
    stat = status::GameLobbyClient;
    _joinLoadingPage->reset();
  }
  else if (_joinLoadingPage->getStatus() == JoinLoadingPageStatus::Error) {
    showError("Error while joining game", "ERROR");
  }
  }
  else if (stat == status::GameLobbyHost|| stat == status::GameLobbyClient) {
    if (_gameLobbyPage->getStatus() == GameLobbyPageStatus::Back) {
    _gameLobbyPage->setVisible(false);
    _lobbyPage->setVisible(true);
    stat = status::Lobby;  
    _state->closeGame();
    _gameLobbyPage->reset();
    }
    else if (_gameLobbyPage->getStatus() == GameLobbyPageStatus::StartGame) {
      showError("Start Game Not Implemented Yet", "ERROR");
    }
  }
  else if (stat == status::Error) {
    if (_errorPage->getStatus() == ErrorPageStatus::Back) {
      _errorPage->setVisible(false);
      _mainMenuPage->setVisible(true);
      stat = status::MainMenu;
      _mainMenuPage->reset();
    }
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
  _hostLoadingPage ->setVisible(false);
  _gameLobbyPage   ->setVisible(false);
  _joinLoadingPage ->setVisible(false);
  _mainMenuPage    ->reset();
  _joinLobbyPage   ->reset();
  _lobbyPage       ->reset();
  _hostPage        ->reset();
  _optionsPage     ->reset();
  _lobbyLoadingPage->reset();
  _hostLoadingPage ->reset();
  _gameLobbyPage   ->reset();
  _joinLoadingPage ->reset();
  _errorPage->setMessage(desc,title);
  _state->stop();
}