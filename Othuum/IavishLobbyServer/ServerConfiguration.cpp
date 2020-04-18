#include "ServerConfiguration.h"

#include "json.hpp"
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

  void ServerConfiguration::toFile(std::string filename) {
    std::ofstream stream;
    stream.open(filename);
    nlohmann::json j = toJson();
    stream << j.dump(4);
    stream.close();
  }

  void ServerConfiguration::fromFile(std::string filename) {
    if (!std::filesystem::exists(filename))
      return;
    std::ifstream t(filename);
    std::string content((std::istreambuf_iterator<char>(t)),
      std::istreambuf_iterator<char>());
    t.close();
    fromJson(nlohmann::json::parse(content));
  }
}