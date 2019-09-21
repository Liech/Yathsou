#pragma once

#include "Uniform.h"
#include "glad/glad.h"
#include "glm/glm.hpp"

#include <vector>
#include <string>

//SSBO has more capacity (Shader Storage Buffer Object - (texture trans dressing as normal array))
//UBO  is faster         (normal uniform variable in big)
namespace YolonaOss {
  namespace GL {
    class SSBOvec4 : public Uniform {
    public:
      SSBOvec4(std::string name, std::vector<glm::vec4> content);
      virtual ~SSBOvec4();

      virtual std::string toGLSL() override;
      virtual void bind() override;
      virtual std::string getType() override { return "vec4"; }
      void setData(std::vector<glm::vec4> content);

      virtual bool isBuffer() override { return true; }

    private:
      GLuint _ssbo;
    };

    class SSBOuint : public Uniform {
    public:
      SSBOuint(std::string name, std::vector<unsigned int> content);
      virtual ~SSBOuint();

      virtual std::string toGLSL() override;
      virtual void bind() override;
      virtual std::string getType() override { return "uint"; }
      void setData(std::vector<unsigned int> content);

      virtual bool isBuffer() override { return true; }

    private:
      GLuint _ssbo;
    };
  }
}
//template<typename Content, std::string structDescription>
//class SSBO : public Uniform {
//public:
//  SSBO(std::string name, Content content) : Uniform(name) {
//    glGenBuffers(1, &_ssbo);
//    glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
//    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Content), content, GL_DYNAMIC_COPY);
//    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
//
//  }
//  virtual ~SSBO() {}
//
//  virtual std::string toGLSL() override {
//    std::string result = "";
//    result += "layout (std430, binding=" + std::to_string(getLocation()) + ") buffer type" + getName() + "\n";
//    result += "{\n";
//    result += structDescription + " " + getName() + ";\n";
//    result += "};\n";
//    return result;
//  }
//  
//  virtual void bind() override
//  {
//    glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
//    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, getLocation(), _ssbo);
//  }
//
//  virtual std::string getType() override {
//    return structDescription;
//  }
//
//  void setData(Content& content) {
//    glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
//    GLvoid* p = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
//    memcpy(p, content, sizeof(Content));
//    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
//  }
//
//  virtual bool isBuffer() override { return true; }
//
//private:
//  GLuint _ssbo;
//};