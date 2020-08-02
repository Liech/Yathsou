#pragma once

#include <stack>
#include <array>
#include <functional>
#include <vector>
#include <IyathuumCoreLib/lib/glm/glm.hpp>

namespace YolonaOss {
  template<size_t Dimension>
  class Util {
  public:
    using vec = glm::vec<Dimension, float, glm::defaultp>;

    static void apply(std::array<size_t, Dimension> start, std::array<size_t, Dimension> size, std::function<void(std::array<size_t, Dimension> index)> func) {
      std::vector<std::array<size_t, Dimension>> indices = Util<Dimension>::getRange(start, size);
#pragma omp parallel for
      for (int64_t i = 0; i < indices.size(); i++) {
        func(indices[i]);
      }
    }

    static std::vector<std::array<size_t, Dimension>> getRange(std::array<size_t, Dimension> start, std::array<size_t, Dimension> size) {
      std::vector<std::array<size_t, Dimension>> result;
      struct Todo {
        size_t dimension;
        std::array<size_t, Dimension> index;
      };
      std::stack<Todo> todo;
      Todo startTodo;
      startTodo.dimension = 0;
      startTodo.index = start;
      todo.push(startTodo);

      while (!todo.empty()) {
        Todo current = todo.top();
        todo.pop();

        if (current.dimension != Dimension - 1)
          for (size_t i = 0; i < size[current.dimension]; i++) {
            Todo next;
            next.dimension = current.dimension + 1;
            next.index = current.index;
            next.index[current.dimension] += i;
            todo.push(next);
          }
        else
        {
          for (size_t i = 0; i < size[current.dimension]; i++) {
            std::array<size_t, Dimension> r = current.index;
            r[current.dimension] = current.index[current.dimension] + i;
            result.push_back(r);
          }
        }
      }
      return result;
    }

    template<typename t>
    static vec array2Vec(std::array<t, Dimension> val) {
      vec result;
      for (size_t i = 0; i < Dimension; i++)
        result[i] = (float)val[i];
      return result;
    }
    template<typename t>
    static std::array<t, Dimension> vec2Array(vec val) {
      std::array<t, Dimension> result;
      for (size_t i = 0; i < Dimension; i++)
        result[i] = (t)val[i];
      return result;
    }
  };
}