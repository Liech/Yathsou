#pragma once

#include "../OpenGL/Loadable.h"
#include "glm/glm.hpp"

namespace YolonaOss {
  class LineRenderer : public GL::Loadable {
    // Geerbt über Loadable
    virtual void load(GL::DrawSpecification* spec) override;

    static void start();
    static void end();
    void drawLine(glm::vec3 start, glm::vec3 end, float thickness, glm::vec4 color);

  private:
    GL::DrawSpecification* _spec;
  };
}