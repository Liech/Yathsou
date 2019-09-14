#include "RotatingCube.h"


#include "GLFW/glfw3.h"

#include "../glad/include/glad/glad.h"
void RotatingCube::load(DrawSpecification *d)
{
  _spec = d;
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  std::vector<PositionColorNormalVertex> input;

  
  //front
  input.push_back(PositionColorNormalVertex(glm::vec3(-0.5,-0.5, 0.5),glm::vec4(0, 0, 1, 1),glm::vec3(0,0,1)));
  input.push_back(PositionColorNormalVertex(glm::vec3( 0.5,-0.5, 0.5),glm::vec4(1, 0, 1, 1),glm::vec3(0,0,1)));
  input.push_back(PositionColorNormalVertex(glm::vec3( 0.5, 0.5, 0.5),glm::vec4(1, 1, 1, 1),glm::vec3(0,0,1)));
  input.push_back(PositionColorNormalVertex(glm::vec3(-0.5, 0.5, 0.5),glm::vec4(0, 1, 1, 1),glm::vec3(0,0,1)));

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
  std::vector<GLuint> indices = {
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
  gl_Position = view * vec4(position , 1.0);
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

  _camera = std::make_unique<Camera>("Camera",_spec->width,_spec->height);
  _light = std::make_unique<UniformVec3>("Light");
  _light->setValue(glm::normalize(glm::vec3(1, 1, 1)));
  uniforms.push_back(_light.get());
  std::vector<Uniform*> cameraUniforms = _camera->getUniforms();
  uniforms.insert(uniforms.end(),cameraUniforms.begin(), cameraUniforms.end());
  _ibo = std::make_unique<IBO>(indices);
  _vbo = std::make_unique<VBO<PositionColorNormalVertex>>(input);
  _vao = std::make_unique<VAO<PositionColorNormalVertex>>(_vbo.get());
  _shader = std::make_unique<ShaderProgram>(_vao.get(), uniforms, vertex_shader_source, fragment_shader_source);
}

void RotatingCube::draw()
{
  float radius = 4.0f;
  float camX = sin(glfwGetTime()) * radius;
  float camZ = cos(glfwGetTime()) * radius;
  _camera->setPosition(glm::vec3(camX, 0.1, camZ));

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader->bind();
  _camera->bind();
  _ibo->bind(_vao.get());
}
