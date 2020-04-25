#include "LoginInstructions.h"

#include "BinaryPackage.h"

namespace Vishala {
  BinaryPackage LoginInstructions::toBinary()
  {
    BinaryPackage result;
    val2bin<std::string>(result, ip  );
    val2bin<int        >(result, port);
    return result;
  }

  void LoginInstructions::fromBinary(BinaryPackage& Package)
  {
    ip   = bin2val<std::string>(Package);
    port = bin2val<int        >(Package);
  }

  nlohmann::json LoginInstructions::toJson()
  {
    nlohmann::json result;
    result["Port"] = port;
    result["IP"]   = ip  ;
    return result;
  }

  void LoginInstructions::fromJson(nlohmann::json data)
  {
    port = data["Port"];
    ip   = data["IP"  ];
  }
}