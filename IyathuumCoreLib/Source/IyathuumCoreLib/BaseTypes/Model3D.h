#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

namespace Iyathuum {
  struct Vertex {
    glm::vec3 position ;
    glm::vec3 normal   ;
    glm::vec3 bitangent;
    glm::vec3 tangent  ;
    glm::vec2 texCoords;
  };

  struct Bone {
    std::string        name;
    glm::mat4          offset;
    std::vector<int  > index;
    std::vector<float> weight;
  };

  class Mesh3D {
  public:
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<std::string>  textures;
    std::vector<Bone>         bone;
  };

  class Model3D {
  public:
    Model3D();

    std::vector<Mesh3D> meshes   ;
    std::string         directory;
    glm::mat4           rootTransformation;
    glm::mat4           globalInvertTransformation;

  private:

  };
}