#pragma once


template<size_t Dimension>
class Util {
public:
  using vec = typedef glm::vec<Dimension, float, glm::defaultp>;

  template<typename t>
  static vec array2Vec(std::array<t, Dimension> val) {
    vec result;
    for (size_t i = 0; i < Dimension; i++)
      result[i] = val[i];
    return result;
  }
  template<typename t>
  static std::array<t, Dimension> vec2Array(vec val) {
    std::array<t, Dimension> result;
    for (size_t i = 0; i < Dimension; i++)
      result[i] = val[i];
    return result;
  }
};