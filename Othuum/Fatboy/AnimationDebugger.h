#pragma once

#include <memory>
#include <string>
#include <vector>

#include "AhwassaGraphicsLib/Drawables/Drawable.h"

namespace Ahwassa
{
  class Window;
  class ListLayout;
  class Mesh;
  class SupComGLMesh;
  class BasicBoxRenderer;
  class BasicTextRenderer;
}

class SupComModel;
namespace Haas
{
  class ScriptEngine;
}

namespace Fatboy{
  class AnimationDebugger : public Ahwassa::Drawable {
  public:
    AnimationDebugger(Ahwassa::Window*);

    virtual void draw() override;
    void update();

  private:
    void loadMenu();
    void loadModel();
    void loadScript();

    void drawModel();
    void renderStuff();
    void renderStuff2();

    std::vector<std::shared_ptr<Ahwassa::Drawable>>     _preDrawables;
    std::vector<std::shared_ptr<Ahwassa::Drawable>>     _postDrawables;
    
    std::shared_ptr<Ahwassa::ListLayout>  _layout;

    std::shared_ptr< SupComModel> _modl;
    Ahwassa::SupComGLMesh* _scMesh;
    std::shared_ptr<Haas::ScriptEngine> _script;
    std::shared_ptr<Ahwassa::BasicBoxRenderer> _box;
    std::shared_ptr<Ahwassa::BasicTextRenderer> _text;
    std::string _animName;
    std::string _unitName;

    bool _keyPressed = false;
  };
}