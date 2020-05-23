#include "MainMenuLogic.h"

#include "ClientConfiguration.h"

#include "JoinLobbyPage.h"
#include "MainMenuPage.h"
#include "LobbyPage.h"

#include "YolonaOss/OpenGL/Drawable.h"
#include "IyathuumCoreLib/Singleton/Database.h"


MainMenuLogic::MainMenuLogic(std::shared_ptr<ClientConfiguration> config) {
  _config = config;
  _mainMenuPage  = std::make_shared<MainMenuPage >();
  _joinLobbyPage = std::make_shared<JoinLobbyPage>(config);
  _lobbyPage     = std::make_shared<LobbyPage>(config);
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_mainMenuPage , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_joinLobbyPage, { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_lobbyPage    , { "Main" });
}

void MainMenuLogic::update() {
  if (_mainMenuPage->getStatus() == MainMenuPageStatus::Multiplayer && stat == status::MainMenu) {
    _mainMenuPage->reset();
    _mainMenuPage->setVisible(false);
    _joinLobbyPage->setVisible(true);
    stat = status::LobbyEntry;
  }
  else if (_joinLobbyPage->getStatus() == JoinLobbyPageStatus::Back && stat == status::LobbyEntry) {
    _mainMenuPage->setVisible(true);
    _joinLobbyPage->setVisible(false);
    stat = status::MainMenu;
    _joinLobbyPage->reset();
  }
  else if (_joinLobbyPage->getStatus() == JoinLobbyPageStatus::Proceed && stat == status::LobbyEntry) {
    _lobbyPage->setVisible(true);
    _joinLobbyPage->setVisible(false);
    stat = status::Lobby;
    _joinLobbyPage->reset();
  }
  else if (_lobbyPage->getStatus() == LobbyPageStatus::Back && stat == status::Lobby) {
    _lobbyPage->setVisible(false);
    _mainMenuPage->setVisible(true);
    stat = status::MainMenu;
    _joinLobbyPage->reset();
  }
}