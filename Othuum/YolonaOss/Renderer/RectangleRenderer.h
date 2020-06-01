#pragma once

//#include "structs/Factory.h"
#include "../OpenGL/Loadable.h"
#include <iostream>
#include "IyathuumCoreLib/Singleton/Factory.h"
#include "glm/glm.hpp"
#include "IyathuumCoreLib/BaseTypes/AABB.h"
#include <memory>

#include <map>
#include "../OpenGL/VAO.h"
#include "../OpenGL/VBO.h"
#include "../OpenGL/ShaderProgram.h"
#include "../OpenGL/PositionVertex.h"

namespace YolonaOss {
  namespace GL {
    class ShaderProgram;
    class UniformMat4;
    class UniformVec3;
  }

  class RectangleRenderer : public GL::Loadable {
    REGISTER(Loadable, RectangleRenderer, "RectangleRenderer", { "Main" })
  public:
    RectangleRenderer() {}
    virtual ~RectangleRenderer() {}
    static void start();
    static void end();
    static void drawRectangle(glm::vec2 pos, glm::vec2 size, glm::vec3 color);
    static void drawRectangle(Iyathuum::AABB<2> box, glm::vec3 color);
    static void setClippingRectangle(Iyathuum::AABB<2> box);
    static void disableClipping(Iyathuum::AABB<2> box);

    virtual void load(GL::DrawSpecification*) override;

  private:
    struct RenderVars {
      std::unique_ptr<GL::VBO<GL::PositionVertex>>   vbo;
      std::unique_ptr<GL::VAO<GL::PositionVertex>>   vao;
      std::unique_ptr<GL::ShaderProgram>              shader;
      GL::DrawSpecification* spec;
      std::unique_ptr<GL::UniformMat4>                projection;
      std::unique_ptr<GL::UniformVec3>                color;
    };

    void makeShader();

    static inline bool              _alreadyLoaded   = false;
    static inline bool              _inRenderProcess = false;
    static inline bool              _clipping        = false;
    static inline Iyathuum::AABB<2> _clippingBox;
    static RenderVars               _vars;

  };
}
