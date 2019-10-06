#pragma once

#include <map>
#include <set>
#include <limits>
#include <vector>
#include <algorithm>

//solve dijkstra on arbitrary graph
//result is a gradient for each entry
//std::set<NodeType*> getNeighbours(NodeType* T) should return all neighbours of T
//double getDistance(NodeType* A, NodeType* B) should return the distance between a and b
template<typename NodeType, typename getNeighbours, typename getDistance>
class Dijkstra { //TODO: check spelling
public:
  Dijkstra(NodeType* startNode) {
    _startNode = startNode;

    struct Edge {
      Edge(NodeType* a, NodeType* b, double currentDistance) {
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
        todo.push_back(Edge(_startNode, s,0));
      }
    }
    
    _gradient[_startNode] = 0;
    done.insert(_startNode);

    while (todo.size() != 0) {
      std::sort(todo.begin(), todo.end(), [](const Edge& a, const Edge& b) {return a.Distance < b.Distance; });
      Edge current = todo[0];
      todo.erase(todo.begin());
      done.insert(current.B);
      _gradient[current.B] = current.Distance;
      for (auto s : getNeighbours(current.B)) {
        if (done.count(s) == 0)
          todo.push_back(Edge(current.B, s, current.Distance));
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

private:

  NodeType*                   _startNode;
  std::map<NodeType*, double> _gradient;
  double                      _maxValue;
};