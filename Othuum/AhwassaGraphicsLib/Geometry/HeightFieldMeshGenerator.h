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
        size_t count = 0;

        bool sm0 = position[0] > 0;
        bool sp0 = position[0] < vertecies.getDimension(0) - 1;
        bool s0m = position[1] > 0;
        bool s0p = position[1] < vertecies.getDimension(1) - 1;
        bool smm = sm0 && s0m;
        bool smp = sm0 && s0p;
        bool spm = sp0 && s0m;
        bool spp = sp0 && s0p;
        glm::vec3 up(0, 1, 0);

        vertex.normal = glm::vec3(0);
        glm::vec3 vm0 = (sm0 ? vertecies.getVal({ position[0] - 1,position[1]     }).position-p : glm::vec3(-1,0, 0));
        glm::vec3 vp0 = (s0m ? vertecies.getVal({ position[0]    ,position[1] - 1 }).position-p : glm::vec3( 0,0,-1));
        glm::vec3 v0m = (smm ? vertecies.getVal({ position[0] - 1,position[1] - 1 }).position-p : glm::vec3(-1,0,-1));
        glm::vec3 v0p = (sp0 ? vertecies.getVal({ position[0] + 1,position[1]     }).position-p : glm::vec3(+1,0, 0));
        glm::vec3 vmm = (s0p ? vertecies.getVal({ position[0]    ,position[1] + 1 }).position-p : glm::vec3( 0,0,+1));
        glm::vec3 vmp = (spp ? vertecies.getVal({ position[0] + 1,position[1] + 1 }).position-p : glm::vec3(+1,0,+1));
        glm::vec3 vpm = (spm ? vertecies.getVal({ position[0] + 1,position[1] - 1 }).position-p : glm::vec3(+1,0,-1));
        glm::vec3 vpp = (smp ? vertecies.getVal({ position[0] - 1,position[1] + 1 }).position-p : glm::vec3(-1,0,+1));

        vertex.normal += glm::cross(glm::cross(vm0, up), vm0);
        vertex.normal += glm::cross(glm::cross(vp0, up), vp0);
        vertex.normal += glm::cross(glm::cross(v0m, up), v0m);
        vertex.normal += glm::cross(glm::cross(v0p, up), v0p);
        vertex.normal += glm::cross(glm::cross(vmm, up), vmm);
        vertex.normal += glm::cross(glm::cross(vmp, up), vmp);
        vertex.normal += glm::cross(glm::cross(vpm, up), vpm);
        vertex.normal += glm::cross(glm::cross(vpp, up), vpp);

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