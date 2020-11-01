#pragma once

#include "VAO.h"
#include "IBO.h"
#include "Uniform.h"
#include <string>
namespace YolonaOss {
  namespace GL {
    class ShaderProgram
    {
    public:
      ShaderProgram(const std::vector<AttributeDescription>&, std::vector<Uniform*> uniforms, std::string vs, std::string fs);
      
      ~ShaderProgram();


      void bind();
      GLuint getID() { return _program; };

    private:
      std::string _vertexShader;
      std::string _fragmentShader;

      std::vector<AttributeDescription> _attributes;
      GLuint _program;
      std::vector<Uniform*> _uniform;
      std::vector<bool>     _uniformIsActive;

      std::string toGLSL_vs();
      std::string toGLSL_fs();
      void checkUsageOfUniforms();
      std::string AttributetoGLSL(size_t locationOffset = 0);
    };
  }
}