#pragma once

#include <memory>
#include <string>
#include "AezeselFileIOLib/lib/json.hpp"
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
    void save(nlohmann::json&);
    void load(nlohmann::json&);
    void start();

  private:
    std::string getRendererNames(RendererModes);

  private:
    Game&                                      _game;
    Ahwassa::Window&                           _window;

    //defered renderering
    std::unique_ptr<Ahwassa::DeferredComposer>       _composer;
    std::shared_ptr<Ahwassa::BasicTexture2DRenderer> _textureRenderer;
    RendererModes                                    _currentRendererMode = RendererModes::Result;
    int _screenWidth  = 700;
    int _screenHeight = 700;

    //background
    std::unique_ptr<Ahwassa::Background> _background;
    glm::vec3                            _backgroundColor = glm::vec3(0.2f, 0.3f, 0.3f);

    //map
    bool _drawTerrain = true;
    std::unique_ptr<Athanah::MapRenderer> _mapRenderer = nullptr;
    std::shared_ptr<Ahwassa::IMesh>       _mapMesh     = nullptr;

    //units
    bool _debugUnitView = true;
    bool _unitsView     = true;
    std::unique_ptr<UnitsVisualization> _unitsVis;

    //physic
    bool _debugPhysicView = false;
    std::unique_ptr<Superb::PhysicsDebugView> _physicDebug;
  };
}