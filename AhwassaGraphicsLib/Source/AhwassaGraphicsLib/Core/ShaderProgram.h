#pragma once

#include <string>
#include <vector>

namespace Ahwassa {
  struct AttributeDescription;
  class  Uniform;

  class ShaderProgram
  {
  public:
    ShaderProgram(const std::vector<AttributeDescription>&, std::vector<Uniform*> uniforms, std::string vs, std::string fs);
    virtual ~ShaderProgram();

    void bind();
    unsigned int getID();

  private:
    std::vector<AttributeDescription> _attributes     ;
    unsigned int                      _program        ;
    std::vector<Uniform*>             _uniform        ;
    std::vector<Uniform*>             _attributeUniforms; //<- not really a uniform anymore
    std::vector<bool>                 _uniformIsActive;

    std::string toGLSL_vs(std::string shader);
    std::string toGLSL_fs(std::string shader);
    void checkUsageOfUniforms();
    std::string AttributetoGLSL(size_t locationOffset = 0);
  };
}