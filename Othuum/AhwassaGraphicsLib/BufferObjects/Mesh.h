#pragma once

#include <memory>
#include "IMesh.h"
#include "VBO.h"
#include "VAO.h"
#include "IBO.h"

namespace Ahwassa {
  template <typename Vertex>
  class Mesh : public IMesh
  {
  public:
    Mesh(const std::vector<Vertex>& vertecies, const std::vector<int>& indicies) {
      _ibo = std::make_unique<IBO>(indices);
      _vbo = std::make_unique<VBO<Vertex>>(vertecies);
      _vao = std::make_unique<VAO<Vertex>>(vbo.get());
    }

    Mesh(const std::vector<Vertex>& trianglestrip) {
      std::vector<int> indices;
      indices.resize(trianglestrip.size());
      for (int i = 0; i < trianglestrip.size(); i++)
        indices[i] = i;
      _ibo = std::make_unique<IBO>(indices);
      _vbo = std::make_unique<VBO<Vertex>>(vertecies);
      _vao = std::make_unique<VAO<Vertex>>(vbo.get());
    }

    virtual void draw() override {
      _ibo->draw(_vao.get());
    }

    virtual void drawInstanced(size_t amount) override {
      _ibo->drawInstanced(_vao.get(),amount);
    }

  private:
    std::unique_ptr<VBO<Vertex>>> _vbo;
    std::unique_ptr<VAO<Vertex>>> _vao;
    std::unique_ptr<IBO>        > _ibo;
  };
}