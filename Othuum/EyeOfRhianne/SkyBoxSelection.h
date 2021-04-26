#pragma once

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include <memory>
#include <string>

#include "Graphic.h"

class ListSelection;

class SkyBoxSelection {
public:
  SkyBoxSelection(const std::string& path, Iyathuum::glmAABB<2> area, Graphic&);

  void update();
  void draw();

  void setVisible(bool);
  bool isVisible();
private:
  std::shared_ptr<ListSelection> _list;
  Graphic&                       _graphic;  
  std::string                    _path;
};