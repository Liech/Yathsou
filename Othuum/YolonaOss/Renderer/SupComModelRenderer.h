#pragma once

#include "../OpenGL/Loadable.h"
#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "IyathuumCoreLib/Singleton/Factory.h"
#include <vector>


namespace YolonaOss
{
  namespace GL
  {
    class Camera;
    class UniformVec3;
    class UniformVec4;
    class UniformMat4;
    class ShaderProgram;
    class Texture;
    struct SupComVertex;
  }
  class MeshPimpl;
  class SupComGLMesh
  {
  public:
    SupComGLMesh(const std::vector<GL::SupComVertex>& vertecies, const std::vector<int>& indicies);
    void setAlbedo(std::shared_ptr<GL::Texture>& texture);
    void setInfo  (std::shared_ptr<GL::Texture> texture);
    void setNormal(std::shared_ptr<GL::Texture> texture);
    void draw() const;

    int getAlbedoID()const;
    int getInfoID()  const;
    int getNormalID()const;
  private:
    std::unique_ptr<MeshPimpl> _p;
  };

  class SupComModelRenderer : public GL::Loadable {
    REGISTER(Loadable, SupComModelRenderer, "SupComModelRenderer", { "Main" })
  public:
    virtual void load(GL::DrawSpecification*) override;
    static void start();
    static void end();
    static void draw(const SupComGLMesh& mesh, glm::mat4 transformation);

  private:
    static inline std::unique_ptr<GL::Camera>                               _camera;
    static inline GL::DrawSpecification*                                    _spec  ;
    static inline std::unique_ptr<GL::UniformVec3>                          _light ;
    static inline std::unique_ptr<GL::UniformMat4>                          _mat   ;
    static inline std::unique_ptr<GL::ShaderProgram>                        _shader;
    static inline std::unique_ptr<GL::Texture>                              _albedo;
    static inline std::unique_ptr<GL::Texture>                              _info  ;
    static inline std::unique_ptr<GL::Texture>                              _normal;
    static inline std::unique_ptr<GL::UniformVec4>                          _color;
  };
}