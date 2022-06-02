#pragma once

#include <memory>
#include <string>

namespace Haas {
  class Dll {
    public:
    Dll(const std::string&);
    virtual ~Dll();


    private:
      void load_hostfxr();
      
      void* load_library(const wchar_t*);
      void* get_export(void*, const char*);
    
      class Pimpl;
      std::unique_ptr<Dll::Pimpl> _pimpl;
  };
}