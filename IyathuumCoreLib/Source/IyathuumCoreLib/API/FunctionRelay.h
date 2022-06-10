#pragma once

#include <nlohmann/json.hpp>

namespace Iyathuum {
  /// <summary>
  /// Deserializes numbers into callable functions. 
  /// E.g. a script gives an APIFunction a Function (disguised as number) in its parameters. To call it an Relay is needed
  /// </summary>
  class FunctionRelay {
    public:
      virtual nlohmann::json call(size_t id, const nlohmann::json&) = 0;
  };
}