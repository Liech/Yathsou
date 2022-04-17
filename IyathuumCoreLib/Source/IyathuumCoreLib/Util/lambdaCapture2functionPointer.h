#pragma once

#include<type_traits>
#include<utility>
//https://stackoverflow.com/questions/28746744/passing-capturing-lambda-as-function-pointer/45365798
//https://stackoverflow.com/a/45365798

namespace Iyathuum
{
  template<typename Callable>
  union storage
  {
    storage() {}
    std::decay_t<Callable> callable;
  };

  template<int, typename Callable, typename Ret, typename... Args>
  auto fnptr_(Callable&& c, Ret(*)(Args...))
  {
    static bool used = false;
    static storage<Callable> s;
    using type = decltype(s.callable);

    if (used)
      s.callable.~type();
    new (&s.callable) type(std::forward<Callable>(c));
    used = true;

    return [](Args... args) -> Ret {
      return Ret(s.callable(std::forward<Args>(args)...));
    };
  }

  template<typename Fn, int N = 0, typename Callable>
  Fn* lambdaCapture2functionPointer(Callable&& c)
  {
    return fnptr_<N>(std::forward<Callable>(c), (Fn*)nullptr);
  }
}