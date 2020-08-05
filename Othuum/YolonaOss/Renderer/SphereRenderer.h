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
  class SphereRenderer : public GL::Loadable {
    REGISTER(Loadable, SphereRenderer, "SphereRenderer", { "Main" })
    // Geerbt �ber Loadable
    virtual void load(GL::DrawSpecification* spec) override;
  public:
    static void start();
    static void end();
    static void drawLine(glm::vec3 start, glm::vec3 end, float thickness, glm::vec4 color);
    static void drawDot(glm::vec3 start, glm::vec3 size, glm::vec4 color);
    static void drawSphere(glm::vec3 start, glm::vec3 size, glm::vec4 color);
    static void draw(glm::mat4 mat, glm::vec4 color);
  private:
    std::vector<GL::PositionNormalVertex> genSphere();

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