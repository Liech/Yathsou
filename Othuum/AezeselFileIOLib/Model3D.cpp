#include "Model3D.h"

#include <stdexcept>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//https://assimp-docs.readthedocs.io/en/latest/usage/use_the_lib.html
//https://learnopengl.com/Model-Loading/Model

namespace Aezesel {
  Model3D::Model3D(const std::string& file) {
    //const std::string pFile = "C:\\Users\\Niki\\Documents\\GitHub\\Yathsou\\Othuum\\x64\\Debug\\Data\\Clonk\\Graphics.mesh.xml";
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(file, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
      std::cout << import.GetErrorString() << std::endl;
      throw std::runtime_error( "ERROR::ASSIMP::" + std::string(import.GetErrorString()));
      return;
    }
    directory = file.substr(0, file.find_last_of('/'));

    processNode(scene->mRootNode, scene);
  }

  void Model3D::processNode(aiNode* node, const aiScene* scene) {
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
      aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
      meshes.push_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
      processNode(node->mChildren[i], scene);
    }
  }

  Mesh3D Model3D::processMesh(aiMesh* mesh, const aiScene* scene)
  {
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<std::string>  textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
      Vertex vertex;

      glm::vec3 vector;
      vector.x = mesh->mVertices[i].x;
      vector.y = mesh->mVertices[i].y;
      vector.z = mesh->mVertices[i].z;
      vertex.Position = vector;

      vector.x = mesh->mNormals[i].x;
      vector.y = mesh->mNormals[i].y;
      vector.z = mesh->mNormals[i].z;
      vertex.Normal = vector;

      if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
      {
        glm::vec2 vec;
        vec.x = mesh->mTextureCoords[0][i].x;
        vec.y = mesh->mTextureCoords[0][i].y;
        vertex.TexCoords = vec;
      }
      else
        vertex.TexCoords = glm::vec2(0.0f, 0.0f);

      vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
      aiFace face = mesh->mFaces[i];
      for (unsigned int j = 0; j < face.mNumIndices; j++)
        indices.push_back(face.mIndices[j]);
    }
    
    if (mesh->mMaterialIndex >= 0)
    {
      aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
      std::vector<std::string> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
      textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
      std::vector<std::string> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
      textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    Mesh3D result;
    result.vertices = vertices;
    result.indices  = indices;
    result.textures = textures;
    return result;
  }

  std::vector<std::string> Model3D::loadMaterialTextures(aiMaterial* mat, int type, std::string typeName)
  {
    std::vector<std::string> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount((aiTextureType)type); i++)
    {
      aiString str;
      mat->GetTexture((aiTextureType)type, i, &str);
      textures.push_back(str.C_Str());
    }
    return textures;
  }
}