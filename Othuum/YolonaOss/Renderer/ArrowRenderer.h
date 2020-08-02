#pragma once

#include "../OpenGL/Loadable.h"
#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "../OpenGL/VBO.h"
#include "../OpenGL/VAO.h"
#include "IyathuumCoreLib/Singleton/Factory.h"
#include "../OpenGL/PositionNormalVertex.h"
#include "../OpenGL/Camera.h"
#include "../OpenGL/ShaderProgram.h"
namespace YolonaOss {
  namespace GL {
    class IBO;
    class UniformVec3;
    class UniformVec4;
    class UniformMat4;
  }
  class ArrowRenderer : public GL::Loadable {
    REGISTER(Loadable, ArrowRenderer, "ArrowRenderer", { "Main" })
    // Geerbt über Loadable
    virtual void load(GL::DrawSpecification* spec) override;
  public:
    static void start();
    static void end();
    static void drawArrow(glm::vec3 start, glm::vec3 dir, float scale, glm::vec4 color);
    static void draw(glm::mat4 mat, glm::vec4 color);
  private:
    static inline GL::DrawSpecification*                                    _spec; 
    static inline std::vector<int>                                          _indices;
    static inline std::unique_ptr<GL::UniformMat4>                          _mat;
    static inline std::unique_ptr<GL::UniformVec4>                          _color;
    static inline std::unique_ptr<GL::VBO<GL::PositionNormalVertex>>        _vbo;
    static inline std::unique_ptr<GL::VAO<GL::PositionNormalVertex>>        _vao;
    static inline std::unique_ptr<GL::IBO>                                  _ibo;
    static inline std::unique_ptr<GL::ShaderProgram>                        _shader;
    static inline std::unique_ptr<GL::UniformVec3>                          _light;
    static inline std::unique_ptr<GL::Camera>                               _camera;
  };
}