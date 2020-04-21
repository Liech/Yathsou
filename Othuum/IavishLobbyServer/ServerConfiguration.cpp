#include "ServerConfiguration.h"

#include <fstream>
#include <filesystem>

namespace Iavish {

  nlohmann::json ServerConfiguration::toJson() {
    nlohmann::json result;
    result["Port"] = port;
    return result;
  }

  void ServerConfiguration::fromJson(nlohmann::json from) {
    port = from["Port"];
  }

  std::vector<unsigned char> ServerConfiguration::toBinary() {
    std::vector<unsigned char> result;
    val2bin<int>(result,port);
    return result;
  }

  void ServerConfiguration::fromBinary(std::vector<unsigned char> data,size_t position) {
    port = bin2val<int>(data, position);
  }
}