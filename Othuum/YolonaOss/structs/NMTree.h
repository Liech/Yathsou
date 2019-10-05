#pragma once

#include "MultiDimensionalArray.h"
#include <set>

//NM Tree means N^M Tree
//I don't know whats the real name is
//2^3 Tree is formaly known as Octree
//this link proposes HyperOctree and Orthtree, which would only describe 2^N trees.
//https://math.stackexchange.com/questions/644032/name-of-the-generalization-of-quadtree-and-octree

//It is not neccessary for my purpose that it has n dimensions, therefor it is not really tested
//Im just interested in the mindfuck of building it ultra generic
//and it should be fully compatible to the MultiDimensionalarray, which was also born out of the desire to mindfuck
//So this code will be not easy to read, not even for me. Forgive me

//maybe 3 and 4 dimensions are neccessary. For voxel animations?
namespace YolonaOss {

  enum class TreeMergeBehavior {
    Sum, Max, Min, Avg, Default
  };
  enum class NMTreeDirection {
    Positive, Negative
  };

  template <typename Content, size_t ArraySize, size_t Dimension, TreeMergeBehavior Merge, Content defaultValue>
  class NMTree {
  public:
    NMTree() {}

    NMTree(Content value, std::array<size_t, Dimension> position) {
      _position = position;
      _content = value;
    }

    NMTree(MultiDimensionalArray<Content, Dimension>* description) {
      //find suitable size for enclosing tree    
      size_t maxDim = 0;
      for (size_t dim = 0; dim < Dimension; dim++) {
        assert(description->getDimension(dim) > 0);
        if (description->getDimension(dim) > maxDim)
          maxDim = description->getDimension(dim);
      }
      _size = 1;
      while (_size <= maxDim)
        _size *= ArraySize;

      if (_size == 1) {
        _content = description->get_linearVal(0);
        return;
      }
      for (size_t dim = 0; dim < Dimension; dim++)
        _position[dim] = 0;
      recursiveFill(description);
    }

    virtual ~NMTree() {
      if (_childs)
        delete _childs;
      //for (int i = 0; i < Dimension; i++) {
      //  for (auto n : _neighbourhood[i * 2])
      //    if (n->_neighbourhood[i * 2 + 1].find(this) != n->_neighbourhood[i * 2 + 1].end())
      //      n->_neighbourhood[i * 2 + 1].erase(this);
      //  for (auto n : _neighbourhood[i * 2+1])
      //    if (n->_neighbourhood[i * 2].find(this) != n->_neighbourhood[i * 2].end())
      //      n->_neighbourhood[i * 2].erase(this);
      //}
    }

    void createChildren() {
      assert(_childs == nullptr);
      std::vector<size_t> size;
      size.resize(Dimension);
      std::fill(size.begin(), size.end(), ArraySize);
      _childs = new MultiDimensionalArray<NMTree<Content, ArraySize, Dimension, Merge, defaultValue>, Dimension>(size);
           
      _childs->apply([this](std::array<size_t, Dimension> pos, NMTree<Content, ArraySize, Dimension, Merge, defaultValue>& child) {
        child._size = _size / ArraySize;
        child._content = _content;
        std::array<size_t, Dimension> newPosition;
        for (int i = 0; i < Dimension; i++)
          newPosition[i] = _position[i] + pos[i] * child._size;
        child._position = newPosition;
        });
    }
    void initNeighbourgraph() {
      if (_childs != nullptr)
        for(size_t i = 0;i < _childs->getSize();i++)
          _childs->get_linearRef(i).initNeighbourgraph(this);
    }
    void initNeighbourgraph(NMTree<Content, ArraySize, Dimension, Merge, defaultValue>* parent) {
      // Neighboorhood ---------------------------------
      //for (int dim = 0; dim < Dimension; dim++) {
      //  if (getPosition()[dim] != 0) { //inside
      //    std::array<size_t, Dimension> neighbourPos = getPosition();
      //    neighbourPos[dim] -= 1;
      //    _neighbourhood[dim * 2].insert(&(_childs->getRef(neighbourPos)));
      //  }

      //}
      //  else //border
      //  {
      //    for (auto n : this->_neighbourhood[dim * 2]) {
      //      //check for intersections
      //      bool validNeighbour = true;
      //      for (int i = 0; i < Dimension; i++) {
      //        if (i == dim) continue;
      //        if (n->_position[i] > (child._position[i] + child._size)) 
      //          { validNeighbour = false; break; }
      //        if ((n->_position[i] + n->_size) < child._position[i]) 
      //          { validNeighbour = false; break; }
      //      }
      //      if (!validNeighbour) continue;

      //      child._neighbourhood[dim * 2].insert(n);
      //      if (n->_neighbourhood[dim * 2+1].count(this))
      //        n->_neighbourhood[dim * 2+1].erase(this);
      //      n->_neighbourhood[dim * 2+1].insert(&child);
      //    }
      //  }

      //  ////Neighboorhood ++++++++++++++++++++++++++++++++
      //  if (pos[dim] < ArraySize - 1) {
      //    std::array<size_t, Dimension> neighbourPos = pos;
      //    neighbourPos[dim] += 1;
      //    child._neighbourhood[dim * 2 + 1].insert(&(_childs->getRef(neighbourPos)));
      //  }
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

    std::set< NMTree<Content, ArraySize, Dimension, Merge, defaultValue>* > getNeighbours(size_t dimension, NMTreeDirection dir) {
      return _neighbourhood[dimension * 2 + (dir == NMTreeDirection::Positive) ? 1 : 0];
    }

    void killChildren() {
      delete _childs;
      _childs = nullptr;
    }

    struct Leaf {
      std::array<size_t, Dimension> position;
      size_t                        size;
      Content                       value;
      NMTree<Content, ArraySize, Dimension, Merge, defaultValue>* link;

    };
    std::vector<Leaf> getLeafs() {
      if (_childs == nullptr) {
        Leaf f;
        f.position = _position;
        f.size     = _size;
        f.value    = _content;
        f.link     = this;
        return { f };
      }
      else {
        std::vector<Leaf> result;
        for (size_t i = 0; i < _childs->getSize(); i++) {
          auto subResult = _childs->get_linearRef(i).getLeafs();
          result.insert(result.end(), subResult.begin(), subResult.end());
        }
        return result;
      }
    }

    std::vector<Content> toFlat(Content isNodeValue) {
      if (_childs) {
        std::vector<Content> result;
        result.push_back(isNodeValue);
        for (int64_t i = 0; i < _childs->getSize(); i++) {
          auto sub = _childs->get_linearVal(i).toFlat(isNodeValue);
          result.insert(result.end(), sub.begin(), sub.end());
        }
        return result;
      }
      else {
        return { _content };
      }
    }

    Content getContent() { return _content; }
    size_t getSize() { return _size; }
    std::array<size_t, Dimension> getPosition() { return _position; }
  private:
    void recursiveFill(MultiDimensionalArray<Content, Dimension>* description) {
      assert(_size > 0);
      if (_size == 1) {
        for (size_t dim = 0; dim < Dimension; dim++)
          if (_position[dim] >= description->getDimension(dim)) {
            _content = defaultValue;
            return;
          }
        _content = description->getVal(_position);
      }
      else {
        createChildren();
        for (int i = 0; i < _childs->getSize(); i++)
          assert(_childs->get_linearRef(i)._size == _size / ArraySize);
#pragma omp parallel for  
        for (int i = 0; i < _childs->getSize(); i++) {
          _childs->get_linearRef(i).recursiveFill(description);
        }

        bool allSame = true;
        Content compare = _childs->get_linearRef(0)._content;
        Content merged = compare;

        for (uint64_t i = 1; i < _childs->getSize(); i++) {
          Content current = _childs->get_linearRef(i)._content;
          if (compare != current)
            allSame = false;

          if      constexpr (Merge == TreeMergeBehavior::Max) merged = std::max(merged, current);
          else if constexpr (Merge == TreeMergeBehavior::Min) merged = std::min(merged, current);
          else if constexpr (Merge == TreeMergeBehavior::Avg) merged += current;
          else if constexpr (Merge == TreeMergeBehavior::Sum) merged += current;
        }
        if constexpr (Merge == TreeMergeBehavior::Avg)
          merged /= _childs->getSize();

        bool allLeafs = true;
        for (size_t i = 0; i < _childs->getSize(); i++)
          if (_childs->get_linearRef(i)._childs) {
            allLeafs = false;
            break;
          }

        if (allSame && allLeafs) {
          _content = compare;
          killChildren();
        }
        else
          _content = merged;
      }
    }

    //dim0-,dim0+,dim1-,dim1+,dim2-,dim3+,....
    //x-,x+,y-,y+,z-,z+
    std::array< std::set<NMTree<Content, ArraySize, Dimension, Merge, defaultValue>* > , 2 * Dimension>    _neighbourhood; //at least for 4 dimensions correct. 
    std::array<size_t, Dimension>                                                                          _position;
    size_t                                                                                                 _size = 1;
    Content                                                                                                _content;
    MultiDimensionalArray<NMTree<Content, ArraySize, Dimension, Merge, defaultValue>, Dimension>*          _childs = nullptr;
  };
}