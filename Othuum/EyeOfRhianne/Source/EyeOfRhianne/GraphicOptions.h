#pragma once

#include <memory>
#include <functional>
#include <map>
#include "Graphic.h"
#include <nlohmann/json.hpp>

namespace Ahwassa {
  class Window;
  class Button;
  class Texture;
  class Slider;
  class Label;
  class ListLayout;
  class Bloom;
}

class ListSelection;

class GraphicOptions {
public:
  GraphicOptions(std::function<void()> disableAllCall, Graphic& graphic);

  void update();
  void drawUI();

  void setVisible(bool visible);
  bool isVisible();

  std::shared_ptr<Ahwassa::Texture> getCurrentTexture();

private:
  void makeBloomOptions();
  void initScript();

  std::shared_ptr<Ahwassa::Button>               _showHide;
  bool                                           _visible = false;
  std::function<void()>                          _disableAllCall;
  std::map<std::string,int> _textures;
  std::shared_ptr<Ahwassa::Texture>              _currentTexture;
  std::shared_ptr<Ahwassa::ListLayout>           _bloomOptions;
  Graphic& _graphic;


  std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> _setBloomQuality   ;
  std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> _setBloomDirections;
  std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> _setBloomIntensity ;
  std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> _setBloomSize      ;
};