#include "Model3DLoader.h"

#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <IyathuumCoreLib/BaseTypes/Model3D.h>

#include "AssimpUtil.h"

namespace Aezesel {
  std::unique_ptr<Iyathuum::Model3D> Model3DLoader::load(const std::string& filename) {
    std::unique_ptr<Iyathuum::Model3D> result = std::make_unique<Iyathuum::Model3D>();
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
      std::cout << import.GetErrorString() << std::endl;
      throw std::runtime_error("ERROR::ASSIMP::" + std::string(import.GetErrorString()));
    }
    std::string directory = filename.substr(0, filename.find_last_of('/'));
    result->rootTransformation = Private::AssimpUtil::convert(scene->mRootNode->mTransformation);

    processNode(scene->mRootNode, scene, *result);
    return std::move(result);
  }

  void Model3DLoader::processNode(const aiNode* node, const aiScene* scene, Iyathuum::Model3D& result) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
      aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
      processMesh(mesh, scene, result);
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
      processNode(node->mChildren[i], scene,result);
    }
  }

  void Model3DLoader::processMesh(const aiMesh* mesh, const aiScene* scene, Iyathuum::Model3D& result) {
    std::vector<Iyathuum::Vertex> vertices;
    std::vector<unsigned int>     indices;
    std::vector<std::string>      textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
      Iyathuum::Vertex vertex;

      glm::vec3 vector;
      vector.x = mesh->mVertices[i].x;
      vector.y = mesh->mVertices[i].y;
      vector.z = mesh->mVertices[i].z;
      vertex.position = vector;

      if (mesh->HasNormals()) {
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;
      }
      else
        vertex.normal = glm::vec3(0, 0, 0);

      if (mesh->mTextureCoords) {
        const aiVector3D* textureVec = &mesh->mTextureCoords[0][i];
        glm::vec2 vec;
        vec.x = textureVec->x;
        vec.y = textureVec->y;
        vertex.texCoords = vec;
      }
      else
        vertex.texCoords = glm::vec2(0.0f, 0.0f);


      vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
      aiFace face = mesh->mFaces[i];
      for (unsigned int j = 0; j < face.mNumIndices; j++)
        indices.push_back(face.mIndices[j]);
    }

    if (mesh->mMaterialIndex >= 0) {
      aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
      std::vector<std::string> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
      textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
      std::vector<std::string> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
      textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    if (mesh->HasBones()) {
      for (size_t i = 0; i < mesh->mNumBones; i++) {
        auto& bone  = mesh->mBones[i];
        Iyathuum::Bone subResult;
        subResult.name = bone->mName.C_Str();        
        subResult.offset = Aezesel::Private::AssimpUtil::convert(bone->mOffsetMatrix);
        for (size_t w = 0; w < bone->mNumWeights; w++) {
          subResult.index .push_back(bone->mWeights[w].mVertexId);
          subResult.weight.push_back(bone->mWeights[w].mWeight  );
        }
      }
    }

    Iyathuum::Mesh3D subMesh;
    subMesh.vertices = vertices;
    subMesh.indices = indices;
    subMesh.textures = textures;
    result.meshes.push_back(subMesh);
  }

  std::vector<std::string> Model3DLoader::loadMaterialTextures(const aiMaterial* mat, int type, const std::string& typeName) {
    std::vector<std::string> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount((aiTextureType)type); i++) {
      aiString str;
      mat->GetTexture((aiTextureType)type, i, &str);
      textures.push_back(str.C_Str());
    }
    return textures;
  }
}