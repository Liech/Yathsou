#pragma once

//#include "structs/Factory.h"
#include "../OpenGL/Drawable.h"
#include <iostream>
class TextRenderer : public Drawable {
public:
  TextRenderer() {}
  virtual ~TextRenderer() {}

  virtual void load(DrawSpecification*) override { std::cout << "Hello Dependency injection madness" << std::endl; };
  virtual void draw() override{};

//  static inline Factory<Drawable>::Registrator<TextRenderer> RegisterTextRenderer("TextRenderer", {});
};