#include "Uniform.h"

#include <cassert>

namespace Ahwassa {
  Uniform::Uniform(const std::string& name) { 
    _name = name; 
  }

  std::string Uniform::toGLSL() const {
    return "layout(location = " + std::to_string(getLocation()) + ") uniform " + getType() + " " + getName() + getArrayPostfix() + ";\n";
  }

  std::string Uniform::getName() const {
    return _name; 
  }

  void Uniform::setLocation(int location) {
    _location = location; 
  }

  int  Uniform::getLocation() const  {
    return _location; 
  }

  bool Uniform::isActive() const {
    return _location == -1;
  }

  bool Uniform::isBindable() const {
    return _bindable; 
  }

  void Uniform::setBindable(bool val) {
    _bindable = val; 
  }

  bool Uniform::isTexture() const {
    return false;
  }

  void Uniform::setTextureLocation(int location) { 
    assert(_texLoc == -1);
    assert(isTexture());
    _texLoc = location; 
  }

  int Uniform::getTextureLocation() const {
    assert(isTexture()); 
    return _texLoc;
  }

  std::string Uniform::getArrayPostfix() const {
    return ""; 
  }

  int Uniform::getNumberOfLocationsUsed() const {
    return 1;
  }

  bool Uniform::isBuffer() const {
    return false;
  }
  
  bool Uniform::isAttribute() const {
    return false;
  }

}