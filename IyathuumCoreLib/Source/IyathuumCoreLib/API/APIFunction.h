#pragma once

#include <string>
#include <functional>
#include <nlohmann/json.hpp>

namespace Iyathuum {
  /// <summary>
  /// std::function with a name and description strapped on
  /// </summary>
  class APIFunction {
    public:
      APIFunction(const std::string& name, std::function<nlohmann::json(const nlohmann::json&)>);
      void setDescription(const std::string&);

      nlohmann::json call(const nlohmann::json&) const;
      std::string    getDescription() const;
      std::string    getName() const;
    private:
      std::function<nlohmann::json(const nlohmann::json&)> _func       ;
      std::string                                          _name       ;
      std::string                                          _description;
  };
}