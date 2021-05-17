#pragma once

#include <vector>
#include <string>

#include "IyathuumCoreLib/lib/glm/glm.hpp"


struct aiNode;
struct aiScene;
struct aiMaterial;
struct aiMesh;

namespace Aezesel {
  struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
  };

  class Mesh3D {
  public:
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<std::string>  textures;
  };

  class Model3D {
  public:
    Model3D(const std::string& file);

    std::vector<Mesh3D> meshes   ;
    std::string         directory;
    glm::mat4           rootTransformation;
    glm::mat4           globalInvertTransformation;

  private:
    void   processNode(aiNode* node, const aiScene* scene);
    Mesh3D processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<std::string> loadMaterialTextures(aiMaterial* mat, int type, std::string typeName);

  };
}