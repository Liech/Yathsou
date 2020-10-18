#pragma once

#include <string>
#include <memory>

namespace Ahwassa
{
  class SoundHandler;
  
  class SoundEngine
  {
  public:
    void                          load          (std::string filename, std::string alias);
    void                          playAndForget (                      std::string alias);
    std::shared_ptr<SoundHandler> createHandler (                      std::string alias);    
  private:
  };
}