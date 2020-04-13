#pragma once

#include <array>

namespace Iyathuum {
  //RGBA color
  class Color
  {
  public:
    Color();
    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
    ~Color();

    unsigned char& r() { return _color[0]; }
    unsigned char& g() { return _color[1]; }
    unsigned char& b() { return _color[2]; }
    unsigned char& a() { return _color[3]; }
    unsigned char& red() { return _color[0]; }
    unsigned char& green() { return _color[1]; }
    unsigned char& blue() { return _color[2]; }
    unsigned char& alpha() { return _color[3]; }

    unsigned char getRed()   const { return _color[0]; }
    unsigned char getGreen() const { return _color[1]; }
    unsigned char getBlue()  const { return _color[2]; }

    static Color random();


    Color operator+(Color const& other)const
    {
      return Color(
        (_color[0] + other._color[0]) / 2,
        (_color[1] + other._color[1]) / 2,
        (_color[2] + other._color[2]) / 2);
    }

    unsigned char& operator [](int i);
  private:
    std::array<unsigned char, 4> _color;
  };
}
