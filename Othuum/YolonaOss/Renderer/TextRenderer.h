#pragma once

//#include "structs/Factory.h"
#include "../OpenGL/Loadable.h"
#include <iostream>
#include "../structs/Factory.h"
#include "glm/glm.hpp"

class TextRenderer : public Loadable {
REGISTER(Loadable, TextRenderer, "TextRenderer", { "PreDrawCall" })
public:
  TextRenderer() {}
  virtual ~TextRenderer() {}

  static void drawText(std::string text, float x,float y, float scale, glm::vec3 color);

  virtual void load(DrawSpecification*) override { 
    std::cout << "Load Text Renderer" << std::endl; 
    //if (_alreadyLoaded)
    //  throw std::runtime_error("TextRenderer Twice Initialized.");
    //_alreadyLoaded = true;
  };
  
private:
  //static bool _alreadyLoaded = false;

};