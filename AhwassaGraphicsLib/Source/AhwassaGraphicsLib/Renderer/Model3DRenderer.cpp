#include "Model3DRenderer.h"

#include <IyathuumCoreLib/BaseTypes/Model3D.h>
#include <AhwassaGraphicsLib/Vertex/Model3DVertex.h>
#include <AhwassaGraphicsLib/Uniforms/SSBOmat4.h>
#include <AhwassaGraphicsLib/Uniforms/Texture.h>
#include <AhwassaGraphicsLib/Uniforms/SSBOmat4.h>
#include <AhwassaGraphicsLib/Util.h>
#include <AhwassaGraphicsLib/BufferObjects/Mesh.h>

namespace Ahwassa {
  Model3DRenderer::Model3DRenderer(std::shared_ptr<Ahwassa::Camera> camera) : 
    Ahwassa::RendererTemplate<Model3DRendererMesh>(camera,Ahwassa::Model3DVertex::getBinding()){
    _matrices.resize(bufferSize());
    _rotationMatrices.resize(bufferSize());
  }

  Model3DRenderer::~Model3DRenderer() {

  }

  std::string Model3DRenderer::vertexShader() {
    return R"(
     out vec2 texCoords;
     out vec3 fragPos  ;
     out vec3 Normal   ;

     void main() {
        mat4 view = )" + getCamera()->getName() + R"(Projection *  )" + getCamera()->getName() + R"(View;
        mat4 world = models[gl_InstanceID];
        gl_Position = view * world * vec4(position , 1.0);
        fragPos   = (world * vec4(position , 1.0)).xyz;
        world[3] = vec4(0, 0, 0, 1); //cancel translation

        Normal    = (modelsRot[gl_InstanceID] * vec4(normal, 1.0)).xyz;
     }
    )";
  }

  std::string Model3DRenderer::fragmentShader() {
    return R"(
     layout (location = 0) out vec4 gPosition;
     layout (location = 1) out vec4 gNormal;
     layout (location = 2) out vec4 gAlbedoSpec;
     layout (location = 3) out vec4 gSpecial;

     in vec2 texCoords;
     in vec3 fragPos  ;
     in vec3 Normal   ;

     void main() {
       gAlbedoSpec.rgb = vec3(1,1,1);
       gAlbedoSpec.a = 1;
       gNormal.rgb = normalize(Normal).rgb; 
       gNormal.a = 1;
       gPosition.rgb = fragPos.rgb; 	
       gPosition.a = 1;

       gSpecial.r = 0; // reflection
       gSpecial.g = 0; // bloom
       gSpecial.b = 0; // specular
       gSpecial.a = 1; // unused
     }
    )";
  }

  std::vector<std::shared_ptr<Ahwassa::Uniform>> Model3DRenderer::initUniforms() {
    _models    = std::make_shared<Ahwassa::SSBOmat4>("models"   , bufferSize());
    _modelsRot = std::make_shared<Ahwassa::SSBOmat4>("modelsRot", bufferSize());
    return std::vector<std::shared_ptr<Ahwassa::Uniform>>{_models,_modelsRot};
  }

  void Model3DRenderer::vectorize(const size_t& index, std::shared_ptr<Model3DRendererMesh> m) {
    _matrices[index] = m->transformation;
    _rotationMatrices[index] = Ahwassa::Util::removeTranslation(m->transformation);
  }

  void Model3DRenderer::bind() {
    _models->setData(_matrices);
    _modelsRot->setData(_rotationMatrices);
    _models->bind();
    _modelsRot->bind();
  }

  std::shared_ptr<Ahwassa::IMesh> Model3DRenderer::meshFromModel3D(const Iyathuum::Model3D& modl) {

    if (modl.meshes.size() != 1)
      throw std::runtime_error(":(");

    std::vector<int> indices;
    indices.resize(modl.meshes[0].indices.size());
    for(size_t i =0;i < modl.meshes[0].indices.size();i++)
      indices[i] = modl.meshes[0].indices[i];

    std::vector< Ahwassa::Model3DVertex> vertices;
    auto& v = modl.meshes[0].vertices;
    vertices.resize(v.size());
    for (int i = 0; i < v.size(); i++)
      vertices[i] = Ahwassa::Model3DVertex(v[i].position, v[i].normal, v[i].bitangent,v[i].tangent,v[i].texCoords,glm::vec4(-1,-1,-1,1),glm::vec4());
    
    for (size_t bone = 0; bone < modl.meshes[0].bone.size(); bone++) {
      auto& b = modl.meshes[0].bone[bone];
      for (size_t i = 0; i < b.index.size(); i++) {
        vertices[b.index[i]].boneIndex .x = bone;
        vertices[b.index[i]].boneWeight.x = b.weight[i];
        vertices[b.index[i]].boneIndex.y = 0;
        vertices[b.index[i]].boneIndex.z = 0;
        vertices[b.index[i]].boneIndex.w = 0;
      }
    }

    auto result = std::make_shared<Ahwassa::Mesh<Ahwassa::Model3DVertex>>(vertices,indices);
    return result;
  }
}