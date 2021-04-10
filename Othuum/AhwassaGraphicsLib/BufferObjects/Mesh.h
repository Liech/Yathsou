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
    Mesh(const std::vector<Vertex>& vertecies, const std::vector<int>& indices) {
      _ibo = std::make_unique<IBO>(indices);
      _vbo = std::make_unique<VBO<Vertex>>(vertecies);
      _vao = std::make_unique<VAO>(_vbo.get());
    }

    Mesh(const std::vector<Vertex>& trianglestrip) {
      std::vector<int> indices;
      indices.resize(trianglestrip.size());
      for (int i = 0; i < trianglestrip.size(); i++)
        indices[i] = i;
      _ibo = std::make_unique<IBO>(indices);
      _vbo = std::make_unique<VBO<Vertex>>(trianglestrip);
      _vao = std::make_unique<VAO<Vertex>>(_vbo.get());
    }

    virtual void draw() override {
      _ibo->draw(_vao.get());
    }

    virtual void drawInstanced(size_t amount) override {
      _ibo->drawInstanced(_vao.get(),amount);
    }

  private:
    std::unique_ptr<VBO<Vertex>> _vbo;
    std::unique_ptr<VAO>         _vao;
    std::unique_ptr<IBO        > _ibo;
  };
}