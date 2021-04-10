#include "Uniform.h"

#include <cassert>

namespace Ahwassa {
  Uniform::Uniform(std::string name) { 
    _name = name; 
  }

  std::string Uniform::toGLSL() {
    return "layout(location = " + std::to_string(getLocation()) + ") uniform " + getType() + " " + getName() + getArrayPostfix() + ";\n";
  }

  std::string Uniform::getName() { 
    return _name; 
  }

  void Uniform::setLocation(int location) {
    _location = location; 
  }

  int  Uniform::getLocation() {
    return _location; 
  }

  bool Uniform::isActive() {
    return _location == -1;
  }

  bool Uniform::isBindable() { 
    return _bindable; 
  }

  void Uniform::setBindable(bool val) {
    _bindable = val; 
  }

  bool Uniform::isTexture() {
    return false;
  }

  void Uniform::setTextureLocation(int location) { 
    assert(_texLoc == -1);
    assert(isTexture());
    _texLoc = location; 
  }

  int Uniform::getTextureLocation() {
    assert(isTexture()); 
    return _texLoc;
  }

  std::string Uniform::getArrayPostfix() {
    return ""; 
  }

  int Uniform::getNumberOfLocationsUsed() {
    return 1;
  }

  bool Uniform::isBuffer() {
    return false;
  }
  
  bool Uniform::isAttribute() {
    return false;
  }

}