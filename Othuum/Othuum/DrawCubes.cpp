#include "DrawCubes.h"


#include "glad/glad.h"
#include "glm/ext/matrix_transform.hpp"

using namespace YolonaOss::GL;

void DrawCubes::load(GL::DrawSpecification *d)
{
  _camera = d->getCam();
  _spec = d;
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  std::vector<GL::PositionColorNormalVertex> input;

  
  //front
  input.push_back(GL::PositionColorNormalVertex(glm::vec3(-0.5,-0.5, 0.5),glm::vec4(0, 0, 1, 1),glm::vec3(0,0,1)));
  input.push_back(GL::PositionColorNormalVertex(glm::vec3( 0.5,-0.5, 0.5),glm::vec4(1, 0, 1, 1),glm::vec3(0,0,1)));
  input.push_back(GL::PositionColorNormalVertex(glm::vec3( 0.5, 0.5, 0.5),glm::vec4(1, 1, 1, 1),glm::vec3(0,0,1)));
  input.push_back(GL::PositionColorNormalVertex(glm::vec3(-0.5, 0.5, 0.5),glm::vec4(0, 1, 1, 1),glm::vec3(0,0,1)));

  //right
  input.push_back(PositionColorNormalVertex(glm::vec3(0.5, 0.5, 0.5),glm::vec4(1, 1, 1, 1),glm::vec3(1,0,0)));
  input.push_back(PositionColorNormalVertex(glm::vec3(0.5, 0.5,-0.5),glm::vec4(1, 1, 0, 1),glm::vec3(1,0,0)));
  input.push_back(PositionColorNormalVertex(glm::vec3(0.5,-0.5,-0.5),glm::vec4(1, 0, 0, 1),glm::vec3(1,0,0)));
  input.push_back(PositionColorNormalVertex(glm::vec3(0.5,-0.5, 0.5),glm::vec4(1, 0, 1, 1),glm::vec3(1,0,0)));

  //back
  input.push_back(PositionColorNormalVertex(glm::vec3(-0.5,-0.5,-0.5),glm::vec4(0, 0, 0, 1),glm::vec3(0,0,-1)));
  input.push_back(PositionColorNormalVertex(glm::vec3( 0.5,-0.5,-0.5),glm::vec4(1, 0, 0, 1),glm::vec3(0,0,-1)));
  input.push_back(PositionColorNormalVertex(glm::vec3( 0.5, 0.5,-0.5),glm::vec4(1, 1, 0, 1),glm::vec3(0,0,-1)));
  input.push_back(PositionColorNormalVertex(glm::vec3(-0.5, 0.5,-0.5),glm::vec4(0, 1, 0, 1),glm::vec3(0,0,-1)));

  //left
  input.push_back(PositionColorNormalVertex(glm::vec3(-0.5,-0.5,-0.5),glm::vec4(0, 0, 0, 1),glm::vec3(-1,0,0)));
  input.push_back(PositionColorNormalVertex(glm::vec3(-0.5,-0.5, 0.5),glm::vec4(0, 0, 1, 1),glm::vec3(-1,0,0)));
  input.push_back(PositionColorNormalVertex(glm::vec3(-0.5, 0.5, 0.5),glm::vec4(0, 1, 1, 1),glm::vec3(-1,0,0)));
  input.push_back(PositionColorNormalVertex(glm::vec3(-0.5, 0.5,-0.5),glm::vec4(0, 1, 0, 1),glm::vec3(-1,0,0)));

  //upper
  input.push_back(PositionColorNormalVertex(glm::vec3( 0.5, 0.5, 0.5),glm::vec4(1, 1, 1, 1),glm::vec3(0,1,0)));
  input.push_back(PositionColorNormalVertex(glm::vec3(-0.5, 0.5, 0.5),glm::vec4(0, 1, 1, 1),glm::vec3(0,1,0)));
  input.push_back(PositionColorNormalVertex(glm::vec3(-0.5, 0.5,-0.5),glm::vec4(0, 1, 0, 1),glm::vec3(0,1,0)));
  input.push_back(PositionColorNormalVertex(glm::vec3( 0.5, 0.5,-0.5),glm::vec4(1, 1, 0, 1),glm::vec3(0,1,0)));

  //bottom
  input.push_back(PositionColorNormalVertex(glm::vec3(-0.5, -0.5,-0.5),glm::vec4(0, 0, 0, 1),glm::vec3(0,-1,0)));
  input.push_back(PositionColorNormalVertex(glm::vec3( 0.5, -0.5,-0.5),glm::vec4(1, 0, 0, 1),glm::vec3(0,-1,0)));
  input.push_back(PositionColorNormalVertex(glm::vec3( 0.5, -0.5, 0.5),glm::vec4(1, 0, 1, 1),glm::vec3(0,-1,0)));
  input.push_back(PositionColorNormalVertex(glm::vec3(-0.5, -0.5, 0.5),glm::vec4(0, 0, 1, 1),glm::vec3(0,-1,0)));

  //note every face of the cube is on a single line
  std::vector<int> indices = {
    0,  1,  2,  0,  2,  3,   //front
    4,  5,  6,  4,  6,  7,   //right
    8,  9,  10, 8,  10, 11,  //back
    12, 13, 14, 12, 14, 15,  //left
    16, 17, 18, 16, 18, 19,  //upper
    20, 21, 22, 20, 22, 23 }; //bottom


  vertex_shader_source = R"(
out vec4 clr;
out vec3 nrm;
void main() {

  mat4 view = CameraProjection * CameraView;
  gl_Position = view * model * vec4(position , 1.0);
  clr = color;
  nrm = normal;
}
   )";

  fragment_shader_source = R"(
in vec4 clr;
in vec3 nrm;

out vec4 frag_color;
void main() {
  float ambientStrength = 0.7;  
  float diffuseStrength = 0.3;
  float diff = max(dot(nrm, Light), 0.0) * diffuseStrength;

  vec4 result = clr *  diff + clr;
  result[3] = 1;
	frag_color = result;
}
   )";

  std::vector<Uniform*> uniforms;

  _light = std::make_unique<UniformVec3>("Light");
  _light->setValue(glm::normalize(glm::vec3(1, 1, 1)));
  _model = std::make_unique<UniformMat4>("model");
  _model->setValue(glm::mat4(1.0));
  uniforms.push_back(_light.get());
  uniforms.push_back(_model.get());
  std::vector<Uniform*> cameraUniforms = _camera->getUniforms();
  uniforms.insert(uniforms.end(),cameraUniforms.begin(), cameraUniforms.end());
  _ibo = std::make_unique<IBO>(indices);
  _vbo = std::make_unique<VBO<PositionColorNormalVertex>>(input);
  _vao = std::make_unique<VAO<PositionColorNormalVertex>>(_vbo.get());
  _shader = std::make_unique<ShaderProgram>(_vao.get(), uniforms, vertex_shader_source, fragment_shader_source);

  for (int x = 0; x < 5; x++) {
    for (int y = 0; y < 5; y++) {
      _positions.push_back((glm::vec3(x / 5.0, y / 5.0, 0) - glm::vec3(0.5,0.5,0)) * 10.0f);
    }
  }
}

void DrawCubes::draw()
{

  //_camera->setPosition(glm::vec3(camX, 0.1, camZ));
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (int i = 0; i < _positions.size(); i++) {
    _model->setValue(glm::translate(glm::mat4(1), _positions[i]));
    _shader->bind();
    _camera->bind();
    _ibo->bind(_vao.get());
  }
}
