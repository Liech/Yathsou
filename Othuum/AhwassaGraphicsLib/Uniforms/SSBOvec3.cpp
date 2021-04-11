#include "SSBOvec3.h"

#include "glad/glad.h"

namespace Ahwassa {
    //https://www.geeks3d.com/20140704/tutorial-introduction-to-opengl-4-3-shader-storage-buffers-objects-ssbo-demo/
    SSBOvec3::SSBOvec3(std::string name, std::vector<glm::vec3> content) : Uniform(name) {
      glGenBuffers(1, &_ssbo);
      glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
      glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(glm::vec3) * content.size(), content.data(), GL_DYNAMIC_COPY);
      glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    }

    void SSBOvec3::setData(std::vector<glm::vec3> content) {
      glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
      GLvoid* p = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
      memcpy(p, content.data(), sizeof(glm::vec3));
      glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    }


    SSBOvec3::~SSBOvec3() {

    }

    void SSBOvec3::bind()
    {
      glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
      glBindBufferBase(GL_SHADER_STORAGE_BUFFER, getLocation(), _ssbo);
    }

    std::string SSBOvec3::toGLSL() {
      std::string result = "";
      result += "layout (std430, binding=" + std::to_string(getLocation()) + ") buffer type" + getName() + "\n";
      result += "{\n";
      result += getType() + " " + getName() + "[];\n";
      result += "};\n";

      return result;
    }
}