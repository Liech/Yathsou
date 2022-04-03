//#pragma once
//
//#include <glm/glm.hpp>
//#include "IyathuumCoreLib/Singleton/Factory.h"
//#include <vector>
//
//
//namespace YolonaOss
//{
//  namespace GL
//  {
//    class Camera;
//    class UniformVec3;
//    class UniformVec4;
//    class UniformMat4;
//    class ShaderProgram;
//    struct PositionNormalVertex;
//  }
//  struct MeshPimpl;
//  class Mesh
//  {
//  public:
//    Mesh(const std::vector<GL::PositionNormalVertex>& vertecies, const std::vector<int>& indicies);
//    void draw() const;
//  private:
//    std::unique_ptr<MeshPimpl> _p;
//  };
//
//  class MeshRenderer {
//  public:
//    virtual void load(GL::DrawSpecification*) override;
//    static void start();
//    static void end();
//    static void draw(const Mesh& mesh, glm::mat4 transformation, glm::vec4 color);
//
//  private:
//    static inline std::unique_ptr<GL::Camera>                               _camera;
//    static inline GL::DrawSpecification*                                    _spec  ;
//    static inline std::unique_ptr<GL::UniformVec3>                          _light ;
//    static inline std::unique_ptr<GL::UniformMat4>                          _mat   ;
//    static inline std::unique_ptr<GL::UniformVec4>                          _color ;
//    static inline std::unique_ptr<GL::ShaderProgram>                        _shader;
//  };
//}