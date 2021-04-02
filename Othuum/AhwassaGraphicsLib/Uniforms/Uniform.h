#pragma once

#include <string>
#include <vector>
#include "IyathuumCoreLib/lib/glm/glm.hpp"

namespace Ahwassa {
  class Uniform
  {
  public:
    Uniform(std::string name);
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
  private:
    std::string _name;
    int         _location = -1;
    int         _texLoc   = -1;
    bool        _bindable = true;
  };
}