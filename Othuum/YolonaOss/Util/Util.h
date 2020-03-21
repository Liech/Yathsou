#pragma once


template<size_t Dimension>
class Util {
public:
  using vec = typedef glm::vec<Dimension, float, glm::defaultp>;

  static vec array2Vec(std::array<size_t, Dimension> val) {
    vec result;
    for (size_t i = 0; i < Dimension; i++)
      result[i] = val[i];
    return result;
  }
  static std::array<size_t, Dimension> vec2Array(vec val) {
    std::array<size_t, Dimension> result;
    for (size_t i = 0; i < Dimension; i++)
      result[i] = val[i];
    return result;
  }
};