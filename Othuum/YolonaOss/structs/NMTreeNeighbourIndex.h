#pragma once

#include <array>
#include <map>
#include "NMTree.h"

//This class indexes all leaves.
//the basic idea is from this paper
//https://pdfs.semanticscholar.org/cec7/b45bca54d2ce5424bf9e7c61e954153f1ce0.pdf
//Cardinal Neighbor Quadtree: a New Quadtree-based Structure for Constant - Time Neighbor Finding
//Safwan W. Qasem, Ameur A. Touir
//because of lazyness it works a little bit differernt
//for greater and equal sized neighbours one neighbour is saved
//for smaller and therefor more neighbours the neighbour with the same size is saved
//on request of all neighbours, when they are smaller, the non leaf node is expanded to the correct border


namespace YolonaOss {


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
      //get one neighbour
      #pragma omp parallel for  
      for (int64_t batch = 0; batch < batchSize; batch++) {
        for (size_t i = batchSize * batch; i < batchSize * (batch+1) && i<leafs.size(); i++) {
          Neighbourhood n;
          n._target = leafs[i].link;
          for (size_t dim = 0; dim < Dimension; dim++){
            for (auto dir : { NMTreeDirection::Negative,NMTreeDirection::Positive }) {
              n.get(dim, dir) = getNeighbour(n._target, dim, dir);
            }
          }
          result[batch].push_back(n);
        }
      }

      //merge everything
      for (size_t batch = 0; batch < result.size(); batch++) {
        for (size_t i = 0; i < result[batch].size(); i++)
          _neighbourhood[result[batch][i]._target] = result[batch][i];
      }
    }

    std::set<Tree*> getAllNeighbours(Tree* node) {
      std::set<Tree*> result;
      for(size_t dimension = 0;dimension < Dimension;dimension++)
        for(auto dir : {NMTreeDirection::Negative, NMTreeDirection::Positive}){
          std::set<Tree*> subresult = getNeighbours(node, dimension, dir);
          result.insert(subresult.begin(), subresult.end());
        }
      return result;
    }

    std::set<Tree*> getNeighbours(Tree* node, size_t dimension, NMTreeDirection dir) {
      std::set<Tree*> result;

      Tree* first = _neighbourhood[node].get(dimension, dir);
      if (first == nullptr) 
        return {};
      else if (first->isLeaf())
        return { first };
      else {
        std::vector<Tree*> result;
        result.push_back(first);
        size_t currentPosition = 0;
        //expand border slices
        while (currentPosition < result.size()) {
          if (!result[currentPosition]->isLeaf()) {
            Tree* current = result[currentPosition];
            result.erase(result.begin() + currentPosition);
            std::set<Tree*> side = current->getSide(dimension, (dir == NMTreeDirection::Negative)?NMTreeDirection::Positive:NMTreeDirection::Negative);
            result.insert(result.begin(),side.begin(), side.end());
            continue;
          }
          currentPosition++;
        }
        return std::set<Tree*>(result.begin(), result.end());
      }
    }

  private:

    Tree* getNeighbour(Tree* node, size_t dimension, NMTreeDirection dir) {
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
      //not leafs are expanded to real neighbours in the question function to save memory
      return current;
    }

    std::vector<std::array<size_t, Dimension>> getPathToNeighbour(Tree* node, size_t dimension, YolonaOss::NMTreeDirection dir, Tree*& root) {
      //modifys the path so that it should point to its neighbour at the same height
      std::vector<std::array<size_t, Dimension>> input;
      getOwnPath(node,input, root);
      std::vector<std::array<size_t, Dimension>> result;
      
      for (size_t currentPosition = 0; currentPosition < input.size(); currentPosition++) {
        if (input[currentPosition][dimension] == 0 && dir == NMTreeDirection::Negative) {
          std::array<size_t, Dimension> newPath = input[currentPosition];
          newPath[dimension] = ArraySize - 1;
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
      Tree*& get(size_t dimension, NMTreeDirection dir) { 
        size_t index = 2 * dimension + ((dir == NMTreeDirection::Negative) ? 0 : 1);
        return _neighbourhood[index]; 
      }
      std::array<Tree*, 2 * Dimension> _neighbourhood; //at least for 4 dimensions correct. 
      Tree*                            _target;

      Neighbourhood() {
        for (size_t i = 0; i < 2 * Dimension; i++)
          _neighbourhood[i] = nullptr;
      }
    };

    std::map< Tree*, Neighbourhood> _neighbourhood;
    Tree*                           _root;
  };
}