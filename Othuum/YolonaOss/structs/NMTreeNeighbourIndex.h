#pragma once

#include <array>
#include <map>
#include "NMTree.h"



namespace YolonaOss {
  enum class NMTreeDirection {
    Positive, Negative
  };

  template <typename Content, size_t ArraySize, size_t Dimension, TreeMergeBehavior Merge, Content defaultValue>
  class NMTreeNeighbourIndex {
    using Tree = NMTree<Content, ArraySize, Dimension, Merge, defaultValue>;
  public:
    NMTreeNeighbourIndex(Tree* root) {
      _root = root;
    }
    
    void init() {
      auto leafs = _root->getLeafs();     
      int batchSize = 1000;
      int64_t numberOfBatches = (leafs.size() / batchSize) + 1;
      std::vector<std::vector<Neighbourhood>> result;
      result.resize(numberOfBatches);
      //#pragma omp parallel for  
      for (int64_t batch = 0; batch < batchSize; batch++) {
        for (size_t i = batchSize * batch; i < batchSize * (batch+1) && i<leafs.size(); i++) {
          Neighbourhood n;
          n._target = leafs[i].link;
          for (size_t dim = 0; dim < Dimension; dim++){
            for (auto dir : { NMTreeDirection::Negative,NMTreeDirection::Positive }) {
              n.get(dim, dir) = getCardinalNeighbour(n._target, dim, dir);
            }
          }
          result[batch].push_back(n);
        }
      }

      for (size_t batch = 0; batch < result.size(); batch++) {
        for (size_t i = 0; i < result[batch].size(); i++)
          _neighbourhood[result[batch][i]._target] = result[batch][i];
      }
    }

    std::vector<Tree*> getNeighbours(Tree* node, size_t dimension, NMTreeDirection dir) {
      std::vector<Tree*> result;

      result.push_back(_neighbourhood[node].get(dimension, dir));
      size_t maxPos = node->getPosition()[dimension] + node->getSize();
      if (result[0] == nullptr) return {};
      //Tree* current = result[0];
      //while (current->getPosition()[dimension] < maxPos) {
      //  Tree* next = _neighbourhood[current].get(dimension,)
      //}
      //all neighbours coming soon TM
      return result;
    }

  private:

    Tree* getCardinalNeighbour(Tree* node, size_t dimension, NMTreeDirection dir) {
      Tree* root = nullptr;
      std::vector<std::array<size_t, Dimension>> pathToNeighbour = getPathToNeighbour(node, dimension, dir, root);
      if (pathToNeighbour.size() == 0) return nullptr;
      Tree* current = root;
      for (int i = pathToNeighbour.size()-1; i >= 0; i--) {
        if (current->isLeaf()) {
          return current;
        }
        else {
          Tree* next = current->getChild(pathToNeighbour[i]);
          current = next;
        }
      }
      while (!current->isLeaf()) {
        //traverse even deeper. Idea of cn is to take the most - node possible as representative.
        //all other nodes are reachable by going + in neighbourhood
        std::array<size_t, Dimension> childPos;
        for (size_t i = 0; i < Dimension; i++)
          childPos[i] = 0;
        childPos[dimension] = (dir == NMTreeDirection::Negative) ? ArraySize - 1 : 0;
        Tree* next = current->getChild(childPos);
        current = next;
      }
      return current;
    }

    std::vector<std::array<size_t, Dimension>> getPathToNeighbour(Tree* node, size_t dimension, YolonaOss::NMTreeDirection dir, Tree*& root) {
      //modifys the path so that it should point to its neighbour at the same height
      std::vector<std::array<size_t, Dimension>> input;
      getOwnPath(node,input, root);
      std::vector<std::array<size_t, Dimension>> result;
      size_t currentPosition = 0;
      for (; currentPosition < input.size(); currentPosition++) {
        if (input[currentPosition][dimension] == 0 && dir == NMTreeDirection::Negative) {
          std::array<size_t, Dimension> newPath = input[currentPosition];
          newPath[dimension] += ArraySize - 1;
          result.push_back(newPath);
        }
        else if (input[currentPosition][dimension] == ArraySize - 1 && dir == NMTreeDirection::Positive) {
          std::array<size_t, Dimension> newPath = input[currentPosition];
          newPath[dimension] = 0;
          result.push_back(newPath);
        }
        else {
          std::array<size_t, Dimension> newPath = input[currentPosition];
          newPath[dimension] += (dir==NMTreeDirection::Positive) ? 1 : -1;
          result.push_back(newPath);
          for (size_t p = currentPosition + 1; p < input.size(); p++)
            result.push_back(input[p]);
          return result;
        }
      }
      return {};//no path found
    }

    //returns the path to this element
    void getOwnPath(Tree* node, std::vector<std::array<size_t, Dimension>>& path, Tree*& root) {
      if (!node->getParent()) {
        root = node;
        return;
      }
      std::array<size_t, Dimension> myPos = node->getPosition();
      for (size_t i = 0; i < Dimension; i++) myPos[i] = (myPos[i] - node->getParent()->getPosition()[i]) / node->getSize();
      path.push_back(myPos);
      getOwnPath(node->getParent(),path,root);
    }


    struct Neighbourhood {
      //dim0-,dim0+,dim1-,dim1+,dim2-,dim3+,....
      //x-,x+,y-,y+,z-,z+
      Tree*& get(size_t dimension, NMTreeDirection dir) { return _neighbourhood[2 * dimension + (dir == NMTreeDirection::Negative) ? 0 : 1]; }
      std::array<Tree*, 2 * Dimension> _neighbourhood; //at least for 4 dimensions correct. 
      Tree*                            _target;
    };

    std::map< Tree*, Neighbourhood> _neighbourhood;
    Tree*                           _root;
  };
}


/*
    void initNeighbourgraph() {
      if (_childs != nullptr)
        for(size_t i = 0;i < _childs->getSize();i++)
          _childs->get_linearRef(i).initNeighbourgraph(this);
    }


  void initNeighbourgraph(NMTree<Content, ArraySize, Dimension, Merge, defaultValue>* parent) {
    // Neighboorhood ---------------------------------
    std::array<size_t, Dimension> myPos = getPosition();
    for (size_t i = 0; i < Dimension; i++) myPos[i] = (myPos[i] - parent->getPosition()[i]) / getSize();
    if (parent != nullptr) {
      for (int dim = 0; dim < Dimension; dim++) {
        if (myPos[dim] != 0) { //inside
          std::array<size_t, Dimension> neighbourPos = myPos;
          neighbourPos[dim] -= 1;
          addNeighbour(dim, YolonaOss::NMTreeDirection::Negative, &parent->_childs->getRef(neighbourPos));
        }
        if (getPosition()[dim] < ArraySize - 1) {
          std::array<size_t, Dimension> neighbourPos = myPos;
          neighbourPos[dim] += 1;
          addNeighbour(dim, YolonaOss::NMTreeDirection::Positive, &parent->_childs->getRef(neighbourPos));
        }

        //border
        //if (myPos[dim] >= ArraySize - 1)
        //{
        //  for (auto n : parent->getNeighbours(dim, NMTreeDirection::Positive)) {
        //    //check for intersections
        //    bool validNeighbour = true;
        //    for (int i = 0; i < Dimension; i++) {
        //      if (i == dim) continue;
        //      if (n->getPosition()[i] > (getPosition()[i] + getSize()))
        //      {
        //        validNeighbour = false; break;
        //      }
        //      if ((n->getPosition()[i] + n->getSize()) < getPosition()[i])
        //      {
        //        validNeighbour = false; break;
        //      }
        //    }
        //    if (!validNeighbour) continue;

        //    addNeighbour(dim, NMTreeDirection::Positive, n);
        //  }

        //}

        //  ////Neighboorhood ++++++++++++++++++++++++++++++++
        //  //else {
        //  //  for (auto n : this->_neighbourhood[i * 2 + 1]) {
        //  //    child._neighbourhood [i * 2+1].insert(n);
        //  //    if (n->_neighbourhood[i * 2+1].count(this))
        //  //      n->_neighbourhood  [i * 2+1].erase(this);
        //  //    n->_neighbourhood    [i * 2+1].insert(&child);
        //  //  }
        //  //}
        //}
      }
    }
    if (_childs != nullptr)
      for (int i = 0; i < _childs->getSize(); i++)
        _childs->get_linearRef(i).initNeighbourgraph(this);
  }


*/