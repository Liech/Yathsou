#include "Visualization.h"

#include "Game.h"

#include "AthanahCommonLib/Map/MapRenderer.h"

namespace Superb {
  Visualization::Visualization(const Ahwassa::Window& w, const Game& g) : _window(w), _game(g) {
    //_mapRenderer = std::make_shared<Athanah::MapRenderer>(window->camera(), textures, gamedata);

  }

  void Visualization::menu() {

  }

  void Visualization::draw() {
    gather();

    if (_mapRenderer && _mapMesh)
      _mapRenderer->draw(*_mapMesh);
  }

  void Visualization::gather() {

  }
}