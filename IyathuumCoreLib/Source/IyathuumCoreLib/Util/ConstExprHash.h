#pragma once

#include <string>
//https://stackoverflow.com/questions/2111667/compile-time-string-hashing
template<class>struct constexprHASHER;
template<>
struct constexprHASHER<std::string> {
  std::size_t constexpr operator()(char const* input)const {
    return *input ?
      static_cast<unsigned int>(*input) + 33 * (*this)(input + 1) :
      5381;
  }
  std::size_t operator()(const std::string& str) const {
    return (*this)(str.c_str());
  }
};
template<typename T>
std::size_t constexpr constexprHASH(T&& t) {
  return constexprHASHER< typename std::decay<T>::type >()(std::forward<T>(t));
}
inline namespace literals {
  std::size_t constexpr operator "" _hash(const char* s, size_t) {
    return constexprHASHER<std::string>()(s);
  }
}
 