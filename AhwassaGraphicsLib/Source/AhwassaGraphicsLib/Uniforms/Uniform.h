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

            std::string getName()                 const;
            void        setLocation(int location);
            int         getLocation()             const;
            bool        isActive()                const;
            bool        isBindable()              const;
            void        setBindable(bool val);
    virtual bool        isTexture()               const;
            void        setTextureLocation(int location);
            int         getTextureLocation()      const;
    virtual std::string getArrayPostfix()         const;
    virtual int         getNumberOfLocationsUsed()const;
    virtual std::string toGLSL()                  const;
    virtual std::string getType()                 const = 0;
    virtual bool        isBuffer()                const;
    virtual bool        isAttribute()             const;
  private:
    std::string _name;
    int         _location = -1;
    int         _texLoc   = -1;
    bool        _bindable = true;
  };
}