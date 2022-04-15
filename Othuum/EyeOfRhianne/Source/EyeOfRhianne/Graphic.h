#pragma once

#include <memory>
#include <vector>
#include <AthanahCommonLib/SupCom/SupComMeshRendererDef.h>
#include <IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h>
#include <IyathuumCoreLib/BaseTypes/Color.h>

namespace Ahwassa {
  class Window;
  class DeferredComposer;
  class Bloom;
  class CubeReflection;
  class CubeTexture;
  class Texture;
  class AdditiveComposer;
  class BoxRenderer;
  struct DiffuseMeshRendererMesh;
}
namespace Athanah {
  class SkyBox;
  class Map;
  class MapRenderer;
}
namespace Haas {
  class ScriptEngine;
}
class Graphic {
public:
  Graphic(Ahwassa::Window*);

  void draw();
  std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color,2>> screenshot();
  void setModel(std::shared_ptr<Athanah::SupComModel>);

  std::shared_ptr<Athanah::SupComMesh> _mesh;
  int                                  _renderedTexture = 0;
  std::shared_ptr<Athanah::SupComModel> _model;

  std::vector<std::shared_ptr<Ahwassa::Texture>>    _textures;
  std::shared_ptr<Athanah::SupComMeshRendererDef>   _renderer;
  std::shared_ptr<Ahwassa::Bloom>                   _bloom;
  std::shared_ptr<Ahwassa::CubeReflection  >        _cubeReflection     ;
  bool                                              _bloomEnabled = true;
  std::shared_ptr<Athanah::SkyBox>                  _skyBox;
  std::shared_ptr<Ahwassa::CubeTexture>             _reflectionTexture;
  std::shared_ptr<Athanah::Map>                     _currentMap;
  std::shared_ptr<Haas::ScriptEngine>               _scripts;
  std::shared_ptr<Ahwassa::IMesh>                   _mapMesh = nullptr;
  std::shared_ptr<Athanah::MapRenderer>             _mapRenderer = nullptr;
  Ahwassa::Window* getWindow();
private:
  void drawScene();

  Ahwassa::Window*                                _window  ;
  std::shared_ptr<Ahwassa::DeferredComposer>      _composer;
};