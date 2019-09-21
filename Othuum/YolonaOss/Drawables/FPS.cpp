#include "FPS.h"

#include "glad/glad.h"
#include "Renderer/TextRenderer.h"

namespace YolonaOss {
  FPS::FPS()
  {
  }


  FPS::~FPS()
  {
  }

  void FPS::load(GL::DrawSpecification* spec)
  {
    _spec = spec;
    _lastMeasurement = std::chrono::high_resolution_clock::now();
  }

  void FPS::draw()
  {
    auto currentMeasurment = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = currentMeasurment - _lastMeasurement;
    double seconds = diff.count();
    _avFPS = (1.0 / seconds) * 0.005f + 0.995 * _avFPS;
    TextRenderer::startTextRender();
    TextRenderer::drawText("Frametime: " + std::to_string(seconds), _spec->width - 250.0f, _spec->height - 40.0f, 0.5f, glm::vec3(0, 0, 0));
    TextRenderer::drawText("FPS:            " + std::to_string((int)_avFPS), _spec->width - 250.0f, _spec->height - 20.0f, 0.5f, glm::vec3(0, 0, 0));
    TextRenderer::endTextRender();


    _lastMeasurement = currentMeasurment;
  }
}