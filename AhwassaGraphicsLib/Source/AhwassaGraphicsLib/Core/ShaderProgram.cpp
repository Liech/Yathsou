#include "ShaderProgram.h"

#include <set>
#include <iostream>
#include <sstream>

#include <glad/glad.h>
#include "AhwassaGraphicsLib/Uniforms/Uniform.h"
#include "AhwassaGraphicsLib/Core/AttributeDescription.h"

namespace Ahwassa {
  ShaderProgram::ShaderProgram(const std::vector<AttributeDescription>& attributes, std::vector<Uniform*> uniforms, std::string vsmain, std::string fsmain)
  {
    _attributes = attributes;
    _uniform = uniforms;

    size_t attributeUniformLocations = 0;

    for (int i = 0; i < _uniform.size(); i++) {
      if (_uniform[i]->isAttribute()) {
        _attributeUniforms.push_back(_uniform[i]);
        _uniform[i]->setLocation((int)(attributes.size() + attributeUniformLocations));

        attributeUniformLocations+= _uniform[i]->getNumberOfLocationsUsed();
        _uniform.erase(_uniform.begin() + i);
        i--;
      }
    }

    _uniformIsActive.resize(_uniform.size());
    size_t ssboLocations = 0;
    size_t textureLocations = 0;
    size_t uniformLocations = 0;

    for (int i = 0; i < _uniform.size(); i++) {
      if (_uniform[i]->isBuffer()) {
        _uniform[i]->setLocation((int)ssboLocations);
        ssboLocations++;
      }
      else {
        _uniform[i]->setLocation((int)uniformLocations);
        uniformLocations += _uniform[i]->getNumberOfLocationsUsed();
      }
      if (_uniform[i]->isTexture()) {
        _uniform[i]->setTextureLocation((int)textureLocations);
        textureLocations++;
      }
      _uniformIsActive[i] = false;
    }

    std::string vssrc = toGLSL_vs(vsmain);
    std::string fssrc = toGLSL_fs(fsmain);

    std::string s(fssrc);
    std::string m = "";
    int currentStart = 0;
    int line = 1;
    for (int i = 0; i < s.length(); i++) {
      if (s[i] == '\n') {
        m += std::to_string(line) + " " + s.substr(currentStart, i - currentStart) + "\n";
        currentStart = i + 1;
        line++;
      }
    }
    m += std::to_string(line) + " " + s.substr(currentStart, s.length() - 1);

    std::string s2(vssrc);
    std::string m2 = "";
    currentStart = 0;
    line = 1;
    for (int i = 0; i < s2.length(); i++) {
      if (s2[i] == '\n') {
        m2 += std::to_string(line) + " " + s2.substr(currentStart, i - currentStart) + "\n";
        currentStart = i + 1;
        line++;
      }
    }
    m2 += std::to_string(line) + " " + s2.substr(currentStart, s2.length() - 1);


    //std::cout << std::endl << "SHADER VS" << std::endl << m2 << std::endl;
    //std::cout << std::endl << "SHADER FS" << std::endl << m << std::endl;

    const char* vs_src = vssrc.c_str();
    const char* fs_src = fssrc.c_str();
    GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_src, nullptr);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
    char logBuf[1024];
    int len;
    if (0 == compile_ok)
    {
      glGetShaderInfoLog(vs, sizeof(logBuf), &len, logBuf);
      std::cout << numberLines(vs_src) << std::endl;
      std::cout << "-----------" << std::endl;
      std::cout << logBuf << std::endl;
      throw std::runtime_error(logBuf);
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_src, nullptr);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
    if (0 == compile_ok)
    {
      glGetShaderInfoLog(fs, sizeof(logBuf), &len, logBuf);
      std::cout << numberLines(fs_src) << std::endl;
      std::cout << "-----------" << std::endl;
      std::cout << logBuf << std::endl;
      throw std::runtime_error(logBuf);
    }


    _program = glCreateProgram();
    glAttachShader(_program, vs);
    glAttachShader(_program, fs);
    glLinkProgram(_program);
    glGetProgramiv(_program, GL_LINK_STATUS, &link_ok);
    if (!link_ok)
    {
      glGetShaderInfoLog(vs, sizeof(logBuf), &len, logBuf);
      throw std::runtime_error(logBuf);
    }
    glDeleteShader(vs);
    glDeleteShader(fs);

    checkUsageOfUniforms();
  }

  unsigned int ShaderProgram::getID() const { 
    return _program; 
  };

  void ShaderProgram::checkUsageOfUniforms() {
    GLint count;
    GLint size; // size of the variable
    GLenum type; // type of the variable (float, vec3 or mat4, etc)

    const GLsizei bufSize = 32; // maximum name length
    GLchar name[bufSize]; // variable name in GLSL
    GLsizei length; // name length

    glGetProgramiv(_program, GL_ACTIVE_UNIFORMS, &count);
    std::set<std::string> activeNames;

    for (int i = 0; i < count; i++)
    {
      if (_uniform[i]->isBuffer())
        continue;
      glGetActiveUniform(_program, i, bufSize, &length, &size, &type, name);
      activeNames.insert(name);
    }
    for (int i = 0; i < _uniform.size(); i++) {
      if (_uniform[i]->isBuffer())
        continue;
      _uniformIsActive[i] = activeNames.count(_uniform[i]->getName()) != 0 || activeNames.count(_uniform[i]->getName() + "[0]") != 0;
      //if (!_uniformIsActive[i]) {
      //  std::cout << "Uniform is inactive: " << _uniform[i]->getName() << std::endl;
      //}
    }

  }

  void ShaderProgram::bind() {
    glUseProgram(_program);
    for (int i = 0; i < _uniform.size(); i++)
      if (_uniformIsActive[i] && _uniform[i]->isBindable())
        _uniform[i]->bind();
  }

  ShaderProgram::~ShaderProgram()
  {
  }

  std::string ShaderProgram::toGLSL_vs(const std::string& shader) const {
    std::string result = "#version 460\n";
    for (int i = 0; i < _uniform.size(); i++)
      result += _uniform[i]->toGLSL();
    result += AttributetoGLSL();
    result += shader;
    return result;
  }

  std::string ShaderProgram::toGLSL_fs(const std::string& shader) const{
    std::string result = "#version 460\n";
    for (int i = 0; i < _uniform.size(); i++)
      result += _uniform[i]->toGLSL();
    result += shader;
    return result;
  }

  std::string ShaderProgram::AttributetoGLSL(size_t locationOffset) const {
    std::string result = "\n";
    for (int i = 0; i < _attributes.size(); i++) {
      result += "layout(location = ";
      result += std::to_string(i + locationOffset);
      result += ") in ";
      result += _attributes[i].getTypeAsString();
      result += " ";
      result += _attributes[i].getName();
      result += ";\n";
    }

    for (int i = 0; i < _attributeUniforms.size(); i++) {
      result += "layout(location = ";
      result += std::to_string(_attributeUniforms[i]->getLocation());
      result += ") in ";
      result += _attributeUniforms[i]->getType();
      result += " ";
      result += _attributeUniforms[i]->getName();
      result += ";\n";
    }

    return result;
  }

  std::string ShaderProgram::numberLines(const std::string& shader) const {
    std::string    result = "";
    size_t         lineNo = 0;
    std::istringstream iss(shader);

    for (std::string line; std::getline(iss, line); ) {
      lineNo++;
      std::string l = std::to_string(lineNo);
      l.insert(l.begin(), 3 - l.size(), ' ');

      result += l + " " + line + "\n";
    }
    return result;
  }
}