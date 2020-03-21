#pragma once

#include "Dijkstra.h"
#include "NMTree.h"
#include "NMTreeNeighbourIndex.h"

namespace YolonaOss {

  template<size_t Dimension>
  class NMTreeDijkstra : public DijkstraI<Dimension> {
    using Tree = NMTree<bool, 2, Dimension, YolonaOss::TreeMergeBehavior::Max, false>;
    using TreeI = NMTreeNeighbourIndex<bool, 2, Dimension, YolonaOss::TreeMergeBehavior::Max, false>;
    using vec = typedef glm::vec<Dimension, float, glm::defaultp>;
    using self = typedef NMTreeDijkstra<Dimension>;
  public:
    NMTreeDijkstra(vec start, Tree* root, std::function<double(Tree*)> weight)
    {
      _root = root;
      _getWeight = weight;
      _start = start;
      _treeIndex = std::make_unique<TreeI>(root);
      _treeIndex->init();
      _dijkstra = std::make_unique<Dijkstra<Tree>>(root->getLeaf(Util<Dimension>::vec2Array(start)), [this](Tree* A, Tree* B) { return getDijkstraDistance(A, B); }, [this](Tree* node) { return getDijkstraNeighbours(node); });
    }

    virtual vec getDirectionSuggestion(vec currentPosition) override {
      Tree* current = _root->getLeaf(Util<Dimension>::vec2Array(currentPosition));
      auto next = _dijkstra->getNext(current);
      if (next == nullptr)
        return vec();
      vec nextCenter = Util<Dimension>::array2Vec(next->getPosition());
      for(int i = 0;i < Dimension;i++) nextCenter+=next->getSize() / 2.0;
      return glm::normalize(nextCenter- currentPosition);
    }

    virtual double getDistance(vec postion) override {
      return glm::distance(_start, postion);
    }

  private:
    double getDijkstraDistance(Tree* A, Tree* B) {
      return glm::distance(Util<2>::array2Vec(A->getPosition()),Util<Dimension>::array2Vec(B->getPosition())) * std::max(_getWeight(A), _getWeight(B));
    }

    std::set<Tree*> getDijkstraNeighbours(Tree* node) {
      return _treeIndex->getAllNeighbours(node);
    }
  private:
    std::function<double(Tree*)> _getWeight;
    vec _start;
    std::unique_ptr< Dijkstra<NMTree<bool,2, Dimension, YolonaOss::TreeMergeBehavior::Max, false>>> _dijkstra;
    std::unique_ptr<TreeI> _treeIndex;
    Tree* _root;
  };
}