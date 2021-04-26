#include "SSR.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>

#include "AhwassaGraphicsLib/BufferObjects/VAO.h"
#include "AhwassaGraphicsLib/Uniforms/Rendertarget.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AhwassaGraphicsLib/Uniforms/UniformFloat.h"
#include "AhwassaGraphicsLib/Uniforms/UniformMat4.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/ShaderProgram.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/Util.h"
#include "AhwassaGraphicsLib/BufferObjects/VAO.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTexture2DRenderer.h"

namespace Ahwassa {
  SSR::SSR(Ahwassa::Window* window, int width, int height) : PostProcessingEffect("SSR", window, width, height) {

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
      vec4  inp = texture(Input, TexCoords);


      color = vec4(1,1,0, 1.0);
    }  
   )";

    std::vector<Ahwassa::Uniform*> uniforms = getUniforms();

    _input = std::make_shared<Ahwassa::Texture>("Input", 0);


    _reflectionMap = std::make_shared<Ahwassa::Texture>("ReflectionMap", 0);
    uniforms.push_back(_reflectionMap.get());
    uniforms.push_back(_input.get());
    _shader = std::make_shared<Ahwassa::ShaderProgram>(Ahwassa::PositionTextureVertex::getBinding(), uniforms, vertex_shader_source, fragment_shader_source);
  }

  void SSR::draw(std::shared_ptr<Ahwassa::Texture> input, std::shared_ptr<Ahwassa::Texture> SSRMap, int channel) {
    if (!enabled())
      return;
    _reflectionMap->setTextureID(SSRMap->getTextureID());
    _input->setTextureID(input->getTextureID());

    start();

    _shader->bind();

    end();
  }

}