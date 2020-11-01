#include "ShaderProgram.h"
#include <set>
#include <iostream>
namespace YolonaOss {
  namespace GL{
  ShaderProgram::ShaderProgram(const std::vector<AttributeDescription>& attributes, std::vector<Uniform*> uniforms, std::string vsmain, std::string fsmain)
  {
    _attributes = attributes;
    _vertexShader = vsmain;
    _fragmentShader = fsmain;
    _uniform = uniforms;

    _uniformIsActive.resize(_uniform.size());
    size_t ssboLocations = 0;
    size_t uniformLocations = 0;
    for (int i = 0; i < _uniform.size(); i++) {
      if (_uniform[i]->isBuffer()) {
        _uniform[i]->setLocation((int)ssboLocations);
        ssboLocations++;
      }
      else {
        _uniform[i]->setLocation((int)uniformLocations);
        uniformLocations++;
      }
      _uniformIsActive[i] = false;
    }

    std::string vssrc = toGLSL_vs();
    std::string fssrc = toGLSL_fs();

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


    std::cout << std::endl << "SHADER VS" << std::endl << m2 << std::endl;
    std::cout << std::endl << "SHADER FS" << std::endl << m << std::endl;

    const char* vs_src = vssrc.c_str();
    const char* fs_src = fssrc.c_str();

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_src, nullptr);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_src, nullptr);
    glCompileShader(fs);

    _program = glCreateProgram();
    glAttachShader(_program, vs);
    glAttachShader(_program, fs);
    glLinkProgram(_program);
    glDeleteShader(vs);
    glDeleteShader(fs);

    checkUsageOfUniforms();
  }


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
      if (_uniform[i]->isBuffer()) continue;
      glGetActiveUniform(_program, (GLuint)_uniform[i]->getLocation(), bufSize, &length, &size, &type, name);
      activeNames.insert(name);
    }
    for (int i = 0; i < _uniform.size(); i++) {
      if (_uniform[i]->isBuffer()) continue;
      _uniformIsActive[i] = activeNames.count(_uniform[i]->getName()) != 0;
      if (!_uniformIsActive[i]) {
        std::cout << "Uniform is inactive: " << _uniform[i]->getName() << std::endl;
      }
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

  std::string ShaderProgram::toGLSL_vs() {
    std::string result = "#version 460\n";
    for (int i = 0; i < _uniform.size(); i++)
      result += _uniform[i]->toGLSL();
    result += AttributetoGLSL();
    result += _vertexShader;
    return result;
  }

  std::string ShaderProgram::toGLSL_fs() {
    std::string result = "#version 460\n";
    for (int i = 0; i < _uniform.size(); i++)
      result += _uniform[i]->toGLSL();
    result += _fragmentShader;
    return result;
  }

  std::string ShaderProgram::AttributetoGLSL(size_t locationOffset) {
    std::string result = "\n";
    size_t currentOffset = 0;
    for (int i = 0; i < _attributes.size(); i++) {
      result += "layout(location = ";
      result += std::to_string(i + locationOffset);
      result += ") in ";
      result += _attributes[i].getTypeAsString();
      result += " ";
      result += _attributes[i].name;
      result += ";\n";
    }
    return result;
  }
}}