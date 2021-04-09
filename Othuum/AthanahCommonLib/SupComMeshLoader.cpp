#include "SupComMeshLoader.h"

namespace Athanah {
  std::shared_ptr<Ahwassa::Mesh<Ahwassa::PositionNormalVertex>> SupComMeshLoader::loadBasic(std::string filename) {
    Aezesel::SCM model;
    auto data = model.load(filename);
    std::vector<int> indices;
    for (auto i : data.indices) {
      indices.push_back(i.a);
      indices.push_back(i.b);
      indices.push_back(i.c);
    }
    std::vector<Ahwassa::PositionNormalVertex> vertices;
    for (auto v : data.vertecies) {
      Ahwassa::PositionNormalVertex p;
      p.position = v.position;
      p.normal = v.normal;
      vertices.push_back(p);
    }
    return std::make_shared<Ahwassa::Mesh<Ahwassa::PositionNormalVertex>>(vertices, indices);
  }
}