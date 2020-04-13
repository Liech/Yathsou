#include "Color.h"
#include <assert.h>
#include <stdlib.h>
namespace Iyathuum {

  Color::Color()
  {
    _color.fill(0);
  }

  Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    _color[0] = r;
    _color[1] = g;
    _color[2] = b;
    _color[3] = a;
  }


  Color::~Color()
  {
  }

  unsigned char& Color::operator [](int i) {
    assert(i >= 0);
    assert(i < 4);
    return _color[i];
  }

  Color Color::random() {
    return Color(rand() % 255, rand() % 255, rand() % 255);
  }
}