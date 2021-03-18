#include "LoginInstructions.h"

#include "Core/BinaryPackage.h"

namespace Vishala {
  BinaryPackage LoginInstructions::toBinary()
  {
    BinaryPackage result;
    BinaryPackage::val2bin<std::string>(result, ip  );
    BinaryPackage::val2bin<int        >(result, port);
    return result;
  }

  void LoginInstructions::fromBinary(BinaryPackage& Package)
  {
    ip   = BinaryPackage::bin2val<std::string>(Package);
    port = BinaryPackage::bin2val<int        >(Package);
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