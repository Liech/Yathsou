#pragma once

#include <glm/glm.hpp>

#include <memory>

#include "../Navigation/MapGroup.h"
#include "../Navigation/DijkstraMap.h"
#include "../Navigation/GradientGridMap.h"
#include "../Navigation/DiscomfortMap.h"
#include "../Navigation/ComfortMap.h"
#include "../Navigation/DirectDistanceMap.h"
#include "../Navigation/AligmentMap.h"
#include "../structs/MultiDimensionalArray.h"
#include "../structs/NMTree.h"
#include "../structs/NMTreeNeighbourIndex.h"
#include "../structs/Dijkstra.h"
#include "../structs/NMTreeDijkstra.h"

namespace YolonaOss{
  template<size_t Dimension>
  class Landscape{
    using vec = glm::vec<Dimension, float, glm::defaultp>;
    using Tree = NMTree<bool, Dimension, 2, YolonaOss::TreeMergeBehavior::Max>;
    using TreeI = NMTreeNeighbourIndex<bool, Dimension, 2, YolonaOss::TreeMergeBehavior::Max>;
  public:
    const int _disMapScale = 10;
    public:
      Landscape(std::string filename) {
        loadLandscape(filename);
      }
      void setConfig(std::array<float, 20> config) {
        _config = config;
      }

      std::shared_ptr<NavigationMap<Dimension>> getMap(vec target) {
        std::shared_ptr<MapGroup<Dimension>>         result     = std::make_shared<MapGroup         <Dimension>>(           );
        std::shared_ptr<DijkstraMap<Dimension>>      navigation = std::make_shared<DijkstraMap      <Dimension>>(           );
        std::shared_ptr<DiscomfortMap<Dimension>>    discomfort = std::make_shared<DiscomfortMap    <Dimension>>(_unitAgents);
        std::shared_ptr<ComfortMap<Dimension>>       comfort    = std::make_shared<ComfortMap       <Dimension>>(_unitAgents);
        std::shared_ptr<AligmentMap<Dimension>>      alignment  = std::make_shared<AligmentMap      <Dimension>>(_unitAgents);
        std::shared_ptr<DirectDistanceMap<Dimension>> direct    = std::make_shared<DirectDistanceMap<Dimension>>(           );
        result->addMap(_staticMap  , _config[0]);
        result->addMap(navigation  , _config[1]);
        result->addMap(direct      , _config[2]);
        result->addMap(discomfort  , _config[3]);
        result->addMap(comfort     , _config[4]);
        result->addMap(alignment   , _config[5]);
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
      _unitAgents = std::make_shared < NavigationAgentManager<Dimension>>(AABB<Dimension>(vec(0.0f),(float)dim[0]));
      _staticMap = std::make_shared<GradientGridMap<Dimension>>((double)_disMapScale);
      _staticMap->setMap(_staticDiscomfort);
      _tree = std::make_shared<Tree>(_landscape.get(), false);
      _index = std::make_shared<NMTreeNeighbourIndex<bool, Dimension, 2, YolonaOss::TreeMergeBehavior::Max>>(_tree.get());
      _index->init();
    }

    private:
    public:
      std::shared_ptr<MultiDimensionalArray<bool, Dimension>>   _landscape        ;
      std::shared_ptr<MultiDimensionalArray<double, Dimension>> _staticDiscomfort ;
      std::shared_ptr< GradientGridMap<Dimension> >             _staticMap        ;
      std::shared_ptr<NavigationAgentManager<Dimension>>        _unitAgents       ;

      std::shared_ptr<Tree>                                     _tree             ;
      std::shared_ptr<TreeI>                                    _index            ;

      std::array<float, 20> _config; //temporary
  };
    
}