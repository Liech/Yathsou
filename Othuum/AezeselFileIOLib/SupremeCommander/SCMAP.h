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
    struct ScaledTexture {
      std::string path ;
      float       scale;
    };
    struct Decal {
      int id;

    };

    struct MapHeader {
      int                        versionMajor;
      float                      width;
      float                      height;
      std::vector<unsigned char> previewImageData;
    };
    struct Map {
      MapHeader header;

      std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> previewImage;

      int                        versionMinor;
      int                        resolutionWidth;
      int                        resolutionHeight;
      float                      heightScale;

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

      int cartographicContourInterval  ;
      int cartographicDeepWaterColor   ;
      int cartographicMapContourColor  ;
      int cartographicMapShoreColor    ;
      int cartographicMapLandStartColor;
      int cartographicMapLandEndColor  ;

      std::vector<ScaledTexture> terrainTexturePaths;
      std::vector<ScaledTexture> terrainNormalPaths;
      std::vector<Decal>         decals;
    };

    std::unique_ptr<SCMAP::Map> load(const std::string& filename);
    std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> loadPreview(const std::string& filename);
  private:
    std::unique_ptr<SCMAP::Map> readMap            (const std::vector<unsigned char>&, size_t&);
    Decal                 readDecal                (const std::vector<unsigned char>&, size_t&);
    MapHeader             readMapHeader            (const std::vector<unsigned char>&, size_t&);
    WaveGenerator         readWaveGenerator        (const std::vector<unsigned char>&, size_t&);
    WaterShaderProperties readWaterShaderProperties(const std::vector<unsigned char>&, size_t&);
    WaveTexture           readWaveTexture          (const std::vector<unsigned char>&, size_t&);

    size_t                     _fileposition = 0;
    std::vector<unsigned char> _buffer;

  };
}