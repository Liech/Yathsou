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

  std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> SCMAP::loadPreview(const std::string& filename) {
    std::ifstream input(filename, std::ios::binary);
    if (input.fail())
      throw std::runtime_error("Error opening " + filename);
    std::vector<unsigned char> data;
    data.resize(34);
    input.read((char*)data.data(), 34);
    size_t position = 0;

    auto header = readMapHeader(data, position);

    int lengthOfPreviewImage = readInt(data, position);
    data.resize(34 + lengthOfPreviewImage);
    input.read((char*)(data.data()+34), lengthOfPreviewImage);

    std::vector<unsigned char> rawPreview = read(data, position, lengthOfPreviewImage);
    return Aezesel::ImageIO::readImage(Aezesel::ImageIO::Format::DDS, rawPreview);
  }

  std::unique_ptr<SCMAP::Map> SCMAP::readMap(const std::vector<unsigned char>&data, size_t&position) {
    auto result = std::make_unique<SCMAP::Map>();
    result->header = readMapHeader(data, position);

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

    if (result->versionMinor > 56)
      readFloat(data, position);

    result->cartographicContourInterval   = readInt(data,position);
    result->cartographicDeepWaterColor    = readInt(data,position);
    result->cartographicMapContourColor   = readInt(data,position);
    result->cartographicMapShoreColor     = readInt(data,position);
    result->cartographicMapLandStartColor = readInt(data,position);
    result->cartographicMapLandEndColor   = readInt(data,position);

    for (int i = 0; i < 10; i++) {
      ScaledTexture sub;
      sub.path = readString(data, position);
      sub.scale = readFloat(data, position);
      result->terrainTexturePaths.push_back(sub);
    }
    for (int i = 0; i < 9; i++) {
      ScaledTexture sub;
      sub.path = readString(data, position);
      sub.scale = readFloat(data, position);
      result->terrainNormalPaths.push_back(sub);
    }

    readInt(data, position);
    readInt(data, position);

    int decalCount = readInt(data, position);
    result->decals.resize(decalCount);
    for (int i = 0; i < decalCount; i++)
      result->decals[i] = readDecal(data,position);

    return std::move(result);
  }

  SCMAP::Decal SCMAP::readDecal(const std::vector<unsigned char>& data, size_t& position) {

  }

  SCMAP::MapHeader SCMAP::readMapHeader(const std::vector<unsigned char>& data, size_t&position) {
    std::string magic = readString(data, position, 4);
    if (!magic.starts_with("Map"))
      throw std::runtime_error("Wrong Format");
    SCMAP::MapHeader result;
    result.versionMajor = readInt(data, position);
    readInt(data, position);
    readInt(data, position);
    result.width = readFloat(data, position);
    result.height = readFloat(data, position);
    readInt(data, position);
    readUShort(data, position);
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