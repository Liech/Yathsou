#pragma once

#include <memory>

namespace Ahwassa {
  class Rendertarget;
}

namespace Superb {
  class FormationWidget{
  public:
    FormationWidget();
    virtual ~FormationWidget() = default;

    void menu();
    void preDraw();


  private:
    int _resolutionX = 200;
    int _resolutionY = 200;

    std::unique_ptr<Ahwassa::Rendertarget> _canvas;
    
  };
}