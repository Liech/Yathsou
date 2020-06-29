#pragma once


#include <set>

#include "Connection.h"
#include "NetworkGameSeedInput.h"

/*
  The GameSeeds goal is to get a list of ip+port & info packages and make sure that the seed is connected to all seeds on the other side
  If the connection is lost it reconnects them
  Somehow the Peer2Peer central hub.
  The MainMenu should spit one out, which can be used to start a game
  It could be generated otherwise. Maybe even automated for cloud based ai
  Im not sure about the name. Something like "ConnectionManager" sounds lame. The primary job is to be the general core part of a startGame invocation
*/
namespace Vishala {
  class NetworkGameSeed {
  public:
    NetworkGameSeed(NetworkGameSeedInput input);

    void update();

  private:
    struct Target {
      std::string ip  ;
      int         port;
      size_t      id;
    };

    std::vector<Target>            _targets   ;
    NetworkGameSeedInput        _input     ;
    std::unique_ptr<Connection> _connection;
    size_t                      _targetIDCounter = 0;

    void initConnection();
    void initTargets();

    void newConnection        (size_t clientnumber, std::string ip, int port);
    void connectionFailed     (std::string name);
    void disconnect           (size_t clientnumber);
    void messageRecived       (size_t channel, size_t clientNumber, std::unique_ptr<BinaryPackage>);
    void controlMessageRecived(size_t clientNumber, std::unique_ptr<BinaryPackage>);


  };

}