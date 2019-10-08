#pragma once

#include "../OpenGL/Drawable.h"
#include "../structs/MultiDimensionalArray.h"
#include "../structs/NMTree.h"
#include "../structs/NMTreeNeighbourIndex.h"
#include "../structs/Dijkstra.h"
#include <memory>

namespace YolonaOss {
  namespace GL {
    class DrawSpecification;
  }
  using Tree = NMTree<bool, 2, 2, YolonaOss::TreeMergeBehavior::Max, false>;
  using TreeI = NMTreeNeighbourIndex<bool, 2, 2, YolonaOss::TreeMergeBehavior::Max, false>;

  class Texture2Tree : public GL::Drawable {
    // Geerbt über Drawable
  public:
    virtual void load(GL::DrawSpecification*) override;
    virtual void draw() override;

  private:
    std::shared_ptr<MultiDimensionalArray<bool, 2>> _map;
    std::shared_ptr<Tree>                           _tree;
    std::shared_ptr<TreeI>                          _index;
    std::shared_ptr < Dijkstra<Tree>>               _path; 
  };
}