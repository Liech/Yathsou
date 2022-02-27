#include "FPS.h"

#include "glad/glad.h"
#include "Renderer/BasicTextRenderer.h"
#include "Core/Window.h"

namespace Ahwassa {
  FPS::FPS(Window* w) : Drawable(w)
  {
    _lastMeasurement = std::chrono::high_resolution_clock::now();
    _renderer = std::make_unique<BasicTextRenderer>(w);
  }


  FPS::~FPS()
  {
  }

  void FPS::draw()
  {
    auto currentMeasurment = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = currentMeasurment - _lastMeasurement;
    double seconds = diff.count();
    _avFPS = (1.0 / seconds) * 0.005f + 0.995 * _avFPS;
    _renderer->start();
    _renderer->drawText("Frametime: " + std::to_string(seconds)         , glm::vec2(getWindow()->getWidth() - 250.0f, getWindow()->getHeight() - 40.0f), 0.5f);
    _renderer->drawText("FPS:            " + std::to_string((int)_avFPS), glm::vec2(getWindow()->getWidth() - 250.0f, getWindow()->getHeight() - 20.0f), 0.5f);
    _renderer->end();


    _lastMeasurement = currentMeasurment;
  }
}