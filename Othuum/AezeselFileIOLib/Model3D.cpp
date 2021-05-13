#include "Model3D.h"

#include <assimp/Importer.hpp>      
#include <assimp/scene.h>           
#include <assimp/postprocess.h>     

//https://assimp-docs.readthedocs.io/en/latest/usage/use_the_lib.html

namespace Aezesel {
  Model3D::Model3D() {
    const std::string pFile = "C:\\Users\\Niki\\Downloads\\Two+way+screw\\files\\nut_1.stl";
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(pFile,
      aiProcess_CalcTangentSpace |
      aiProcess_Triangulate |
      aiProcess_JoinIdenticalVertices |
      aiProcess_SortByPType);
  }
}