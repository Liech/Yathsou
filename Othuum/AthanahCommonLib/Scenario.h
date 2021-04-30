#pragma once

#include <string>

namespace Athanah {
  enum class ScenarioType {
    Campaign,
    Skirmish
  };

  class Scenario {
  public:
    Scenario(const std::string& path);

    const std::string& name       ();
    int                width      ();
    int                height     ();
    std::string        description();
    ScenarioType       type       ();
    const std::string& map        ();
    const std::string& save       ();
    const std::string& script     ();
    const std::string& preview    ();
  private:
    std::string _path;

    std::string  _name       ;
    std::string  _description;
    int          _width      ;
    int          _height     ;
    ScenarioType _type       ;

    std::string  _map        ;
    std::string  _save       ;
    std::string  _script     ;
    std::string  _preview    ;
  };
}