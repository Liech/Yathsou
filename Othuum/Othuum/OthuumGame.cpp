#include "OthuumGame.h"

#include "UyanahGameServer/Scene.h"

OthuumGame::OthuumGame() {
  _client = nullptr;
  _scene  = std::make_shared<Uyanah::Scene>();
}
