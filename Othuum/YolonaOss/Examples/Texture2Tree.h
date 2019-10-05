#pragma once

#include "../OpenGL/Drawable.h"
#include "../structs/MultiDimensionalArray.h"
#include "../structs/NMTree.h"
#include "../structs/NMTreeNeighbourIndex.h"
#include <memory>

namespace YolonaOss {
  namespace GL {
    class DrawSpecification;
  }
  class Texture2Tree : public GL::Drawable {
    // Geerbt über Drawable
  public:
    virtual void load(GL::DrawSpecification*) override;
    virtual void draw() override;

  private:
    std::shared_ptr<MultiDimensionalArray<bool, 2>>                                         _map;
    std::shared_ptr<NMTree<bool, 2, 2, YolonaOss::TreeMergeBehavior::Max, false>>           _tree;
    std::shared_ptr<NMTreeNeighbourIndex<bool, 2, 2, YolonaOss::TreeMergeBehavior::Max, false>> _index;
  };
}