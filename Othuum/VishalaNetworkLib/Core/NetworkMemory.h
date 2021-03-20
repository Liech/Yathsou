#pragma once

#include <functional>
#include "VishalaNetworkLib/Core/Connection.h"
#include "VishalaNetworkLib/Core/ConnectionMultiplexer.h"

namespace Vishala {
  class BinaryPackage;

  template<typename T>
  class NetworkMemoryWriter {
  public:
    NetworkMemoryWriter(size_t channel, std::shared_ptr<Connection> connection) {
      _connection = connection;
      _channel    = channel   ;
    }
    T Data;

    void changed() {//please call when data changes
      _changed = true;
    }; 

    void update() {
      if (_changed) {
        BinaryPackage package = Data.toBinary();
        for(auto target : _connection->getAllConnections())
          _connection->send(target, _channel, std::make_unique<BinaryPackage>(package), true);
        //_changed = false;
      }
    }
  private:
    std::shared_ptr<Connection> _connection;
    bool                        _changed = true;
    size_t                      _channel = 0;
  };

  template<typename T>
  class NetworkMemoryReader {
  public:
    NetworkMemoryReader(size_t player, std::shared_ptr<ConnectionMultiplexer> connection) {
      _connection = connection;
      _player     = player    ;
      _connection->setOnRecievedCall(_player, [this](std::unique_ptr<BinaryPackage> inp) {
        messageRecieved(std::move(inp));
        });        
    }

    const T& Data() { 
      return _currentData;
    }

    void setOnChangedCallback(std::function<void()> onChanged) {
      _onChanged = onChanged;
    }
    
  private:
    void messageRecieved(std::unique_ptr<BinaryPackage> package) {
      _currentData.fromBinary(*package);
      _onChanged();
    }

    T                           _currentData;
    std::function<void()>       _onChanged = []() {};
    std::shared_ptr<ConnectionMultiplexer> _connection;
    size_t                                 _player;
  };
}