#pragma once

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include <memory>
#include <string>

#include "Graphic.h"

class ListSelection;

class RendererSelection {
public:
  RendererSelection(Iyathuum::glmAABB<2> area, Graphic&);

  void update();
  void draw();

  void setVisible(bool);
  bool isVisible();
private:
  std::shared_ptr<ListSelection> _list;
  Graphic& _graphic;
  std::map<std::string, int> _textures;


};