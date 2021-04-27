#include "BlueprintCommandCaps.h"

namespace Athanah {
  BlueprintCommandCaps::BlueprintCommandCaps() {

  }

  BlueprintCommandCaps::BlueprintCommandCaps(nlohmann::json input) {
    if (input.find("RULEUCC_Attack"         ) != input.end()) _attack          = input["RULEUCC_Attack"         ] > 0;
    if (input.find("RULEUCC_CallTransport"  ) != input.end()) _callTransport   = input["RULEUCC_CallTransport"  ] > 0;
    if (input.find("RULEUCC_Capture"        ) != input.end()) _capture         = input["RULEUCC_Capture"        ] > 0;
    if (input.find("RULEUCC_Ferry"          ) != input.end()) _ferry           = input["RULEUCC_Ferry"          ] > 0;
    if (input.find("RULEUCC_Guard"          ) != input.end()) _guard           = input["RULEUCC_Guard"          ] > 0;
    if (input.find("RULEUCC_Move"           ) != input.end()) _move            = input["RULEUCC_Move"           ] > 0;
    if (input.find("RULEUCC_Nuke"           ) != input.end()) _nuke            = input["RULEUCC_Nuke"           ] > 0;
    if (input.find("RULEUCC_Patrol"         ) != input.end()) _patrol          = input["RULEUCC_Patrol"         ] > 0;
    if (input.find("RULEUCC_Reclaim"        ) != input.end()) _reclaim         = input["RULEUCC_Reclaim"        ] > 0;
    if (input.find("RULEUCC_Repair"         ) != input.end()) _repair          = input["RULEUCC_Repair"         ] > 0;
    if (input.find("RULEUCC_RetaliateToggle") != input.end()) _retaliateToggle = input["RULEUCC_RetaliateToggle"] > 0;
    if (input.find("RULEUCC_Transport"      ) != input.end()) _stop            = input["RULEUCC_Transport"      ] > 0;
    if (input.find("RULEUCC_Transport"      ) != input.end()) _transport       = input["RULEUCC_Transport"      ] > 0;
  }

  bool BlueprintCommandCaps::attack         () {return _attack         ;};
  bool BlueprintCommandCaps::callTransport  () {return _callTransport  ;};
  bool BlueprintCommandCaps::capture        () {return _capture        ;};
  bool BlueprintCommandCaps::ferry          () {return _ferry          ;};
  bool BlueprintCommandCaps::guard          () {return _guard          ;};
  bool BlueprintCommandCaps::move           () {return _move           ;};
  bool BlueprintCommandCaps::nuke           () {return _nuke           ;};
  bool BlueprintCommandCaps::patrol         () {return _patrol         ;};
  bool BlueprintCommandCaps::reclaim        () {return _reclaim        ;};
  bool BlueprintCommandCaps::repair         () {return _repair         ;};
  bool BlueprintCommandCaps::retaliateToggle() {return _retaliateToggle;};
  bool BlueprintCommandCaps::stop           () {return _stop           ;};
  bool BlueprintCommandCaps::transport      () {return _transport      ;};

}