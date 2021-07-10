#pragma once

#include <string>
#include <array>
#include <memory>
#include <map>

#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "AezeselFileIOLib/IO.h"

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
      std::array<WaveTexture, 4> waves           ;
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
    enum class DecalType {
      Albedo = 1,
      Normals = 2,
      WaterMask = 3,
      WaterAlbedo = 4,
      WaterNormals = 5,
      Glow = 6,
      AlphaNormals = 7,
      GlowMask = 8
    };
    struct Decal {
      int                      id           ;       
      DecalType                type         ;
      std::vector<std::string> texturePaths ;
      glm::vec3                scale        ;
      glm::vec3                position     ;
      glm::vec3                rotation     ;
      float                    cutOffLOD    ;      
      float                    nearCutOffLOD;
      int                      ownerArmy    ;
    };
    struct DecalGroup {
      int              id    ;
      std::string      name  ;
      std::vector<int> member;
    };
    struct MapHeader {
      int                        versionMajor;
      float                      width;
      float                      height;
      std::vector<unsigned char> previewImageData;
    };
    struct Planet {
      glm::vec3 position;
      float     rotation;
      glm::vec2 scale   ;
      glm::vec4 uv      ;
    };
    struct Cirrus {
      glm::vec2 frequency;
      float     speed    ;
      glm::vec2 direction;
    };
    struct SkyBox {
      glm::vec3 position           ;
      float     horizonHeight      ;
      float     scale              ;
      float     subHeight          ;
      int       subDivAx           ;
      int       subDivHeight       ;
      float     zenithHeight       ;
      glm::vec3 horizonColor       ;
      glm::vec3 zenithColor        ;
      float     decalGlowMultiplier;

      std::string         albedo ;
      std::string         glow   ;
      std::vector<Planet> planets;

      Iyathuum::Color     midRgbColor;

      float               cirrusMultiplier;
      glm::vec3           cirrusColor     ;
      std::string         cirrusTexture   ;

      std::vector<Cirrus> cirrusLayer     ;
      float               sevenClouds     ;
    };
    struct Prop {
      std::string path;
      glm::vec3 position;
      glm::vec3 rotationX;
      glm::vec3 rotationY;
      glm::vec3 rotationZ;
      glm::vec3 scale;
    };
    struct Map {
      MapHeader header;

      std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> previewImage;

      int                        versionMinor;
      int                        heightMapWidth;
      int                        heightMapHeight;
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
      std::vector<DecalGroup>    decalGroups;

      int mapWidth;
      int mapHeight;

      std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> normalMap      ;
      std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> lowTexture     ;
      std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> highTexture    ;
      std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> waterMapTexture;


      std::unique_ptr<Iyathuum::MultiDimensionalArray<unsigned short, 2>> heightMapData    ;
      std::unique_ptr<Iyathuum::MultiDimensionalArray<unsigned char , 2>> waterFoamMaskData;
      std::unique_ptr<Iyathuum::MultiDimensionalArray<unsigned char , 2>> flatnessData     ;
      std::unique_ptr<Iyathuum::MultiDimensionalArray<unsigned char , 2>> depthBiasMaskData;
      std::unique_ptr<Iyathuum::MultiDimensionalArray<unsigned char , 2>> terrainTypeData  ;

      SkyBox            skybox;
      std::vector<Prop> props ;
    };

    std::unique_ptr<SCMAP::Map> load(const std::string& filename);
    std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> loadPreview(const std::string& filename);
  private:
    std::unique_ptr<SCMAP::Map> readMap                  (const std::vector<unsigned char>&, size_t&);
    Prop                        readProp                 (const std::vector<unsigned char>&, size_t&);
    SkyBox                      readSkyBox               (const std::vector<unsigned char>&, size_t&);
    DecalGroup                  readDecalGroup           (const std::vector<unsigned char>&, size_t&);
    Decal                       readDecal                (const std::vector<unsigned char>&, size_t&);
    MapHeader                   readMapHeader            (const std::vector<unsigned char>&, size_t&);
    WaveGenerator               readWaveGenerator        (const std::vector<unsigned char>&, size_t&);
    WaterShaderProperties       readWaterShaderProperties(const std::vector<unsigned char>&, size_t&);
    WaveTexture                 readWaveTexture          (const std::vector<unsigned char>&, size_t&);

    size_t                     _fileposition = 0;
    std::vector<unsigned char> _buffer;

  };
}