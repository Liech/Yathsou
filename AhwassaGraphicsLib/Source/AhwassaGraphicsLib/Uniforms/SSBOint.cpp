#include "SSBOint.h"

#include "glad/glad.h"

namespace Ahwassa {
    //https://www.geeks3d.com/20140704/tutorial-introduction-to-opengl-4-3-shader-storage-buffers-objects-ssbo-demo/
    SSBOuint::SSBOuint(const std::string& name, const std::vector<unsigned int>& content) : Uniform(name) {
      glGenBuffers(1, &_ssbo);
      glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
      glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(unsigned int) * content.size(), content.data(), GL_DYNAMIC_COPY);
      glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }

    void SSBOuint::setData(const std::vector<unsigned int>& content) {
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

    std::string SSBOuint::toGLSL() const {
      std::string result = "";
      result += "layout (std430, binding=" + std::to_string(getLocation()) + ") buffer type" + getName() + "\n";
      result += "{\n";
      result += "uint " + getName() + "[];\n";
      result += "};\n";

      return result;
    }
}