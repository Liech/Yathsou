#pragma once

#include "MultiDimensionalArray.h"
#include <set>
#include "../Util/ImageSubsetUtil.h"
//NM Tree means N^M Tree
//I don't know whats the real name is
//2^3 Tree is formaly known as Octree
//this link proposes HyperOctree and Orthtree, which would only describe 2^N trees.
//https://math.stackexchange.com/questions/644032/name-of-the-generalization-of-quadtree-and-octree

//It is not neccessary for my purpose that it has n dimensions (I only need 2 and 3), therefor it is not really tested
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

  template <typename Content, size_t ArraySize, size_t Dimension, TreeMergeBehavior Merge, /*Content defaultValue,*/ typename Scalar = size_t>
  class NMTree final {
    using Tree = NMTree<Content, ArraySize, Dimension, Merge/*, defaultValue*/, Scalar>;
  public:
    NMTree(Tree* parent = nullptr) {
      _parent = parent;
    }

    NMTree(Content value, std::array<Scalar, Dimension> position, Tree* parent = nullptr) {
      _parent = parent;
      _position = position;
      _content = value;
    }

    NMTree(Content value, std::array<Scalar, Dimension> position, Scalar size, Tree* parent = nullptr) {
      _parent = parent;
      _position = position;
      _content = value;
      _size = size;
    }

    
    NMTree(MultiDimensionalArray<Content, Dimension>* description, Content startValue, Tree* parent = nullptr) {
      static_assert(!std::is_same<double, Scalar>());
      static_assert(!std::is_same<float, Scalar>());
      _parent = parent;
      _content = startValue;
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

    ~NMTree() {
      if (_childs)
        killChildren();
    }

    void createChildren() {
      assert(_childs == nullptr);
      std::vector<size_t> size;
      size.resize(Dimension);
      std::fill(size.begin(), size.end(), ArraySize);
      _childs = new MultiDimensionalArray<Tree*, Dimension>(size);
      for (size_t i = 0; i < _childs->getSize(); i++)
        _childs->get_linearRef(i) = new Tree();
      _childs->apply([this](std::array<size_t, Dimension> pos, Tree*& child) {
        child->_size = _size / ArraySize;
        child->_content = _content;
        child->_parent = this;
        std::array<Scalar, Dimension> newPosition;
        for (int i = 0; i < Dimension; i++)
          newPosition[i] = _position[i] + pos[i] * child->_size;
        child->_position = newPosition;
        });
    }

    void killChildren() {
      for (size_t i = 0; i < _childs->getSize(); i++)
        delete _childs->get_linearVal(i);
      delete _childs;
      _childs = nullptr;
    }

    struct Leaf {
      std::array<Scalar, Dimension> position;
      Scalar                        size;
      Content                       value;
      NMTree<Content, ArraySize, Dimension, Merge, /*defaultValue, */Scalar>* link;

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
          auto subResult = _childs->get_linearVal(i)->getLeafs();
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

    Tree* getLeaf(std::array<Scalar, Dimension> position) {
      if (isLeaf()) 
        return this;
      std::array<size_t, Dimension> converted;
      for (size_t i = 0; i < Dimension; i++)
        converted[i] = (position[i] - getPosition()[i]) / (getSize() / ArraySize);
      Tree* t = getChild(converted);
      return t->getLeaf(position);
    }
    
    std::vector<Tree*> getAllChilds() {
      std::vector<Tree*> result;
      for (size_t i = 0; i < _childs->getSize(); i++) {
        result.push_back(_childs->get_linearRef(i));
      }
      return result;
    }

    void setContent(Content c) { _content = c; }
    Content getContent() { return _content; }
    Scalar getSize() { return _size; }
    std::array<Scalar, Dimension> getPosition() { return _position; }
    Tree* getParent() { return _parent; }
    bool  isLeaf() { return _childs == nullptr; }
    Tree* getChild(std::array<size_t, Dimension> pos) {
      assert(pos[0] != 18446744073709551537);
      return _childs->getVal(pos); 
    }
    std::set<Tree*> getSide(size_t dimension, NMTreeDirection direction) {
      auto slicePlane = ImageSubsetUtil::slice<Tree*, Dimension>(_childs, dimension, ((direction == NMTreeDirection::Negative) ? 0 : (ArraySize - 1)));
      std::set<Tree*> result;
      for (size_t i = 0; i < slicePlane->getSize(); i++)
        result.insert(slicePlane->get_linearVal(i));
      return result;
    }

  private:
    void recursiveFill(MultiDimensionalArray<Content, Dimension>* description) {
      assert(_size > 0);
      if (_size == 1) {
        for (size_t dim = 0; dim < Dimension; dim++)
          if (_position[dim] >= description->getDimension(dim)) {
            //_content = defaultValue;
            return;
          }
        _content = description->getVal(_position);
      }
      else {
        createChildren();
        for (int i = 0; i < _childs->getSize(); i++)
          assert(_childs->get_linearVal(i)->_size == _size / ArraySize);
#pragma omp parallel for  
        for (int i = 0; i < _childs->getSize(); i++) {
          _childs->get_linearVal(i)->recursiveFill(description);
        }

        bool allSame = true;
        Content compare = _childs->get_linearVal(0)->_content;
        Content merged = compare;

        for (uint64_t i = 1; i < _childs->getSize(); i++) {
          Content current = _childs->get_linearVal(i)->_content;
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
          if (_childs->get_linearVal(i)->_childs) {
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

    std::array<Scalar, Dimension>             _position          ;
    Scalar                                    _size     = 1      ;
    Content                                   _content           ;
    MultiDimensionalArray<Tree*, Dimension>*  _childs   = nullptr;
    Tree*                                     _parent            ;
  };
}