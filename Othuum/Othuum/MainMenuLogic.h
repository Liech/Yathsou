#pragma once

#include <string>
#include <memory>

class MainMenuPage       ;
class JoinLobbyPage      ;
class LobbyPage          ;
class ClientConfiguration;
class HostGamePage       ;
class OptionsPage        ;
class ErrorPage          ;

class MainMenuLogic {
public:
  enum class status { 
    MainMenu, 
    LobbyEntry,
    Lobby,
    HostGame,
    Options,
    Error
  } stat = status::MainMenu;

  MainMenuLogic(std::shared_ptr<ClientConfiguration> config);

  void update();

private:
  std::shared_ptr<ClientConfiguration> _config;

  std::shared_ptr<MainMenuPage > _mainMenuPage ;
  std::shared_ptr<JoinLobbyPage> _joinLobbyPage;
  std::shared_ptr<LobbyPage>     _lobbyPage    ;
  std::shared_ptr<HostGamePage>  _hostPage     ;
  std::shared_ptr<OptionsPage>   _optionsPage  ;
  std::shared_ptr<ErrorPage>     _errorPage    ;

  void showError(std::string desc, std::string title);
};