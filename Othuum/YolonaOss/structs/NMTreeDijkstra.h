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
    NMTreeDijkstra(vec start, Tree* root,std::shared_ptr<TreeI> index, std::function<double(Tree*)> weight)
    {
      _root = root;
      _getWeight = weight;
      _start = start;
      _treeIndex = index;
      _treeIndex->init();
      _dijkstra = std::make_unique<Dijkstra<Tree>>(root->getLeaf(Util<Dimension>::vec2Array<size_t>(start)), [this](Tree* A, Tree* B) { return getDijkstraDistance(A, B); }, [this](Tree* node) { return getDijkstraNeighbours(node); });
    }

    virtual vec getDirectionSuggestion(vec currentPosition) override {
      for (size_t i = 0; i < Dimension; i++) {
        if (currentPosition[i] < 0) 
          return vec(0.0);
        if (currentPosition[i] >= _root->getSize())
          return vec(0.0);
      }

      Tree* current = _root->getLeaf(Util<Dimension>::vec2Array<size_t>(currentPosition));
      auto next = _dijkstra->getNext(current);
      if (next == nullptr)
        return glm::normalize(vec(_start - currentPosition));
      vec nextCenter = Util<Dimension>::array2Vec(next->getPosition());
      for(int i = 0;i < Dimension;i++) 
        nextCenter[i] += (float)next->getSize() / 2.0;
      vec suggestion = glm::normalize(nextCenter - currentPosition);
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
      return glm::distance(_start, postion);
    }

  private:
    double getDijkstraDistance(Tree* A, Tree* B) {
      vec a = Util<2>::array2Vec(A->getPosition());
      vec b = Util<Dimension>::array2Vec(B->getPosition());
      for (int i = 0; i < Dimension; i++)
        a[i] += (float)A->getSize() / 2.0;
      for (int i = 0; i < Dimension; i++)
        b[i] += (float)B->getSize() / 2.0;
      return glm::distance(a,b) * std::max(_getWeight(A), _getWeight(B));
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
    std::unique_ptr< Dijkstra<NMTree<bool,2, Dimension, YolonaOss::TreeMergeBehavior::Max, false>>> _dijkstra;
    std::shared_ptr<TreeI> _treeIndex;
    Tree* _root;
  };
}