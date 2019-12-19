#pragma once

#include <map>
#include <set>
#include <limits>
#include <vector>
#include <algorithm>
#include <functional>
#include "AABB.h"

namespace YolonaOss {
  //solve dijkstra on arbitrary graph
  //result is a gradient for each entry
  //std::set<NodeType*> getNeighbours(NodeType* T) should return all neighbours of T
  //double getDistance(NodeType* A, NodeType* B) should return the distance between a and b
  template<typename NodeType>
  class Dijkstra { //TODO: check spelling
  public:
    Dijkstra(NodeType* startNode, std::function<double(NodeType*, NodeType*)> getDistance, std::function<std::set<NodeType*>(NodeType*)> getNeighbours) {
      _startNode = startNode;

      struct Edge {
        Edge(NodeType* a, NodeType* b, double currentDistance, std::function<double(NodeType*, NodeType*)> getDistance, std::function<std::set<NodeType*>(NodeType*)> getNeighbours) {
          A = a;
          B = b;
          Distance = getDistance(a, b) + currentDistance;
        }
        NodeType* A;
        NodeType* B;
        double    Distance;
      };
      std::vector<Edge> todo;
      std::set<NodeType*> done;
      {
        std::set<NodeType*> startNeighbours = getNeighbours(_startNode);
        for (auto s : startNeighbours) {
          Edge e = Edge(_startNode, s, 0, getDistance, getNeighbours);
          if (!std::isinf(e.Distance))
            todo.push_back(e);
        }
      }

      _gradient[_startNode] = 0;
      done.insert(_startNode);

      while (todo.size() != 0) {
        std::sort(todo.begin(), todo.end(), [](const Edge& a, const Edge& b) {return a.Distance < b.Distance; });
        Edge current = todo[0];
        todo.erase(todo.begin());
        done.insert(current.B);
        assert(!std::isinf(current.Distance));
        _gradient[current.B] = current.Distance;
        for (auto s : getNeighbours(current.B)) {
          if (done.count(s) == 0) {
            Edge e = Edge(current.B, s, current.Distance, getDistance, getNeighbours);
            done.insert(s);
            if (std::isinf(e.Distance))
              continue;
            todo.push_back(e);
            _maxValue = std::max(_maxValue, current.Distance);
          }
        }
      }
    }

    double getGradient(NodeType* node) {
      if (_startNode == node)
        return 0;
      if (_gradient.count(node) == 0)
        return std::numeric_limits<double>::infinity();
      return _gradient[node];
    }
    double getMaxValue() {
      return _maxValue;
    }
  private:

    NodeType* _startNode;
    std::map<NodeType*, double> _gradient;
    double                      _maxValue;
  };

  template<size_t Dimension>
  class AABBDijkstra : public Dijkstra<AABBHierarchyNetwork<Dimension>>{
    using vec = typedef glm::vec<Dimension, float, glm::defaultp>;
    using self = typedef AABBDijkstra<Dimension>;
  public:
    AABBDijkstra(vec start, AABBHierarchyNetwork<Dimension>* root, std::function<double(AABBHierarchyNetwork<Dimension>*)> weight) : Dijkstra<AABBHierarchyNetwork<Dimension>>(network.getLeaf(root),self::getDistance,self::getNeighbours) {
      _getWeight = weight;
    }
  private:
    static double getDistance(AABBHierarchyNetwork<Dimension>* A, AABBHierarchyNetwork<Dimension>* B) {
      return glm::distance(A->getCenter() - B->getCenter()) * std::max(_getWeight(A), _getWeight(B));
    }

    static std::set<AABBHierarchyNetwork<Dimension>*> getNeighbours(AABBHierarchyNetwork<Dimension>* node) {
      return node->getNeighbours();
    }
  private:
    std::function<double(AABBHierarchyNetwork<Dimension>*)> _getWeight;
  };
}