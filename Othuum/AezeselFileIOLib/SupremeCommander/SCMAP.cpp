#include "SCMAP.h"

#include "ImageIO.h"

namespace Aezesel {
  std::unique_ptr<SCMAP::Map> SCMAP::load(const std::string& filename) {
    std::ifstream input(filename, std::ios::binary);
    if (input.fail())
      throw std::runtime_error("Error opening " + filename);
    _buffer = std::vector<unsigned char>(std::istreambuf_iterator<char>(input), {});
    return readMap(_buffer, _fileposition);
  }

  std::unique_ptr<SCMAP::Map> SCMAP::readMap(const std::vector<unsigned char>&data, size_t&position) {
    std::string magic = readString(data, position, 4);
    if (!magic.starts_with("Map"))
      throw std::runtime_error("Wrong Format");
    auto result = std::make_unique<SCMAP::Map>();
    result->versionMajor = readInt(data, position);
    readInt(data, position);
    readInt(data, position);
    result->width  = readFloat(data, position);
    result->height = readFloat(data, position);
    readInt(data, position);
    readUShort(data, position);

    int lengthOfPreviewImage = readInt(data, position);
    {
      std::vector<unsigned char> rawPreview = read(data, position, lengthOfPreviewImage);
      result->previewImage = Aezesel::ImageIO::readImage(Aezesel::ImageIO::Format::DDS, rawPreview);
    }

    result->versionMinor     = readInt(data, position);
    result->resolutionWidth  = readInt(data, position);
    result->resolutionHeight = readInt(data, position);
    result->heightScale      = readFloat(data, position); //usually 1/128
    {
      int pixelAmount = ((result->resolutionHeight + 1) * (result->resolutionWidth + 1));
      std::vector<unsigned char> rawMap = read(data, position,pixelAmount*2+1);
      //HeightmapData = ReadArray(of Int16))
    }
    result->terrainShader =  readString(data, position); //setons: 2363572
    result->background    =  readString(data, position);
    result->skyCubemap    =  readString(data, position);
    int amountOfEnvMaps = readInt(data, position);
    for (int i = 0; i < amountOfEnvMaps; i++) {
      std::string faction = readString(data, position);
      std::string map = readString(data, position);
      result->envCubemaps[faction.substr(1,faction.length()-2)] = map;
    }

    result->lightingMultiplier = readFloat(data, position);
    result->sunDirection[0] = readFloat(data, position);
    result->sunDirection[1] = readFloat(data, position);
    result->sunDirection[2] = readFloat(data, position);

    result->sunAmbience[0] = readFloat(data, position);
    result->sunAmbience[1] = readFloat(data, position);
    result->sunAmbience[2] = readFloat(data, position);

    result->sunColor[0] = readFloat(data, position);
    result->sunColor[1] = readFloat(data, position);
    result->sunColor[2] = readFloat(data, position);

    result->shadowFillColor[0] = readFloat(data, position);
    result->shadowFillColor[1] = readFloat(data, position);
    result->shadowFillColor[2] = readFloat(data, position);

    result->specularColor[0] = readFloat(data, position);
    result->specularColor[1] = readFloat(data, position);
    result->specularColor[2] = readFloat(data, position);

    result->bloom       = readFloat(data, position);

    result->fogColor[0] = readFloat(data, position);
    result->fogColor[1] = readFloat(data, position);
    result->fogColor[2] = readFloat(data, position);
    result->fogStart    = readFloat(data, position);
    result->fogEnd      = readFloat(data, position);

    result->hasWater = data[position] != 0;
    position += 1;
    result->waterElevation = readFloat(data, position);
    result->elevationDeep  = readFloat(data, position);
    result->elevationAbyss = readFloat(data, position);

    result->waterShaderProperties = readWaterShaderProperties(data, position);

    int numberOfWaveGenerators = readInt(data, position);
    for (int i = 0; i < numberOfWaveGenerators; i++)
      result->waveGenerators.push_back(readWaveGenerator(data, position));

    return std::move(result);
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

    result.surfaceColor[0]  = readFloat(data,position);
    result.surfaceColor[1]  = readFloat(data,position);
    result.surfaceColor[2]  = readFloat(data,position);
    result.colorLerp   [0]  = readFloat(data,position);
    result.colorLerp   [1]  = readFloat(data,position);
    result.refractionScale  = readFloat(data,position);
    result.fresnelBias      = readFloat(data,position);
    result.fresnelPower     = readFloat(data,position);
    result.unitReflection   = readFloat(data,position);
    result.skyReflection    = readFloat(data,position);
    result.sunShininess     = readFloat(data,position);
    result.sunStrength      = readFloat(data,position);
    result.sunDirection[0]  = readFloat(data,position);
    result.sunDirection[1]  = readFloat(data,position);
    result.sunDirection[2]  = readFloat(data,position);
    result.sunColor    [0]  = readFloat(data,position);
    result.sunColor    [1]  = readFloat(data,position);
    result.sunColor    [2]  = readFloat(data,position);
    result.sunReflection    = readFloat(data,position);
    result.sunGlow          = readFloat(data,position);
    result.waterCubemapPath = readString(data, position);
    result.waterRamp        = readString(data, position);
    for (int i = 0; i < 4; i++)
      result.waves[i].normalRepeat = readFloat(data, position);
    for (int i = 0; i < 4; i++)
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