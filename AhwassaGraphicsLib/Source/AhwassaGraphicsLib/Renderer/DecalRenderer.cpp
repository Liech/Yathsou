#include "AhwassaGraphicsLib/Renderer/DecalRenderer.h"

#include <iostream>
#include "glad/glad.h"

#include <glm/gtc/matrix_transform.hpp>

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/ShaderProgram.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Uniforms/UniformVec2.h"
#include "AhwassaGraphicsLib/Uniforms/UniformVecVec3.h"
#include "AhwassaGraphicsLib/Uniforms/UniformMat4.h"
#include "AhwassaGraphicsLib/Uniforms/UniformVecMat4.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AhwassaGraphicsLib/BufferObjects/VAO.h"
#include "AhwassaGraphicsLib/BufferObjects/VBO.h"
#include "AhwassaGraphicsLib/BufferObjects/IBO.h"
#include "AhwassaGraphicsLib/Vertex/PositionNormalVertex.h"

#include "Primitives/Decal.h"
#include "AhwassaGraphicsLib/Util.h"


namespace Ahwassa {
  struct DecalRenderer::RenderVars {
    std::unique_ptr<VBO<PositionNormalVertex>> vbo;
    std::unique_ptr<VAO>                       vao;
    std::unique_ptr<IBO>                       ibo;
    std::unique_ptr<UniformVec3>               light;
    std::unique_ptr<UniformVec2>               resolution;
    std::unique_ptr<ShaderProgram>             shader;
    std::unique_ptr<UniformVecMat4>            models;
    std::unique_ptr<UniformVecMat4>            invers;
    std::unique_ptr<UniformVecVec3>            colors;
    std::shared_ptr<Camera>                    camera;
    std::shared_ptr<Texture>                   texture;
    std::shared_ptr<Texture>                   depth;

    virtual ~RenderVars() {}
  };

  DecalRenderer::DecalRenderer(std::shared_ptr<Camera> camera) {
    _vars = std::make_shared<DecalRenderer::RenderVars>();
    _lightDir = glm::normalize(glm::vec3(25, 31, -21));
    _vars->camera = camera;
    _bufferSize = (Util::maxUniformAmount() - 10) / 2;
    makeModelArray(_bufferSize);
    makeShader();
  }

  void DecalRenderer::draw(std::shared_ptr<Texture> depthTexture) {

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    _vars->depth->setTextureID(depthTexture->getTextureID());
    _vars->shader->bind();
    _vars->camera->bind();

    std::vector<glm::mat4> matrices;
    std::vector<glm::mat4> invers;
    std::vector<glm::vec3> colors;
    matrices.resize(_bufferSize);
    colors.resize(_bufferSize);
    invers.resize(_bufferSize);

    std::vector<size_t> destroyed;
    destroyed.resize(40);
    size_t destroyedIndex = 0;
    size_t current = 0;
    for (size_t i = 0; i < _instances.size(); i++) {
      auto rec = _instances[i].lock();
      if (rec) {
        if (current == _bufferSize) {
          shaderCall(matrices,invers, colors, current);
          current = 0;
        }
        matrices[current] = rec->matrix();
        invers  [current] = glm::inverse(_vars->camera->getViewMatrix() * rec->matrix());
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


    shaderCall(matrices,invers, colors, current);

    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
  }

  void DecalRenderer::clear() {
    _instances.clear();
  }


  void DecalRenderer::makeModelArray(size_t bufferSize) {
    _vars->models = std::make_unique<UniformVecMat4>("models", bufferSize);
    _vars->invers = std::make_unique<UniformVecMat4>("invers", bufferSize);
    _vars->colors = std::make_unique<UniformVecVec3>("colors", bufferSize);
  }

  void DecalRenderer::makeShader() {
    //std::cout << "Load Shader" << std::endl;
    makeGeometry();

    std::string vertex_shader_source = R"(
      out vec3 clr;
      out vec3 nrm;
      out vec4 FragPos;
      void main() {
      
        mat4 view = )" + _vars->camera->getName() + R"(Projection *  )" + _vars->camera->getName() + R"(View;
        gl_Position = view *  models[gl_InstanceID] *vec4(position , 1.0);
        clr = colors[gl_InstanceID];
        nrm = normal;
        FragPos = gl_Position;
      }
   )";

    //https://github.com/diharaw/deferred-decals/blob/master/src/shader/decals_fs.glsl
    std::string fragment_shader_source = R"(
     in vec3 clr;
     in vec3 nrm;
     in vec4 FragPos;
     
     out vec4 frag_color;
     
     vec3 world_position_from_depth(vec2 screen_pos, float ndc_depth)
     {
         mat4 view = )" + _vars->camera->getName() + R"(Projection *  )" + _vars->camera->getName() + R"(View;
         // Remap depth to [-1.0, 1.0] range.
         float depth = ndc_depth * 2.0 - 1.0;     
         // // Create NDC position.
         vec4 ndc_pos = vec4(screen_pos, depth, 1.0);     
         // Transform back into world position.
         vec4 world_pos = view * ndc_pos;     
         // Undo projection.
         world_pos = world_pos / world_pos.w;     
         return world_pos.xyz;
     }

     void main() {
       vec2 screen_pos = FragPos.xy / FragPos.w;
       vec2 tex_coords = screen_pos * 0.5 + 0.5;
       float depth     = texture(Depth, tex_coords).x;
       vec3  world_pos = world_position_from_depth(screen_pos, depth);

       //vec4 ndc_pos = u_DecalVP * vec4(world_pos, 1.0);
       //ndc_pos.xyz /= ndc_pos.w;
       //
       //ndc_pos.xy *= u_AspectRatio;
       //
       //if (ndc_pos.x < -1.0 || ndc_pos.x > 1.0 || ndc_pos.y < -1.0 || ndc_pos.y > 1.0)
       //    discard;

       float ambientStrength = 0.5;  
       float diffuseStrength = 0.5;
       float diff = max(dot(nrm, Light), 0.0) * diffuseStrength;
     
       vec4 result = vec4(clr,1) *  diff + vec4(clr,1) * ambientStrength;
       result[3] = 1;
     	 frag_color = result;
       frag_color.r = depth;
     }
   )";
    std::vector<Uniform*> uniforms;

    std::vector<Uniform*> cameraUniforms = _vars->camera->getUniforms();
    uniforms.insert(uniforms.end(), cameraUniforms.begin(), cameraUniforms.end());
    _vars->light = std::make_unique<UniformVec3>("Light");
    _vars->light->setValue(glm::normalize(glm::vec3(0)));
    _vars->texture = std::make_shared<Texture>("decalTexture", 0);
    _vars->texture->setBindable(false);
    _vars->depth = std::make_shared<Texture>("Depth", 0);
    _vars->depth->setBindable(false);
    uniforms.push_back(_vars->light.get());
    uniforms.push_back(_vars->models.get());
    uniforms.push_back(_vars->invers.get());
    uniforms.push_back(_vars->colors.get());
    uniforms.push_back(_vars->texture.get());
    uniforms.push_back(_vars->depth.get());
    _vars->shader = std::make_unique<ShaderProgram>(PositionNormalVertex::getBinding(), uniforms, vertex_shader_source, fragment_shader_source);
  }

  void DecalRenderer::shaderCall(const std::vector<glm::mat4>& mats, const std::vector<glm::mat4>& inverts, const std::vector<glm::vec3>& clr, size_t amount) {
    _vars->light->setValue(_lightDir);
    _vars->models->setValue(mats);
    _vars->invers->setValue(inverts);
    _vars->colors->setValue(clr);
    _vars->models->bind();
    _vars->invers->bind();
    _vars->colors->bind();
    _vars->ibo->drawInstanced(_vars->vao.get(), amount);
  }

  std::shared_ptr<Decal> DecalRenderer::newDecal(const glm::mat4& mat, Iyathuum::Color clr) {
    std::shared_ptr<Decal> result = std::make_shared<Decal>(mat, clr);
    _instances.push_back(result);
    return result;
  }

  void DecalRenderer::makeGeometry() {
    std::vector<PositionNormalVertex> input;
    float start = 0;
    float end = 1;
    //front
    input.push_back(PositionNormalVertex(glm::vec3(start, start, end), glm::vec3(0, 0, 1)));
    input.push_back(PositionNormalVertex(glm::vec3(end, start, end), glm::vec3(0, 0, 1)));
    input.push_back(PositionNormalVertex(glm::vec3(end, end, end), glm::vec3(0, 0, 1)));
    input.push_back(PositionNormalVertex(glm::vec3(start, end, end), glm::vec3(0, 0, 1)));

    //right
    input.push_back(PositionNormalVertex(glm::vec3(end, end, end), glm::vec3(1, 0, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(end, end, start), glm::vec3(1, 0, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(end, start, start), glm::vec3(1, 0, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(end, start, end), glm::vec3(1, 0, 0)));

    //back
    input.push_back(PositionNormalVertex(glm::vec3(start, start, start), glm::vec3(0, 0, -1)));
    input.push_back(PositionNormalVertex(glm::vec3(end, start, start), glm::vec3(0, 0, -1)));
    input.push_back(PositionNormalVertex(glm::vec3(end, end, start), glm::vec3(0, 0, -1)));
    input.push_back(PositionNormalVertex(glm::vec3(start, end, start), glm::vec3(0, 0, -1)));

    //left
    input.push_back(PositionNormalVertex(glm::vec3(start, start, start), glm::vec3(-1, 0, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(start, start, end), glm::vec3(-1, 0, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(start, end, end), glm::vec3(-1, 0, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(start, end, start), glm::vec3(-1, 0, 0)));

    //upper
    input.push_back(PositionNormalVertex(glm::vec3(end, end, end), glm::vec3(0, 1, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(start, end, end), glm::vec3(0, 1, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(start, end, start), glm::vec3(0, 1, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(end, end, start), glm::vec3(0, 1, 0)));

    //bottom
    input.push_back(PositionNormalVertex(glm::vec3(start, start, start), glm::vec3(0, -1, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(end, start, start), glm::vec3(0, -1, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(end, start, end), glm::vec3(0, -1, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(start, start, end), glm::vec3(0, -1, 0)));

    //note every face of the cube is on a single line
    auto indices = std::vector<int>{
      0,  1,  2,  0,  2,  3,   //front
      4,  5,  6,  4,  6,  7,   //right
      8,  9,  10, 8,  10, 11,  //back
      12, 13, 14, 12, 14, 15,  //left
      16, 17, 18, 16, 18, 19,  //upper
      20, 21, 22, 20, 22, 23 }; //bottom

    _vars->ibo = std::make_unique<IBO>(indices);
    _vars->vbo = std::make_unique<VBO<PositionNormalVertex>>(input);
    _vars->vao = std::make_unique<VAO>(_vars->vbo.get());
  }

}