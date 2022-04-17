#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace Ahwassa {

  //not what an opengl uniform is. Well it was the same in the beginning.
  //e.g. instanced arrays are also uniforms here for simplicity
  class Uniform
  {
  public:
    Uniform(const std::string& name);
    virtual ~Uniform() = default;

    virtual void bind() = 0;

            std::string getName();
            void        setLocation(int location);
            int         getLocation();
            bool        isActive();
            bool        isBindable();
            void        setBindable(bool val);
    virtual bool        isTexture();
            void        setTextureLocation(int location);
            int         getTextureLocation();
    virtual std::string getArrayPostfix();
    virtual int         getNumberOfLocationsUsed();
    virtual std::string toGLSL();
    virtual std::string getType() = 0;
    virtual bool        isBuffer();
    virtual bool        isAttribute();
  private:
    std::string _name;
    int         _location = -1;
    int         _texLoc   = -1;
    bool        _bindable = true;
  };
}