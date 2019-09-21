#include "BasicTriangle.h"



namespace YolonaOss {
  BasicTriangle::BasicTriangle()
  {
  }


  BasicTriangle::~BasicTriangle()
  {
  }

  void BasicTriangle::load(GL::DrawSpecification* d)
  {
    _spec = d;
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    std::vector<Vector3gl> input;
    input.push_back(Vector3gl(0.0f, 0.5f, 0.0f));
    input.push_back(Vector3gl(0.5f, -0.5f, 0.0f));
    input.push_back(Vector3gl(-0.5f, -0.5f, 0.0f));

    vertex_shader_source = R"(
void main() {
	gl_Position = vec4(position, 1.0);
}
   )";

    fragment_shader_source = R"(
out vec4 frag_color;
void main() {
	frag_color = vec4(0.5, 0.0, 0.0, 0.0);
}
   )";

    _vbo = std::make_unique<GL::VBO<Vector3gl>>(input);
    _vao = std::make_unique<GL::VAO<Vector3gl>>(_vbo.get());
    _shader = std::make_unique<GL::ShaderProgram>(_vao.get(), std::vector<GL::Uniform*>(), vertex_shader_source, fragment_shader_source);
  }

  void BasicTriangle::draw()
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _shader->bind();
    _vao->bind();
  }
}