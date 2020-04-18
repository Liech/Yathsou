#pragma once

#include <string>

#include "json_fwd.hpp"

namespace Iavish {
  struct ServerConfiguration {
    int port = 6112;

    nlohmann::json toJson();
    void           fromJson(nlohmann::json);
    void           toFile(std::string filename);
    void           fromFile(std::string filename);
  };
}