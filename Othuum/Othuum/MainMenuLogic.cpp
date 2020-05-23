#include "MainMenuLogic.h"

#include "ClientConfiguration.h"

#include "JoinLobbyPage.h"
#include "MainMenuPage.h"
#include "LobbyPage.h"
#include "HostGamePage.h"
#include "OptionsPage.h"

#include "YolonaOss/OpenGL/Drawable.h"
#include "IyathuumCoreLib/Singleton/Database.h"


MainMenuLogic::MainMenuLogic(std::shared_ptr<ClientConfiguration> config) {
  _config = config;
  _mainMenuPage = std::make_shared<MainMenuPage >();
  _joinLobbyPage = std::make_shared<JoinLobbyPage>(config);
  _lobbyPage     = std::make_shared<LobbyPage>    (config);
  _hostPage      = std::make_shared<HostGamePage> (config);
  _optionsPage   = std::make_shared<OptionsPage> (config);
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_mainMenuPage , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_joinLobbyPage, { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_lobbyPage    , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_hostPage     , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_optionsPage  , { "Main" });
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
    _lobbyPage->setVisible(true);
    stat = status::Lobby;
    _joinLobbyPage->reset();
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
}