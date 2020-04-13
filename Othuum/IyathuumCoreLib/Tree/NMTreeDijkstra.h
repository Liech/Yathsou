#pragma once

#include "Dijkstra.h"
#include "NMTree.h"
#include "NMTreeNeighbourIndex.h"

namespace Iyathuum {

  template<size_t Dimension>
  class NMTreeDijkstra : public DijkstraI<Dimension> {
    using Tree  = NMTree<bool, 2, Dimension, Iyathuum::TreeMergeBehavior::Max>;
    using TreeI = NMTreeNeighbourIndex<bool, 2, Dimension, Iyathuum::TreeMergeBehavior::Max>;
    using vec   = std::array<double,Dimension>;
    using self  = NMTreeDijkstra<Dimension>;
  public:
    NMTreeDijkstra(vec start, Tree* root,std::shared_ptr<TreeI> index, std::function<double(Tree*)> weight)
    {
      _root = root;
      _getWeight = weight;
      _start = start;
      _treeIndex = index;
      _treeIndex->init();
      std::array<size_t, Dimension> d;
      for (size_t i = 0; i < Dimension; i++)
        d[i] = start[i];
      _dijkstra = std::make_unique<Dijkstra<Tree>>(root->getLeaf(d), [this](Tree* A, Tree* B) { return getDijkstraDistance(A, B); }, [this](Tree* node) { return getDijkstraNeighbours(node); });
    }

    virtual vec getDirectionSuggestion(vec currentPosition) override {
      for (size_t i = 0; i < Dimension; i++) {
        if (currentPosition[(int)i] < 0)
          return Geometry<Dimension>::value(0);
        if (currentPosition[(int)i] >= _root->getSize())
          return Geometry<Dimension>::value(0);
      }
      std::array<size_t, Dimension> s;
      for (size_t i = 0; i < Dimension; i++)
        s[i] = currentPosition[i];
      Tree* current = _root->getLeaf(s);
      auto next = _dijkstra->getNext(current);
      if (next == nullptr)
        return Geometry<Dimension>::normalize(Geometry<Dimension>::subtract(_start,currentPosition));
      vec nextCenter;
      for(size_t i = 0;i < Dimension;i++)
        nextCenter[i] = next->getPosition()[i];
      for(int i = 0;i < Dimension;i++) 
        nextCenter[i] += (float)next->getSize() / 2.0;
      vec suggestion = Geometry<Dimension>::normalize(Geometry<Dimension>::subtract(nextCenter,currentPosition));
      return suggestion;
    }

    std::vector<Tree*> getPath(vec currentPosition) {
      Tree* current = _root->getLeaf(Util<Dimension>::vec2Array(currentPosition));
      std::vector<Tree*> result;
      while (current) {
        result.push_back(current);
        current = _dijkstra->getNext(current);
      }
      return result;
    }

    virtual double getDistance(vec postion) override {
      return Geometry<Dimension>::length(Geometry<Dimension>::subtract(_start, postion));
    }

  private:
    double getDijkstraDistance(Tree* A, Tree* B) {
      vec a = Geometry<Dimension>::convert<double,size_t>(A->getPosition());
      vec b = Geometry<Dimension>::convert<double,size_t>(B->getPosition());
      for (int i = 0; i < Dimension; i++)
        a[i] += (float)A->getSize() / 2.0;
      for (int i = 0; i < Dimension; i++)
        b[i] += (float)B->getSize() / 2.0;
      return Geometry<Dimension>::length(Geometry<Dimension>::subtract(a,b)) * std::max(_getWeight(A), _getWeight(B));
    }

    std::set<Tree*> getDijkstraNeighbours(Tree* node) {
      auto all = _treeIndex->getAllNeighbours(node);
      std::set<Tree*> result;
      for (auto single : all)
        if (single->getContent())
          result.insert(single);
      return result;
    }
  private:
    std::function<double(Tree*)> _getWeight;
    vec _start;
    std::unique_ptr< Dijkstra<NMTree<bool,2, Dimension, Iyathuum::TreeMergeBehavior::Max>>> _dijkstra;
    std::shared_ptr<TreeI> _treeIndex;
    Tree* _root;
  };
}