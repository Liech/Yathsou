#include "UniformVecTexture.h"

#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "glad/glad.h"

namespace Ahwassa {

  UniformVecTexture::UniformVecTexture(std::string name, std::vector<std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>>& value) : Uniform(name) {
    _width = value[0]->getDimension(0);
    _height = value[0]->getDimension(1);
    _size = value.size();

    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D_ARRAY, _id);
    glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, _width, _height, value.size());

    std::vector<Iyathuum::Color> allData(value[0]->vector().begin(),value[0]->vector().end());

    for(int i = 1;i < value.size();i++)
      allData.insert(allData.end(), value[i]->vector().begin(), value[i]->vector().end());

    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, allData.data());

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  };

  UniformVecTexture::~UniformVecTexture() {
    glDeleteTextures(1, &_id);
  }

  void UniformVecTexture::bind() {
    int loc = getTextureLocation();
    //glActiveTexture(GL_TEXTURE0 + loc);
    //glBindTexture(GL_TEXTURE_2D, _id);
    glUniform1i(getLocation(), loc);
  }


  std::string UniformVecTexture::getArrayPostfix() {
    return "";
  }
}