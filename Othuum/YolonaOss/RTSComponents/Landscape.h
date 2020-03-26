#pragma once

#include <glm/glm.hpp>

#include <memory>

#include "../Navigation/MapGroup.h"
#include "../Navigation/DijkstraMap.h"
#include "../Navigation/GradientGridMap.h"
#include "../Navigation/DiscomfortGridMap.h"
#include "../structs/MultiDimensionalArray.h"
#include "../structs/NMTree.h"
#include "../structs/NMTreeNeighbourIndex.h"
#include "../structs/Dijkstra.h"
#include "../structs/NMTreeDijkstra.h"

namespace YolonaOss{
  template<size_t Dimension>
  class Landscape{
    using vec = typedef glm::vec<Dimension, float, glm::defaultp>;
    using Tree = NMTree<bool, Dimension, 2, YolonaOss::TreeMergeBehavior::Max, false>;
    using TreeI = NMTreeNeighbourIndex<bool, Dimension, 2, YolonaOss::TreeMergeBehavior::Max, false>;
  public:
    const int _disMapScale = 10;
    public:
      Landscape(std::string filename) {
        loadLandscape(filename);
      }

      std::shared_ptr<NavigationMap<Dimension>> getMap(vec target) {
        std::shared_ptr<MapGroup<Dimension>>          result     = std::make_shared<MapGroup<Dimension>>();
        std::shared_ptr<DijkstraMap<Dimension>>       navigation = std::make_shared<DijkstraMap<Dimension>>();
        std::shared_ptr<DiscomfortGridMap<Dimension>> dynamic    = std::make_shared<DiscomfortGridMap<Dimension>>(_dynamicDiscomfort);
        result->addMap(_staticMap, 0.2);
        result->addMap(navigation, 0.8);
        result->addMap(dynamic, 0.2);
        auto path = std::dynamic_pointer_cast<DijkstraI<Dimension>>(std::make_shared< NMTreeDijkstra<Dimension> >(target, _tree.get(), _index, [](Tree* node) {return 1; }));
        navigation->setDijkstra(path);        
        result->setTarget(target);
        return result;
      }

  private:
    void loadLandscape(std::string filename) {
      auto map = ImageIO::readImage(filename);
      _landscape = map->map<bool>([](Color const& c) { return (bool)(c.getRed() < 125); });

      std::array<size_t, 2> dim;
      dim[0] = _landscape->getDimension(0) * _disMapScale;
      dim[1] = _landscape->getDimension(1) * _disMapScale;
      double maxDistance = glm::distance(glm::vec2(0, 0), glm::vec2(dim[0] / 2, dim[1] / 2));
      auto scaled = ImageUtil::scaleUp<double, Dimension>(_landscape->map<double>([](const bool& val) {return val ? 1.0 : 0.0; }).get(), dim);
      scaled->apply([](size_t pos, double& val) {val = 1.0 - val; });
      _staticDiscomfort = std::shared_ptr<MultiDimensionalArray<double, 2>>(std::move(scaled));
      _dynamicDiscomfort = std::make_shared < DiscomfortGrid<Dimension>>(dim,_disMapScale);
      _staticMap = std::make_shared<GradientGridMap<Dimension>>((double)_disMapScale);
      _staticMap->setMap(_staticDiscomfort);
      _tree = std::make_shared<NMTree<bool, Dimension, 2, YolonaOss::TreeMergeBehavior::Max, false> >(_landscape.get());
      _index = std::make_shared<NMTreeNeighbourIndex<bool, Dimension, 2, YolonaOss::TreeMergeBehavior::Max, false>>(_tree.get());
      _index->init();
    }

    private:
    public:
      std::shared_ptr<MultiDimensionalArray<bool, Dimension>>   _landscape        ;
      std::shared_ptr<MultiDimensionalArray<double, Dimension>> _staticDiscomfort ;
      std::shared_ptr< GradientGridMap<Dimension> >             _staticMap        ;
      std::shared_ptr<DiscomfortGrid<Dimension>>                _dynamicDiscomfort;

      std::shared_ptr<Tree>                                     _tree             ;
      std::shared_ptr<TreeI>                                    _index            ;
  };
    
}