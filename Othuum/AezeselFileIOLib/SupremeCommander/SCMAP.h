#pragma once

#include <string>
#include <array>
#include <memory>
#include <map>

#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "IO.h"

#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"

//map format according to:
//https://www.gamereplays.org/community/index.php?showtopic=176526 -> is for vanilla, not fa
//https://github.com/FAForever/Neroxis-Map-Generator/blob/develop/src/main/java/com/faforever/neroxis/map/exporter/SCMapExporter.java

namespace Aezesel {
  class SCMAP : public IO {
  public:
    struct WaveTexture {
      float       scaleX     ;
      float       scaleY     ;
      std::string texturePath;
      float       normalRepeat;
    };
    struct WaterShaderProperties {
      glm::vec3                  surfaceColor    ;
      glm::vec2                  colorLerp       ;
      float                      refractionScale ;
      float                      fresnelBias     ;
      float                      fresnelPower    ;
      float                      unitReflection  ;
      float                      skyReflection   ;
      float                      sunShininess    ;
      float                      sunStrength     ;
      glm::vec3                  sunDirection    ;
      glm::vec3                  sunColor        ;
      float                      sunReflection   ;
      float                      sunGlow         ;
      std::string                waterCubemapPath;
      std::string                waterRamp       ;
      std::array<WaveTexture, 3> waves           ;
    };
    struct WaveGenerator {
      std::string textureName    ;
      std::string rampName       ;
      glm::vec3   position       ;
      float       rotation       ;
      glm::vec3   velocity       ;
      
      float       lifetimeFirst  ;
      float       lifetimeSecond ;
      float       periodFirst    ;
      float       periodSecond   ;
      float       scaleFirst     ;
      float       scaleSecond    ;

      float       frameCount     ;
      float       frameRateFirst ;
      float       frameRateSecond;
      float       stripCount     ;
    };
    struct Layer {
      std::string pathTexture   ;
      std::string pathNormalmap ;
      float       scaleTexture  ;
      float       scaleNormalMap;
    };
    struct Decal {
      int                      id           ;
      int                      type         ;
      std::vector<std::string> TexturePaths ;
      glm::vec3                scale        ;
      glm::vec3                position     ;
      glm::vec3                rotation     ;
      float                    cutOffLOD    ;
      float                    nearCutOffLOD;
      float                    ownerArmy    ;
    };
    struct DecalGroup {
      int id;
      std::string name;
      std::vector<int> data;
    };
    struct Prop {
      std::string blueprintPath;
      glm::vec3   position     ; 
      glm::mat3   rotation     ;
    };
    struct Map {
      int                        versionMajor;
      float                      width ;
      float                      height;
      std::vector<unsigned char> previewImageData;
      int                        versionMinor;
      int                        resolutionWidth;
      int                        resolutionHeight;
      float                      heightScale;

      std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> previewImage;
      
      std::string                       terrainShader;
      std::string                       background;
      std::string                       skyCubemap;
      std::map<std::string,std::string> envCubemaps; //faction->map (default->map)
      
      float                      lightingMultiplier;
      glm::vec3                  sunDirection      ;
      glm::vec3                  sunAmbience       ;
      glm::vec3                  sunColor          ;
      glm::vec3                  shadowFillColor   ;
      glm::vec3                  specularColor     ;
      float                      bloom             ;

      glm::vec3                  fogColor;
      float                      fogStart;
      float                      fogEnd  ;
      
      bool                       hasWater      ;
      float                      waterElevation;
      float                      elevationDeep ;
      float                      elevationAbyss;

      WaterShaderProperties      waterShaderProperties;
      std::vector<WaveGenerator> waveGenerators;
    };

    std::unique_ptr<SCMAP::Map> load(const std::string& filename);
  private:
    std::unique_ptr<SCMAP::Map> readMap            (const std::vector<unsigned char>&, size_t&);
    Prop                  readProp                 (const std::vector<unsigned char>&, size_t&);
    DecalGroup            readDecalGroup           (const std::vector<unsigned char>&, size_t&);
    Decal                 readDecal                (const std::vector<unsigned char>&, size_t&);
    Layer                 readLayer                (const std::vector<unsigned char>&, size_t&);
    WaveGenerator         readWaveGenerator        (const std::vector<unsigned char>&, size_t&);
    WaterShaderProperties readWaterShaderProperties(const std::vector<unsigned char>&, size_t&);
    WaveTexture           readWaveTexture          (const std::vector<unsigned char>&, size_t&);

    size_t                     _fileposition = 0;
    std::vector<unsigned char> _buffer;

  };
}