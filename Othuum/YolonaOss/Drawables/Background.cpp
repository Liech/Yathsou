#include "Background.h"

#include "glad/glad.h"


namespace YolonaOss {
  Background::Background() :
    color(0.2f, 0.3f, 0.3f)
  {
  }


  Background::~Background()
  {
  }

  void Background::load(GL::DrawSpecification*)
  {
  }

  void Background::draw()
  {
    glClearColor(color[0], color[1], color[2],1);
    glClear(GL_COLOR_BUFFER_BIT);
  }
}