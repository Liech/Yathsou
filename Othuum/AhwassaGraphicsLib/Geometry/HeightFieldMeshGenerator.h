#pragma once

#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"
#include "AhwassaGraphicsLib/BufferObjects/Mesh.h"
#include "AhwassaGraphicsLib/Vertex/PositionNormalVertex.h"

namespace Ahwassa {
  class HeightFieldMeshGenerator {
  public:

    template<typename Number>
    static std::shared_ptr<Mesh<PositionNormalVertex>> generate(Iyathuum::MultiDimensionalArray<Number, 2>& map, Number Min, Number Max, float height = 1, float cellSize = 1) {
      size_t w = map.getDimension(0);
      size_t h = map.getDimension(1);
      
      Iyathuum::MultiDimensionalArray<PositionNormalVertex, 2> vertecies(std::vector<size_t>{w,h});
      std::vector<int> indices;
      indices.reserve(vertecies.getSize() * 6);
      vertecies.apply([&map, cellSize, Min, Max,height](const std::array<size_t, 2>& position, PositionNormalVertex& vertex) {
        vertex.position = glm::vec3(position[0] * cellSize, height * ((float)map.getVal(position) - (float)Min) / (float)Max, position[1] * cellSize);
      });
      vertecies.apply([&vertecies, cellSize, Min, Max](const std::array<size_t, 2>& position, PositionNormalVertex& vertex) {
        glm::vec3 p = vertecies.getVal(position).position;
        vertex.normal = glm::vec3(0);
        size_t count = 0;
        if (position[0] > 0) {
          vertex.normal += vertecies.getVal({ position[0] - 1,position[1] }).position-p;
          count++;
          if (position[1] > 0) {
            vertex.normal += vertecies.getVal({ position[0] - 1,position[1] - 1 }).position - p;
            count++;
          }
          if (position[1] < vertecies.getDimension(1) - 1) {
            vertex.normal += vertecies.getVal({ position[0] - 1,position[1] + 1 }).position - p;
            count++;
          }
        }
        if (position[1] > 0) {
          vertex.normal += vertecies.getVal({ position[0],position[1]-1 }).position - p;
          count++;
          if (position[0] < vertecies.getDimension(0) - 1) {
            vertex.normal += vertecies.getVal({ position[0] + 1,position[1] - 1 }).position - p;
            count++;
          }
        }
        if (position[0] < vertecies.getDimension(0) - 1) {
          vertex.normal += vertecies.getVal({ position[0] + 1,position[1] }).position - p;
          count++;
        }
        if (position[1] < vertecies.getDimension(1) - 1) {
          vertex.normal += vertecies.getVal({ position[0],position[1] + 1}).position - p;
          count++;
        }
        if (position[1] < vertecies.getDimension(1) - 1 && position[0] < vertecies.getDimension(0) - 1) {
          vertex.normal += vertecies.getVal({ position[0]+1,position[1] + 1 }).position - p;
          count++;
        }

        vertex.normal /= count;
        vertex.normal = glm::normalize(vertex.normal);
      });
      for (int x = 0; x < w - 1; x++) {
        for (int y = 0; y < h - 1; y++) {
          indices.push_back(vertecies.transform( x    , y     ));
          indices.push_back(vertecies.transform( x + 1, y + 1 ));
          indices.push_back(vertecies.transform( x + 1, y ));

          indices.push_back(vertecies.transform(x,y         ));
          indices.push_back(vertecies.transform(x, y + 1));
          indices.push_back(vertecies.transform(x + 1,y + 1 ));
        }
      }
      std::shared_ptr<Mesh<PositionNormalVertex>> result = std::make_shared <Mesh<PositionNormalVertex>>(vertecies.vector(), indices);
      return result;
    }
  private:

  };
}