#include "MainMenuLogic.h"

#include "ClientConfiguration.h"

#include "JoinLobbyPage.h"
#include "MainMenuPage.h"

#include "YolonaOss/OpenGL/Drawable.h"
#include "IyathuumCoreLib/Singleton/Database.h"


MainMenuLogic::MainMenuLogic(std::shared_ptr<ClientConfiguration> config) {
  _config = config;
  _mainMenuPage  = std::make_shared<MainMenuPage >();
  _joinLobbyPage = std::make_shared<JoinLobbyPage>(config);
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_mainMenuPage , { "Main" });
  Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Drawable>>::add(_joinLobbyPage, { "Main" });
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
}