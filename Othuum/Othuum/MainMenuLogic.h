#pragma once

#include <string>
#include <memory>

class MainMenuPage;
class JoinLobbyPage;
class LobbyPage;
class ClientConfiguration;

class MainMenuLogic {
public:
  enum class status { 
    MainMenu, 
    LobbyEntry,
    Lobby
  } stat = status::MainMenu;

  MainMenuLogic(std::shared_ptr<ClientConfiguration> config);

  void update();

private:
  std::shared_ptr<ClientConfiguration> _config;

  std::shared_ptr<MainMenuPage > _mainMenuPage ;
  std::shared_ptr<JoinLobbyPage> _joinLobbyPage;
  std::shared_ptr<LobbyPage>     _lobbyPage    ;
};