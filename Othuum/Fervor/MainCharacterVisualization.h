#pragma once

#include "YolonaOss/OpenGL/Drawable.h"

class MainCharacter;

class MainCharacterVisualization : public YolonaOss::GL::Drawable
{
public:
  MainCharacterVisualization(const MainCharacter&);
  virtual void load(YolonaOss::GL::DrawSpecification*) override;
  virtual void draw(                                 ) override;


private:
  const MainCharacter& _target;
};