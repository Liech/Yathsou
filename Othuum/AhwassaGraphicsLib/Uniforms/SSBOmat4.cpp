#include "SSBOmat4.h"

#include "glad/glad.h"

namespace Ahwassa {
    //https://www.geeks3d.com/20140704/tutorial-introduction-to-opengl-4-3-shader-storage-buffers-objects-ssbo-demo/
    SSBOmat4::SSBOmat4(std::string name, std::vector<glm::mat4> content) : Uniform(name) {
      glGenBuffers(1, &_ssbo);
      glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
      glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(glm::mat4) * content.size(), content.data(), GL_DYNAMIC_COPY);
      glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }

    SSBOmat4::SSBOmat4(std::string name, size_t amount) : Uniform(name) {
      glGenBuffers(1, &_ssbo);
      std::vector<glm::mat4> content;
      content.resize(amount);
      glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
      glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(glm::mat4) * content.size(), content.data(), GL_DYNAMIC_COPY);
      glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }

    void SSBOmat4::setData(std::vector<glm::mat4> content) {
      glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
      GLvoid* p = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
      memcpy(p, content.data(), sizeof(glm::mat4)*content.size());
      glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    }

    SSBOmat4::~SSBOmat4() {

    }

    void SSBOmat4::bind()
    {
      glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
      glBindBufferBase(GL_SHADER_STORAGE_BUFFER, getLocation(), _ssbo);
    }

    std::string SSBOmat4::toGLSL() {
      std::string result = "";
      result += "layout (std430, binding=" + std::to_string(getLocation()) + ") buffer type" + getName() + "\n";
      result += "{\n";
      result += getType() + " " + getName() + "[];\n";
      result += "};\n";

      return result;
    }
}