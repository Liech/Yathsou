#include "MapTextureSelection.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include <filesystem>

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicRectangleRenderer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTexture2DRenderer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTextRenderer.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AhwassaGraphicsLib/Renderer/BoxRenderer.h"
#include "AhwassaGraphicsLib/Renderer/Box.h"
#include "AhwassaGraphicsLib/Renderer/Dot.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/Renderer/DiffuseMeshRenderer.h"

#include "ListSelection.h"
#include "Graphic.h"
#include "AthanahCommonLib/Map/Scenario.h"
#include "AthanahCommonLib/Map/Map.h"
#include "AthanahCommonLib/Map/MapFactory.h"
#include "AezeselFileIOLib/ImageIO.h"
#include "AezeselFileIOLib/SupremeCommander/SCMAP.h"
#include "AhwassaGraphicsLib/Geometry/HeightFieldMeshGenerator.h"

MapTextureSelection::MapTextureSelection(Iyathuum::glmAABB<2> area, Graphic& graphic) : _graphic(graphic) {
  _area = area;

  std::vector<std::string> textures;
  textures.push_back("None");
  textures.push_back("Preview");
  textures.push_back("Height");
  textures.push_back("High");
  textures.push_back("Low");
  textures.push_back("Water");
  textures.push_back("Normal");
  textures.push_back("Water Foam Mask");
  textures.push_back("Flatness");
  textures.push_back("Depth Bias Mask");
  textures.push_back("Terrain Type");
  textures.push_back("High Red"  );
  textures.push_back("High Green");
  textures.push_back("High Blue" );
  textures.push_back("High Alpha");
  textures.push_back("Low Red"   );
  textures.push_back("Low Green" );
  textures.push_back("Low Blue"  );
  textures.push_back("Low Alpha" );
  textures.push_back("Water Red"   );
  textures.push_back("Water Green" );
  textures.push_back("Water Blue"  );
  textures.push_back("Water Alpha" );


  _list = std::make_unique<ListSelection>(textures, textures, area, _graphic.getWindow(), [this](std::string img) {
    setImage(img);
  });
  _list->setVisible(false);
}

void MapTextureSelection::setImage(std::string img) {
  if (!_graphic._currentMap)
    return;
  if (img == "None") {
    _graphic._previewImage = nullptr; 
    _graphic._boxRenderer->clear();
    _boxes.clear();
    _dots.clear();
  }
  else if (img == "Preview")
    _graphic._previewImage = std::make_shared<Ahwassa::Texture>("Preview", _graphic._currentMap->scmap().previewImage.get());
  else if (img == "High")
    _graphic._previewImage = std::make_shared<Ahwassa::Texture>("Preview", _graphic._currentMap->scmap().highTexture.get());
  else if (img == "Low")
    _graphic._previewImage = std::make_shared<Ahwassa::Texture>("Preview", _graphic._currentMap->scmap().lowTexture.get());
  else if (img == "Water")
    _graphic._previewImage = std::make_shared<Ahwassa::Texture>("Preview", _graphic._currentMap->scmap().waterMapTexture.get());
  else if (img == "Normal")
    _graphic._previewImage = std::make_shared<Ahwassa::Texture>("Preview", _graphic._currentMap->scmap().normalMap.get());
  else if (img == "Height") {
    auto m = _graphic._currentMap->scmap().heightMapData.get();
    std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> colored = std::make_unique< Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>(m->getDimensionVector());
    colored->apply([&m](size_t pos, Iyathuum::Color& clr) {
      unsigned char d = m->get_linearVal(pos);
      Iyathuum::Color result(255 * d / std::numeric_limits<unsigned short>().max(), 0, 0, 255);
      clr = result;
    });
    _graphic._previewImage = std::make_shared<Ahwassa::Texture>("Preview", colored.get());
    //setGeometry(colored->getDimension(0), colored->getDimension(1), [m](int x, int y) {return 10*(float)m->getVal(x, y) / (float)std::numeric_limits<unsigned short>().max(); });

    _mesh = std::make_shared< Ahwassa::DiffuseMeshRendererMesh>();
    _mesh->mesh = Ahwassa::HeightFieldMeshGenerator::generate<unsigned short>(*m, 0, std::numeric_limits<unsigned short>().max(), 5, 1);
    _graphic.getWindow()->renderer().mesh().addMesh(_mesh);
    _dots.clear();

  }
  else if (
    img == "High Red"    ||
    img == "High Green"  ||
    img == "High Blue"   ||
    img == "High Alpha"  ||
    img == "Low Red"     ||
    img == "Low Green"   ||
    img == "Low Blue"    ||
    img == "Low Alpha"   ||
    img == "Water Red"   ||
    img == "Water Green" ||
    img == "Water Blue"  ||
    img == "Water Alpha"
    ) {
    Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>* im;
    int channel = 0;
    if (img == "High Red") { channel = 0; im = _graphic._currentMap->scmap().highTexture.get(); }
    else if (img == "High Green" ) { channel = 1; im = _graphic._currentMap->scmap().highTexture.get(); }
    else if (img == "High Blue"  ) { channel = 2; im = _graphic._currentMap->scmap().highTexture.get(); }
    else if (img == "High Alpha" ) { channel = 3; im = _graphic._currentMap->scmap().highTexture.get(); }
    else if (img == "Low Red"    ) { channel = 0; im = _graphic._currentMap->scmap().lowTexture.get(); }
    else if (img == "Low Green"  ) { channel = 1; im = _graphic._currentMap->scmap().lowTexture.get(); }
    else if (img == "Low Blue"   ) { channel = 2; im = _graphic._currentMap->scmap().lowTexture.get(); }
    else if (img == "Low Alpha"  ) { channel = 3; im = _graphic._currentMap->scmap().lowTexture.get(); }
    else if (img == "Water Red"  ) { channel = 0; im = _graphic._currentMap->scmap().waterMapTexture.get(); }
    else if (img == "Water Green") { channel = 1; im = _graphic._currentMap->scmap().waterMapTexture.get(); }
    else if (img == "Water Blue" ) { channel = 2; im = _graphic._currentMap->scmap().waterMapTexture.get(); }
    else if (img == "Water Alpha") { channel = 3; im = _graphic._currentMap->scmap().waterMapTexture.get(); }
    else throw std::runtime_error("Unkown type");

    std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> colored = std::make_unique< Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>(im->getDimensionVector());
    colored->apply([&im,channel](size_t pos, Iyathuum::Color& clr) {
      auto d = im->get_linearVal(pos)[channel];
      Iyathuum::Color result(d, 0, 0, 255);
      clr = result;
    });
    _graphic._previewImage = std::make_shared<Ahwassa::Texture>("Preview", colored.get());
    setGeometry(colored->getDimension(0), colored->getDimension(1), [im,channel](int x, int y) {return (float)im->getVal(x, y)[channel] / (float)std::numeric_limits<unsigned char>().max(); });
  }
  else {
    Iyathuum::MultiDimensionalArray<unsigned char, 2>* m;
    if (img == "Water Foam Mask")
      m = _graphic._currentMap->scmap().waterFoamMaskData.get();
    else if (img == "Flatness")
      m = _graphic._currentMap->scmap().flatnessData.get();
    else if (img == "Depth Bias Mask")
      m = _graphic._currentMap->scmap().depthBiasMaskData.get();
    else if (img == "Terrain Type")
      m = _graphic._currentMap->scmap().terrainTypeData.get();
    else throw std::runtime_error("unkown type");

    std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> colored = std::make_unique< Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>(m->getDimensionVector());
    colored->apply([&m](size_t pos, Iyathuum::Color& clr) {
      unsigned char d = m->get_linearVal(pos);
      Iyathuum::Color result(d, 0, 0, 255);
      clr = result;
    });
    _graphic._previewImage = std::make_shared<Ahwassa::Texture>("Preview", colored.get());
    setGeometry(colored->getDimension(0), colored->getDimension(1), [m](int x, int y) {return (float)m->getVal(x, y) / (float)std::numeric_limits<unsigned char>().max(); });
  }
}


void MapTextureSelection::setGeometry(int width, int height, std::function<float(int x,int y)> f) {
  _graphic._boxRenderer->clear();
  _boxes.clear();
  _dots.clear();
  float boxScale = 0.1f;
  float distanceScale = 0.1f;
  float heightScale = 20;
  for (int x = 0; x < width; x++)
    for (int y = 0; y < height; y++)
    {
      glm::mat4 t(1);
      t = glm::translate(t,glm::vec3(x, 0, y)* distanceScale);
      t = glm::scale(t, glm::vec3(boxScale, f(x, y)* heightScale, boxScale));
      _boxes.push_back(_graphic._boxRenderer->newBox(t));
    }
}

void MapTextureSelection::setVisible(bool value) {
  _list->setVisible(value);
}

bool MapTextureSelection::isVisible() {
  return _list->isVisible();
}

void MapTextureSelection::update() {

}

void MapTextureSelection::draw() {
  _list->draw();
}
