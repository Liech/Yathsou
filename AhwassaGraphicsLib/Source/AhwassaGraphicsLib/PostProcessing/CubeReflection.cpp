#include "CubeReflection.h"

#include <glm/gtc/matrix_transform.hpp>

#include "AhwassaGraphicsLib/BufferObjects/VAO.h"
#include "AhwassaGraphicsLib/Uniforms/Rendertarget.h"
#include "AhwassaGraphicsLib/Uniforms/CubeTexture.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AhwassaGraphicsLib/Uniforms/UniformFloat.h"
#include "AhwassaGraphicsLib/Uniforms/UniformVec3.h"
#include "AhwassaGraphicsLib/Uniforms/UniformMat4.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/ShaderProgram.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/Util.h"
#include "AhwassaGraphicsLib/BufferObjects/VAO.h"
#include "AhwassaGraphicsLib/Renderer/BasicTexture2DRenderer.h"

namespace Ahwassa {
  CubeReflection::CubeReflection(Ahwassa::Window* window, int width, int height) : PostProcessingEffect("CubeReflection", window, width, height) {

    std::string vertex_shader_source = R"(
    out vec2 TexCoords;

    void main()
    {
      gl_Position = projection * vec4(position.xy, 0.0, 1.0);
      TexCoords = texture;
    }  
   )";

    std::string fragment_shader_source = R"(
     in vec2 TexCoords;    
     out vec4 color;
    
    void main()
    {    
      vec3 FragPos     = texture(gPosition  , TexCoords).rgb;
      vec4  inp        = texture(Input, TexCoords);
      vec3 Normal      = (texture(gNormal    , TexCoords).rgb - vec3(0.5,0.5,0.5))*2;
      float reflection = texture(ReflectionMap, TexCoords)[int(ReflectionChannel)];
      vec3 reflectionColor = Normal;
      vec3 viewDir = normalize(FragPos-ViewPosition);
      reflectionColor = texture(ReflectionTexture,reflect(viewDir,normalize(Normal))).rgb;

      color = vec4(inp.rgb*(1-reflection) + reflectionColor*reflection, 1.0);
    }  
   )";

    std::vector<Ahwassa::Uniform*> uniforms = getUniforms();

    _input = std::make_shared<Ahwassa::Texture>("Input", 0);

    _viewPosition = std::make_shared<Ahwassa::UniformVec3>("ViewPosition");
    _reflectionChannel = std::make_shared<Ahwassa::UniformFloat>("ReflectionChannel");
    _reflectionIntensityMap = std::make_shared<Ahwassa::Texture>("ReflectionMap", 0);
    _normalMap = std::make_shared<Ahwassa::Texture>("gNormal", 0);
    _gPosition = std::make_shared<Ahwassa::Texture>("gPosition", 0);
    _reflectionTexture = std::make_shared<Ahwassa::CubeTexture>("ReflectionTexture", 0);
    uniforms.push_back(_reflectionIntensityMap.get());
    uniforms.push_back(_reflectionChannel.get());
    uniforms.push_back(_input.get());
    uniforms.push_back(_gPosition.get());
    uniforms.push_back(_viewPosition.get());
    uniforms.push_back(_reflectionTexture.get());
    uniforms.push_back(_normalMap.get());
    _shader = std::make_shared<Ahwassa::ShaderProgram>(Ahwassa::PositionTextureVertex::getBinding(), uniforms, vertex_shader_source, fragment_shader_source);
  }

  void CubeReflection::draw(glm::vec3 viewpos, std::shared_ptr<Ahwassa::Texture> input, std::shared_ptr<Ahwassa::Texture> reflectionMap, std::shared_ptr<Ahwassa::Texture> gPosition, std::shared_ptr<Ahwassa::Texture> normalMap, int channel) {
    if (!enabled())
      return;
    _viewPosition->setValue(viewpos);
    _reflectionIntensityMap->setTextureID(reflectionMap->getTextureID());
    _gPosition->setTextureID(gPosition->getTextureID());
    _reflectionChannel->setValue(channel);
    _normalMap->setTextureID(normalMap->getTextureID());
    _input->setTextureID(input->getTextureID());

    start();

    _shader->bind();

    end();
  }

  void CubeReflection::setTexture(std::shared_ptr<Ahwassa::CubeTexture> texture) {
    _reflectionTexture->setTextureID(texture->getTextureID());
  }
}