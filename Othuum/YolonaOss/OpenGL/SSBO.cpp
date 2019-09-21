#include "SSBO.h"
namespace YolonaOss {
  namespace GL {
    //https://www.geeks3d.com/20140704/tutorial-introduction-to-opengl-4-3-shader-storage-buffers-objects-ssbo-demo/
    SSBOvec4::SSBOvec4(std::string name, std::vector<glm::vec4> content) : Uniform(name) {
      glGenBuffers(1, &_ssbo);
      glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
      glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(glm::vec4) * content.size(), content.data(), GL_DYNAMIC_COPY);
      glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    }

    void SSBOvec4::setData(std::vector<glm::vec4> content) {
      glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
      GLvoid* p = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
      memcpy(p, content.data(), sizeof(glm::vec4));
      glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    }


    SSBOvec4::~SSBOvec4() {

    }

    void SSBOvec4::bind()
    {
      glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
      glBindBufferBase(GL_SHADER_STORAGE_BUFFER, getLocation(), _ssbo);
    }

    std::string SSBOvec4::toGLSL() {
      std::string result = "";
      result += "layout (std430, binding=" + std::to_string(getLocation()) + ") buffer type" + getName() + "\n";
      result += "{\n";
      result += "vec4 " + getName() + "[];\n";
      result += "};\n";

      return result;
    }

    SSBOuint::SSBOuint(std::string name, std::vector<unsigned int> content) : Uniform(name) {
      glGenBuffers(1, &_ssbo);
      glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
      glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(unsigned int) * content.size(), content.data(), GL_DYNAMIC_COPY);
      glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    }

    void SSBOuint::setData(std::vector<unsigned int> content) {
      glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
      GLvoid* p = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
      memcpy(p, content.data(), sizeof(unsigned int));
      glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    }


    SSBOuint::~SSBOuint() {

    }

    void SSBOuint::bind()
    {
      glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
      glBindBufferBase(GL_SHADER_STORAGE_BUFFER, getLocation(), _ssbo);
    }

    std::string SSBOuint::toGLSL() {
      std::string result = "";
      result += "layout (std430, binding=" + std::to_string(getLocation()) + ") buffer type" + getName() + "\n";
      result += "{\n";
      result += "uint " + getName() + "[];\n";
      result += "};\n";

      return result;
    }
  }
}