#pragma once

#include <vector>
#include "MarchingConvexPolygon.h"
#include "BaseTypes/PolygonNet.h"
#include "BaseTypes/Polygon.h"
#include <set>
#include <map>

namespace Iyathuum
{
  /*
    Marching Cubes in a bit more general fashion
    Assumes input polygon is convex, will spit out garbage if not
  */
  template <size_t Dimension>
  class MarchingConvexPolygonNet
  {
    using vec = glm::vec<Dimension, float, glm::defaultp>;
  public:
    static std::vector<Polygon<3>> marchingCubes(float mmm, float mmp, float mpm, float mpp, float pmm, float pmp, float ppm, float ppp, float isovalue)
    {      
      return calculate(PolygonNet<3>::cube(), { mmm,mmp,mpm,mpp,pmm,pmp,ppm,ppp }, isovalue);
    }

    static std::vector<Polygon<Dimension>> calculate(PolygonNet<Dimension> net, std::vector<float> weights, float isovalue)
    {
      using vertex = std::pair<size_t, size_t>;
      struct graphNode
      {
        vec    pos;
        vertex next;
      };
      std::map<vertex, graphNode> graph; //too lazy, please sacrifice me to uncle bob
      std::vector<PolygonNetPolygon<Dimension>*> todo;

      //buildup graph
      for(auto current : net.faces)
      {
        std::vector<vec>   currentPoints;
        std::vector<float> currentWeights;
        for (const auto& p : current.points) {
          currentPoints.push_back(net.points[p]);
          currentWeights.push_back(weights[p]);
        }
        auto lines = MarchingConvexPolygon<Dimension>::calculate(currentPoints, currentWeights, isovalue);

        for (size_t i = 0; i < lines.lines.size(); i++){
          auto startIndex = lines.indices[i].start;
          auto endIndex   = lines.indices[i].end;

          if (graph.count(startIndex) == 0)
          {
            graphNode newNode;
            newNode.pos = lines.lines[i].start;
            newNode.next = endIndex;
            graph[startIndex] = newNode;
          }
          else
            graph[startIndex].next = endIndex;

          if (graph.count(endIndex) == 0)
          {
            graphNode newNode;
            newNode.pos = lines.lines[i].end;
            graph[endIndex] = newNode;
          }
        }
      }
      
      //trace graph
      std::vector<Polygon<Dimension>> result;
      std::set<vertex> visited;
      for (auto v : graph)
      {
        if (visited.count(v.first) != 0)
          continue;
        Polygon<Dimension> poly;
        //trace loop

        vertex current = v.first;
        while (visited.count(current) == 0)
        {
          visited.insert(current);
          auto& r = graph[current];
          poly.points.push_back(r.pos);
          current = r.next;
        }
        result.push_back(poly);
      }
      return result;
    }
  };
}