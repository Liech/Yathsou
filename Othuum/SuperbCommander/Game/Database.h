#pragma once

#include <string>
#include <memory>
#include "AezeselFileIOLib/lib/json.hpp"

namespace Athanah {
  class Gamedata;
}

namespace Superb {
  class Database {
  public:
    Database();
    virtual ~Database() = default;

    void menu();
    void save(nlohmann::json&);
    void load(nlohmann::json&);
    void start();

    Athanah::Gamedata& gamedata();
    std::string supComPath();
  private:
    bool        _useSCDData = false;
    std::string _supComPath = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Supreme Commander Forged Alliance";

    std::unique_ptr<Athanah::Gamedata> _gamedata;
  };
}