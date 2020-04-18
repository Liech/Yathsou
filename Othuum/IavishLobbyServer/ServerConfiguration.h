#pragma once

#include <string>

namespace nlohmann {
  class json;
}

namespace Iavish {
  struct ServerConfiguration {
    int port;

    nlohmann::json toJson();
    void           fromJson(nlohmann::json);
    void           toFile(std::string filename);
    void           fromFile(std::string filename);
  };
}