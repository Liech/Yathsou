#include "Bloom.h"

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
  Bloom::Bloom(Ahwassa::Window* window, int width, int height) : PostProcessingEffect("Bloom",window,width,height) {

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

      vec2 tex_offset = 1.0 / textureSize(Input, 0); // gets size of single texel
      float Pi = 3.1415926;
      vec3 result = vec3(0,0,0); // current fragment's contribution
      //https://www.shadertoy.com/view/Xltfzj
      float Directions = 16.0;
      float Quality = 3.0;
      float Size = 8.0;
      vec2 Radius = Size/textureSize(Input, 0);
      float intensity = Intensity;
      for( float d=0.0; d<Pi; d+=Pi/Directions)
      {
		    for(float i=1.0/Quality; i<=1.0; i+=1.0/Quality)
        {
          vec2  sampleLocation = TexCoords+vec2(cos(d),sin(d))*Radius*i;
          float bloomValue = texture( BloomMap, sampleLocation)[int(BloomChannel)];
		  	  result += texture(Input, sampleLocation).rgb*bloomValue*intensity;		
        }
      }  
      result /= Quality * Directions - 15.0;
      result+= texture(Input, TexCoords).rgb;
      color = vec4(result, 1.0);
    }  
   )";

    std::vector<Ahwassa::Uniform*> uniforms = getUniforms();    

    _bloomMap         = std::make_shared<Ahwassa::Texture     >("BloomMap", 0);
    _input            = std::make_shared<Ahwassa::Texture     >("Input"   , 0);
    _bloomChannel     = std::make_shared<Ahwassa::UniformFloat>("BloomChannel");
    _intensityUniform = std::make_shared<Ahwassa::UniformFloat>("Intensity");

    uniforms.push_back(_bloomMap        .get());
    uniforms.push_back(_input           .get());
    uniforms.push_back(_bloomChannel    .get());
    uniforms.push_back(_intensityUniform.get());
    _shader = std::make_shared<Ahwassa::ShaderProgram>(Ahwassa::PositionTextureVertex::getBinding(), uniforms, vertex_shader_source, fragment_shader_source);
  }

  void Bloom::draw(std::shared_ptr<Ahwassa::Texture> input, std::shared_ptr<Ahwassa::Texture> bloomMap, int channel) {
    _intensityUniform->setValue(_intensity);
    _bloomChannel    ->setValue(channel);
    _bloomMap        ->setTextureID(bloomMap->getTextureID());
    _input           ->setTextureID(input->getTextureID());

    start();

    _shader->bind();

    end();
  }

  void Bloom::setIntensity(float value) {
    _intensity = value;
  }

  float Bloom::intensity() {
    return _intensity;
  }

}