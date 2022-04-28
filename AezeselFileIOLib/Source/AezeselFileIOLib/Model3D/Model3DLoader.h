#pragma once

#include <string>
#include <vector>
#include <memory>

struct aiScene;
struct aiNode;
struct aiMesh;
struct aiMaterial;

namespace Iyathuum {
  class Model3D;
}

namespace Aezesel {

  class Model3DLoader {
    public:
      std::unique_ptr<Iyathuum::Model3D> load(const std::string&);
    private:
      std::vector<std::string> loadMaterialTextures(const aiMaterial* mat, int type, const std::string& typeName);
      void processNode(const aiNode* node, const aiScene* scene, Iyathuum::Model3D&);
      void processMesh(const aiMesh* mesh, const aiScene* scene, Iyathuum::Model3D&);

  };
}