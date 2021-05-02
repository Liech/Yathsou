#pragma once

#include <string>
#include <array>

#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "IO.h"

//map format according to:
//https://www.gamereplays.org/community/index.php?showtopic=176526

namespace Aezesel {
  class SCMAP : public IO {
  public:
    struct WaveTexture {
      float       scaleX     ;
      float       scaleY     ;
      std::string texturePath;
    };
    struct WaterShaderProperties {
      std::string                WaterCubemapPath;
      std::string                WaterRamp       ;
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
      std::vector<unsigned short>mapData;//((Height + 1) * (Width + 1))
      
      std::string                terrainShader;
      std::string                background;
      std::string                skyCubemap;
      std::string                envCubemap;
      
      float                      lightingMultiplier;
      glm::vec3                  sunDirection;
      glm::vec3                  sunAmbience;
      glm::vec3                  sunColor;
      glm::vec3                  specularColor;
      float                      bloom;

      glm::vec3                  fogColor;
      float                      fogStart;
      float                      fogEnd;
      
      bool                       hasWater;
      float                      waterElevation;
      float                      elevationDeep;
      float                      elevationAbyss;

      WaterShaderProperties      waterShaderProperties;
    };

    SCMAP(const std::string& map);
  private:
    Map                   readMap                  (const std::vector<unsigned char>&, size_t&);
    Prop                  readProp                 (const std::vector<unsigned char>&, size_t&);
    DecalGroup            readDecalGroup           (const std::vector<unsigned char>&, size_t&);
    Decal                 readDecal                (const std::vector<unsigned char>&, size_t&);
    Layer                 readLayer                (const std::vector<unsigned char>&, size_t&);
    WaveGenerator         readWaveGenerator        (const std::vector<unsigned char>&, size_t&);
    WaterShaderProperties readWaterShaderProperties(const std::vector<unsigned char>&, size_t&);
    WaveTexture           readWaveTexture          (const std::vector<unsigned char>&, size_t&);
  };
}