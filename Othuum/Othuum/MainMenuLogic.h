#pragma once

#include <string>
#include <memory>
#include "VishalaNetworkLib/Core/Connection.h"
#include "MainMenuLogicResult.h"

class ClientConfiguration;
class ClientState        ;
class MainMenuPage       ;
class JoinLobbyPage      ;
class LobbyPage          ;
class GameLobbyPage      ;
class HostGamePage       ;
class OptionsPage        ;
class ErrorPage          ;
class LobbyLoadingPage   ;
class HostLoadingPage    ;
class JoinLoadingPage    ;
namespace SideProject { class SideProjectMain; }
namespace YolonaOss{namespace GL{class Window;}}

class MainMenuLogic {
public:
  enum class status {
    MainMenu,
    LobbyEntry,
    LoadLobby,
    Lobby,
    AdjustHostOptions,
    LoadHost,
    Options,
    Error,
    GameLobbyHost,
    GameLobbyClient,
    LoadJoin,
    GameStarted,
    SideProject
  };
  

  MainMenuLogic(YolonaOss::GL::Window& window, std::shared_ptr<ClientConfiguration> config,std::shared_ptr<ClientState> state);

  void                  update();
  MainMenuLogic::status getStatus() { return _stat; }
  MainMenuLogicResult   extractResult();

private:
  status                               _stat = status::MainMenu;
  bool                                 _extracted = false;
  std::shared_ptr<ClientConfiguration> _config     ;
  std::shared_ptr<ClientState        > _state      ;
  std::shared_ptr<Vishala::Connection> _connection = nullptr;

  std::shared_ptr<MainMenuPage >                _mainMenuPage    ;
  std::shared_ptr<JoinLobbyPage>                _joinLobbyPage   ;
  std::shared_ptr<LobbyLoadingPage>             _lobbyLoadingPage;
  std::shared_ptr<LobbyPage>                    _lobbyPage       ;
  std::shared_ptr<HostGamePage>                 _hostPage        ;
  std::shared_ptr<HostLoadingPage>              _hostLoadingPage ;
  std::shared_ptr<OptionsPage>                  _optionsPage     ;
  std::shared_ptr<ErrorPage>                    _errorPage       ;
  std::shared_ptr<GameLobbyPage>                _gameLobbyPage   ;
  std::shared_ptr<JoinLoadingPage>              _joinLoadingPage ;
  std::shared_ptr<SideProject::SideProjectMain> _sideProject     ;

  void showError(std::string desc, std::string title);
  YolonaOss::GL::Window& _window;
};