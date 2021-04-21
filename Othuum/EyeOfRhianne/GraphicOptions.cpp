#include "GraphicOptions.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"

GraphicOptions::GraphicOptions(Ahwassa::Window* w) {
  _window = w;

  _showHide = std::make_shared<Ahwassa::Button>("Graphic", Iyathuum::glmAABB<2>(glm::vec2(300, w->getHeight() - 50), glm::vec2(300, 50)), [&]() {
    
  }, w);
}

void GraphicOptions::draw() {
  _showHide->draw();
}

