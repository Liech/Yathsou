#include "Background.h"

#include "glad/glad.h"


namespace YolonaOss {
  Background::Background()
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
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  }
}