#pragma once

#include "AezeselFileIOLib/lib/json.hpp"

namespace Athanah {
  class BlueprintCommandCaps {
  public:
    BlueprintCommandCaps();
    BlueprintCommandCaps(nlohmann::json);

    bool attack         ();
    bool callTransport  ();
    bool capture        ();
    bool ferry          ();
    bool guard          ();
    bool move           ();
    bool nuke           ();
    bool patrol         ();
    bool reclaim        ();
    bool repair         ();
    bool retaliateToggle();
    bool stop           ();
    bool transport      ();


  private:
    bool _attack          = false;
    bool _callTransport   = false;
    bool _capture         = false;
    bool _ferry           = false;
    bool _guard           = false;
    bool _move            = false;
    bool _nuke            = false;
    bool _patrol          = false;
    bool _reclaim         = false;
    bool _repair          = false;
    bool _retaliateToggle = false;
    bool _stop            = false;
    bool _transport       = false;
  };
}