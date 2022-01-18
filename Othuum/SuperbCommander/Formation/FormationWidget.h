#pragma once

#include <memory>

namespace Ahwassa {
  class Rendertarget;
  class Window;
  class BasicRectangleRenderer;
}

namespace Superb {
  class FormationWidget{
  public:
    FormationWidget(Ahwassa::Window&);
    virtual ~FormationWidget() = default;

    void menu();
    void preDraw();
    
  private:
    int _resolutionX = 400;
    int _resolutionY = 400;    

    Ahwassa::Window& _window;
    std::unique_ptr<Ahwassa::Rendertarget>      _canvas  ;
    std::unique_ptr<Ahwassa::BasicRectangleRenderer> _renderer;
  };
}