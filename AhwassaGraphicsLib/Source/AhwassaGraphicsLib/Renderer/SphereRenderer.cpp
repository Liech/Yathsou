#include "AhwassaGraphicsLib/Renderer/SphereRenderer.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "glad/glad.h"

#include <glm/gtc/matrix_transform.hpp>

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/ShaderProgram.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Uniforms/UniformVecVec3.h"
#include "AhwassaGraphicsLib/Uniforms/UniformMat4.h"
#include "AhwassaGraphicsLib/Uniforms/UniformVecMat4.h"
#include "AhwassaGraphicsLib/BufferObjects/VAO.h"
#include "AhwassaGraphicsLib/BufferObjects/VBO.h"
#include "AhwassaGraphicsLib/BufferObjects/IBO.h"
#include "AhwassaGraphicsLib/Vertex/PositionNormalVertex.h"

#include "Sphere.h"
#include "AhwassaGraphicsLib/Util.h"


namespace Ahwassa {
  struct SphereRenderer::RenderVars {
    std::unique_ptr<VBO<PositionNormalVertex>> vbo;
    std::unique_ptr<VAO> vao;
    std::unique_ptr<IBO>                       ibo;
    std::unique_ptr<UniformVec3>         light ;
    std::unique_ptr<ShaderProgram>       shader;
    std::unique_ptr<UniformVecMat4>      models;
    std::unique_ptr<UniformVecVec3>      colors; 
    std::shared_ptr<Camera>              camera;

    virtual ~RenderVars() {}
  };

  SphereRenderer::SphereRenderer(std::shared_ptr<Camera> camera) {
    _vars = std::make_shared<SphereRenderer::RenderVars>();
    _vars->camera = camera;
    _lightDir = glm::normalize(glm::vec3(25, 31, -21));
    _bufferSize = (Util::maxUniformAmount()-10) / 2;
    makeModelArray(_bufferSize);
    makeShader();
  }

  glm::vec3 SphereRenderer::getLightDir()const {
    return _lightDir;
  }

  void SphereRenderer::setLightDir(const glm::vec3& pos) {
    _lightDir = pos;
  }

  void SphereRenderer::draw() {

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    _vars->shader->bind();
    _vars->camera->bind();

    std::vector<glm::mat4> matrices;
    std::vector<glm::vec3> colors  ;
    matrices.resize(_bufferSize);
    colors  .resize(_bufferSize);

    std::vector<size_t> destroyed;
    destroyed.resize(40);
    size_t destroyedIndex = 0;
    size_t current = 0;
    for (size_t i = 0; i < _instances.size(); i++) {
      auto rec = _instances[i].lock();
      if (rec) {
        if (current == _bufferSize) {
          shaderCall(matrices, colors, current);
          current = 0;
        }
        matrices[current] = rec->matrix  ();
        colors  [current] = rec->getColor().to3();
        current++;
      }
      else {
        if (destroyedIndex >= destroyed.size())
          destroyed.push_back(0);
        destroyed[destroyedIndex] = i;
        destroyedIndex++;
      }
    }
    for (size_t i = destroyedIndex; i > 0; i--)
      _instances.erase(_instances.begin() + i);


    shaderCall(matrices,colors,current);

    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
  }

  void SphereRenderer::makeModelArray(size_t bufferSize) {
    _vars->models = std::make_unique<UniformVecMat4>("models", bufferSize);
    _vars->colors = std::make_unique<UniformVecVec3>("colors", bufferSize);
  }

  void SphereRenderer::makeShader() {
    std::cout << "Load Shader" << std::endl;
    genSphere();

    std::string vertex_shader_source = R"(
      out vec3 clr;
      out vec3 nrm;
      void main() {
      
        mat4 view = )" + _vars->camera->getName() + R"(Projection *  )" + _vars->camera->getName() + R"(View;
        gl_Position = view *  models[gl_InstanceID] *vec4(position , 1.0);
        clr = colors[gl_InstanceID];
        nrm = normal;
      }
   )";

    std::string fragment_shader_source = R"(
     in vec3 clr;
     in vec3 nrm;
     
     out vec4 frag_color;
     void main() {
       float ambientStrength = 0.5;  
       float diffuseStrength = 0.5;
       float diff = max(dot(nrm, Light), 0.0) * diffuseStrength;
     
       vec4 result = vec4(clr,1) *  diff + vec4(clr,1) * ambientStrength;
       result[3] = 1;
     	frag_color = result;
     }
   )";
    std::vector<Uniform*> uniforms;

    std::vector<Uniform*> cameraUniforms = _vars->camera->getUniforms();
    uniforms.insert(uniforms.end(), cameraUniforms.begin(), cameraUniforms.end());
    _vars->light = std::make_unique<UniformVec3>("Light");
    _vars->light->setValue(glm::normalize(glm::vec3(0)));
    uniforms.push_back(_vars->light.get());
    uniforms.push_back(_vars->models.get());
    uniforms.push_back(_vars->colors.get());
    _vars->shader = std::make_unique<ShaderProgram>(PositionNormalVertex::getBinding(), uniforms, vertex_shader_source, fragment_shader_source);
  }

  void SphereRenderer::shaderCall(const std::vector<glm::mat4>& mats, const std::vector<glm::vec3>&clr, size_t amount) {
    _vars->light->setValue(_lightDir);
    _vars->models->setValue(mats);
    _vars->colors->setValue(clr);
    _vars->models->bind();
    _vars->colors->bind();
    _vars->ibo->drawInstanced(_vars->vao.get(),amount);
  }

  std::shared_ptr<Sphere> SphereRenderer::newSphere(const glm::vec3& pos, float size, Iyathuum::Color clr) {
    std::shared_ptr<Sphere> result = std::make_shared<Sphere>(pos,size,clr);
    _instances.push_back(result);
    return result;
  }

  //https://stackoverflow.com/questions/7687148/drawing-sphere-in-opengl-without-using-glusphere
  void SphereRenderer::genSphere()
  {
    std::vector<PositionNormalVertex> result;
    int uResolution = 15;
    int vResolution = 15;
    float r = 1;
    auto F = [](float u, float v, float r) {return glm::vec3(cos(u) * sin(v) * r, cos(v) * r, sin(u) * sin(v) * r); };
    auto triangle = [](glm::vec3 a, glm::vec3 b, glm::vec3 c) {};
    float startU = 0;
    float startV = 0;
    float endU = M_PI * 2;
    float endV = M_PI;
    float stepU = (endU - startU) / uResolution; // step size between U-points on the grid
    float stepV = (endV - startV) / vResolution; // step size between V-points on the grid
    for (int i = 0; i < uResolution; i++) { // U-points
      for (int j = 0; j < vResolution; j++) { // V-points
        float u = i * stepU + startU;
        float v = j * stepV + startV;
        float un = (i + 1 == uResolution) ? endU : (i + 1) * stepU + startU;
        float vn = (j + 1 == vResolution) ? endV : (j + 1) * stepV + startV;
        // Find the four points of the grid
        // square by evaluating the parametric
        // surface function
        glm::vec3 p0 = F(u, v, r);
        glm::vec3 p1 = F(u, vn, r);
        glm::vec3 p2 = F(un, v, r);
        glm::vec3 p3 = F(un, vn, r);
        // NOTE: For spheres, the normal is just the normalized
        // version of each vertex point; this generally won't be the case for
        // other parametric surfaces.
        // Output the first triangle of this grid square
        glm::vec3 offset(0, 0, 0);
        result.push_back(PositionNormalVertex(p0 + offset, -glm::cross(p0 - p2, p1)));
        result.push_back(PositionNormalVertex(p2 + offset, -glm::cross(p0 - p2, p1)));
        result.push_back(PositionNormalVertex(p1 + offset, -glm::cross(p0 - p2, p1)));
        result.push_back(PositionNormalVertex(p3 + offset, glm::cross(p3 - p1, p2)));
        result.push_back(PositionNormalVertex(p1 + offset, glm::cross(p3 - p1, p2)));
        result.push_back(PositionNormalVertex(p2 + offset, glm::cross(p3 - p1, p2)));
      }
    }
    std::vector<int> indices;
    indices.resize(result.size());
    for (size_t i = 0; i < result.size(); i++)
      indices[i] = i;
    _vars->ibo = std::make_unique<IBO>(indices);
    _vars->vbo = std::make_unique<VBO<PositionNormalVertex>>(result);
    _vars->vao = std::make_unique<VAO>(_vars->vbo.get());
  }
}