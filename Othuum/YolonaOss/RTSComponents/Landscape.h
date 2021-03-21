#pragma once

#include <IyathuumCoreLib/lib/glm/glm.hpp>

#include <memory>

#include "SelenNavigationLib/MapGroup.h"
#include "SelenNavigationLib/Maps/DijkstraMap.h"
#include "SelenNavigationLib/Maps/GradientGridMap.h"
#include "SelenNavigationLib/Maps/DiscomfortMap.h"
#include "SelenNavigationLib/Maps/ComfortMap.h"
#include "SelenNavigationLib/Maps/DirectDistanceMap.h"
#include "SelenNavigationLib/Maps/AligmentMap.h"
#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"
#include "IyathuumCoreLib/Tree/NMTree.h"
#include "IyathuumCoreLib/Tree/NMTreeNeighbourIndex.h"
#include "IyathuumCoreLib/Tree/Dijkstra.h"
#include "IyathuumCoreLib/Tree/NMTreeDijkstra.h"
#include "IyathuumCoreLib/Util/ImageUtil.h"
#include "SelenNavigationLib/Maps/InfectiousArrivalMapGroup.h"
#include "YolonaOss/Util/Util.h"
#include "YolonaOss/Util/ImageIO.h"

namespace YolonaOss{
  template<size_t Dimension>
  class Landscape{
    using vec   = glm::vec<Dimension, float, glm::defaultp>;
    using Tree  = Iyathuum::NMTree<bool, Dimension, 2, Iyathuum::TreeMergeBehavior::Max>;
    using TreeI = Iyathuum::NMTreeNeighbourIndex<bool, Dimension, 2, Iyathuum::TreeMergeBehavior::Max>;
  public:
    const int _disMapScale = 10;
    public:
      Landscape(std::string filename) {
        loadLandscape(filename);
      }
      void setConfig(std::array<float, 20> config) {
        _config = config;
      }

      std::shared_ptr<Selen::InfectiousArrivalMapGroup<Dimension>> arrival = nullptr;
      std::shared_ptr<Selen::NavigationMap<Dimension>> getMap(vec target) {
        std::shared_ptr<Selen::MapGroup<Dimension>>                  result     = std::make_shared<Selen::MapGroup                 <Dimension>>(           );
        std::shared_ptr<Selen::DijkstraMap<Dimension>>               navigation = std::make_shared<Selen::DijkstraMap              <Dimension>>(           );
        std::shared_ptr<Selen::DiscomfortMap<Dimension>>             discomfort = std::make_shared<Selen::DiscomfortMap            <Dimension>>(_unitAgents);
        std::shared_ptr<Selen::ComfortMap<Dimension>>                comfort    = std::make_shared<Selen::ComfortMap               <Dimension>>(_unitAgents);
        std::shared_ptr<Selen::AligmentMap<Dimension>>               alignment  = std::make_shared<Selen::AligmentMap              <Dimension>>(_unitAgents);
        std::shared_ptr<Selen::DirectDistanceMap<Dimension>>         direct     = std::make_shared<Selen::DirectDistanceMap        <Dimension>>(           );
        /*std::shared_ptr<Selen::InfectiousArrivalMapGroup<Dimension>>*/ arrival    = std::make_shared<Selen::InfectiousArrivalMapGroup<Dimension>>(_unitAgents);
        result ->addMap(_staticMap  , _config[0]);
        arrival->addMap(navigation  , _config[1]);
        arrival->addMap(direct      , _config[2]);
        result ->addMap(arrival     , 1         );        
        result ->addMap(discomfort  , _config[3]);
        result ->addMap(comfort     , _config[4]);
        result ->addMap(alignment   , _config[5]);
        auto path = std::dynamic_pointer_cast<Iyathuum::DijkstraI<Dimension>>(std::make_shared< Iyathuum::NMTreeDijkstra<Dimension> >(Util<Dimension>::template vec2Array<double>(target), _tree.get(), _index, [](Tree* node) {return 1; }));
        navigation->setDijkstra(path);        
        result->setTarget(Util<Dimension>::template vec2Array<double>(target));
        return result;
      }

  private:
    void loadLandscape(std::string filename) {
      auto map = ImageIO::readImage(filename);
      _landscape = map->map<bool>([](Iyathuum::Color const& c) { return (bool)(c.getRed() < 125); });

      std::array<size_t, 2> dim;
      dim[0] = _landscape->getDimension(0) * _disMapScale;
      dim[1] = _landscape->getDimension(1) * _disMapScale;
      double maxDistance = glm::distance(glm::vec2(0, 0), glm::vec2(dim[0] / 2, dim[1] / 2));
      auto scaled = Iyathuum::ImageUtil::scaleUp<double, Dimension>(_landscape->map<double>([](const bool& val) {return val ? 1.0 : 0.0; }).get(), dim);
      scaled->apply([](size_t pos, double& val) {val = 1.0 - val; });
      _staticDiscomfort = std::shared_ptr<Iyathuum::MultiDimensionalArray<double, 2>>(std::move(scaled));
      _unitAgents = std::make_shared < Selen::NavigationAgentManager<Dimension>>(Iyathuum::AABB<Dimension>(Iyathuum::Geometry<Dimension>::value(0), Iyathuum::Geometry<Dimension>::value(dim[0])));
      _staticMap = std::make_shared<Selen::GradientGridMap<Dimension>>((double)_disMapScale);
      _staticMap->setMap(_staticDiscomfort);
      _tree = std::make_shared<Tree>(_landscape.get(), false);
      _index = std::make_shared<Iyathuum::NMTreeNeighbourIndex<bool, Dimension, 2, Iyathuum::TreeMergeBehavior::Max>>(_tree.get());
      _index->init();
    }

    private:
    public:
      std::shared_ptr<Iyathuum::MultiDimensionalArray<bool, Dimension>>   _landscape        ;
      std::shared_ptr<Iyathuum::MultiDimensionalArray<double, Dimension>> _staticDiscomfort ;
      std::shared_ptr<Selen::GradientGridMap<Dimension> >                 _staticMap        ;
      std::shared_ptr<Selen::NavigationAgentManager<Dimension>>           _unitAgents       ;
                                                                         
      std::shared_ptr<Tree>                                               _tree             ;
      std::shared_ptr<TreeI>                                              _index            ;

      std::array<float, 20> _config; //temporary
  };
    
}