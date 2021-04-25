#pragma once

#include <memory>
#include <vector>
#include "AthanahCommonLib/SupComMeshRendererDef.h"

namespace Ahwassa {
  class Window;
  class DeferredComposer;
  class Bloom;
  class Texture;
}
namespace Athanah {
  class SkyBox;
}

class Graphic {
public:
  Graphic(Ahwassa::Window*);

  void draw();
  void setModel(std::shared_ptr<Athanah::SupComModel>);

  std::shared_ptr<Athanah::SupComMesh> _mesh;
  int                                  _renderedTexture = 0;
  std::shared_ptr<Athanah::SupComModel> _model;

  std::vector<std::shared_ptr<Ahwassa::Texture>> _textures;
  std::shared_ptr<Athanah::SupComMeshRendererDef> _renderer;
  std::shared_ptr<Ahwassa::Bloom>                 _bloom   ;
  std::shared_ptr<Athanah::SkyBox>                _skyBox;

  Ahwassa::Window* getWindow();
private:
  Ahwassa::Window*                                _window  ;
  std::shared_ptr<Ahwassa::DeferredComposer>      _composer;
};