#include "SCMAP.h"


namespace Aezesel {
  SCMAP::SCMAP(const std::string& map) {
  }

  SCMAP::Map SCMAP::readMap(const std::vector<unsigned char>&data, size_t&position) {
    std::string magic = readString(data, position, 3);
    if (magic != "map")
      throw std::runtime_error("Wrong map");
    SCMAP::Map result;
    result.versionMajor = readInt(data, position);
    readInt(data, position);
    readInt(data, position);
    result.width  = readFloat(data, position);
    result.height = readFloat(data, position);
    readInt(data, position);
    readUShort(data, position);

    int lengthOfPreviewImage = readInt(data, position);
    for(int i =0 ;i < lengthOfPreviewImage;i++)
      result.mapData.push_back(readUShort(data, position));

    return result;
  }

  SCMAP::Prop SCMAP::readProp(const std::vector<unsigned char>&data, size_t&position) {
    SCMAP::Prop result;
    result.blueprintPath = readString(data, position);
    result.position[0] = readFloat(data, position);
    result.position[1] = readFloat(data, position);
    result.position[2] = readFloat(data, position);

    glm::vec3 m1;
    glm::vec3 m2;
    glm::vec3 m3;

    m1[0] = readFloat(data, position);
    m1[1] = readFloat(data, position);
    m1[2] = readFloat(data, position);

    m2[0] = readFloat(data, position);
    m2[1] = readFloat(data, position);
    m2[2] = readFloat(data, position);

    m3[0] = readFloat(data, position);
    m3[1] = readFloat(data, position);
    m3[2] = readFloat(data, position);

    result.rotation = glm::mat3(m1, m2, m3);

    return result;
  }

  SCMAP::DecalGroup SCMAP::readDecalGroup(const std::vector<unsigned char>&data, size_t&position) {
    SCMAP::DecalGroup result;
    result.id   = readInt   (data, position);
    result.name = readString(data, position);
    int len = readInt(data, position);
    for (int i = 0; i < len; i++)
      result.data.push_back(readInt(data, position));
    return result;
  }

  SCMAP::Decal SCMAP::readDecal(const std::vector<unsigned char>&data, size_t&position) {
    SCMAP::Decal result;
    result.id   = readInt(data, position);
    result.type = readInt(data, position);
    int textureCount = readInt(data, position);
    for (int i = 0; i < textureCount; i++) {
      int stringLen = readInt(data, position);
      result.TexturePaths.push_back(readString(data, position, stringLen));
    }

    result.scale[0]      = readFloat(data, position);
    result.scale[1]      = readFloat(data, position);
    result.scale[2]      = readFloat(data, position);
                         
    result.position[0]   = readFloat(data, position);
    result.position[1]   = readFloat(data, position);
    result.position[2]   = readFloat(data, position);
                         
    result.rotation[0]   = readFloat(data, position);
    result.rotation[1]   = readFloat(data, position);
    result.rotation[2]   = readFloat(data, position);

    result.cutOffLOD     = readFloat(data, position);
    result.nearCutOffLOD = readFloat(data, position);
    result.ownerArmy     = readFloat(data, position);

    return result;
  }

  SCMAP::Layer SCMAP::readLayer(const std::vector<unsigned char>&data, size_t&position) {
    SCMAP::Layer result;
    result.pathTexture    = readString(data, position);
    result.pathNormalmap  = readString(data, position);
    result.scaleTexture   = readFloat (data, position);
    result.scaleNormalMap = readFloat (data, position);    
    return result;
  }

  SCMAP::WaveGenerator SCMAP::readWaveGenerator(const std::vector<unsigned char>& data, size_t& position) {
    SCMAP::WaveGenerator result;
    result.textureName = readString(data, position);
    result.rampName    = readString(data, position);
    
    result.position[0] = readFloat (data, position);
    result.position[1] = readFloat (data, position);
    result.position[2] = readFloat (data, position);
    result.rotation    = readFloat (data, position);
    result.velocity[0] = readFloat (data, position);
    result.velocity[1] = readFloat (data, position);
    result.velocity[2] = readFloat (data, position);

    result.lifetimeFirst  = readFloat(data, position);
    result.lifetimeSecond = readFloat(data, position);
    result.periodFirst    = readFloat(data, position);
    result.periodSecond   = readFloat(data, position);
    result.scaleFirst     = readFloat(data, position);
    result.scaleSecond    = readFloat(data, position);

    result.frameCount      = readFloat(data, position);
    result.frameRateFirst  = readFloat(data, position);
    result.frameRateSecond = readFloat(data, position);
    result.stripCount      = readFloat(data, position);

    return result;
  }

  SCMAP::WaterShaderProperties SCMAP::readWaterShaderProperties(const std::vector<unsigned char>& data, size_t& position) {
    SCMAP::WaterShaderProperties result;
    for (int i = 0; i < 20; i++)
      readFloat(data, position); //unkown
    result.WaterCubemapPath = readString(data, position);
    result.WaterRamp        = readString(data, position);
    for (int i = 0; i < 3; i++)
      result.waves[i] = readWaveTexture(data, position);
    return result;
  }

  SCMAP::WaveTexture SCMAP::readWaveTexture(const std::vector<unsigned char>& data, size_t& position) {
    SCMAP::WaveTexture result;
    result.scaleX      = readFloat(data, position);
    result.scaleY      = readFloat(data, position);
    result.texturePath = readString(data, position);
    return result;
  }

}