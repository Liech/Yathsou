#pragma once

#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

namespace Athanah {
  class BlueprintBase {
  protected:
    template<typename T> 
    T read(std::string name, const nlohmann::json& input,T defaultValue) {
      if (input.find(name) != input.end())
        return input[name];
      else
        return defaultValue;
    }

    bool readBool(std::string name, const nlohmann::json& input, bool defaultValue) {
      if (input.find(name) != input.end()) {
        if (input[name].is_boolean()) {
          return input[name];
        }
        else
          return input[name] > 0;
      }
      else
        return defaultValue;
    }
  };
}