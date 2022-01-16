#pragma once

#include "AezeselFileIOLib/lib/json.hpp"

namespace Superb {
  class FormationDialog;

  class NonGame {
  public:
    NonGame();
    virtual ~NonGame() = default;

    void menu();
    void preDraw();
    void start();
    void save(nlohmann::json&);
    void load(nlohmann::json&);

  private:
    bool _dearIMGUIDemoWindow = false;

    std::unique_ptr<FormationDialog> _formationDialog;
  };
}