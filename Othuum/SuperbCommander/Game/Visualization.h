#pragma once

#include <memory>
#include <string>

#include "IyathuumCoreLib/lib/glm/glm.hpp"

namespace Athanah {
  class MapRenderer;
}

namespace Ahwassa {
  class IMesh;
  class Window;
  class Background;
  class DeferredComposer;
  class BasicTexture2DRenderer;
}

namespace Superb {
  class Game;
  class UnitsVisualization;
  class PhysicsDebugView;

  enum class RendererModes {
    Result, Depth, gPosition, gNormal, gAlbedoSpec, gSpecial
  };

  class Visualization {
  public:
    Visualization(Ahwassa::Window&, Game&);
    virtual ~Visualization() = default;

    void menu();
    void draw();
    void drawLastLayer();

  private:
    std::string getRendererNames(RendererModes);

  private:
    const Game&                                      _game;
    const Ahwassa::Window&                           _window;

    //defered renderering
    std::unique_ptr<Ahwassa::DeferredComposer>       _composer;
    std::shared_ptr<Ahwassa::BasicTexture2DRenderer> _textureRenderer;
    RendererModes                                    _currentRendererMode = RendererModes::Result;

    //background
    std::unique_ptr<Ahwassa::Background> _background;
    glm::vec3                            _backgroundColor = glm::vec3(0.2f, 0.3f, 0.3f);

    //map
    bool _drawTerrain = true;
    std::unique_ptr<Athanah::MapRenderer> _mapRenderer = nullptr;
    std::shared_ptr<Ahwassa::IMesh>       _mapMesh     = nullptr;

    //units
    bool _debugUnitView = true;
    bool _unitsView = true;
    std::unique_ptr<UnitsVisualization> _unitsVis;

    //physic
    bool _debugPhysicView = false;
    std::unique_ptr<Superb::PhysicsDebugView> _physicDebug;
  };
}