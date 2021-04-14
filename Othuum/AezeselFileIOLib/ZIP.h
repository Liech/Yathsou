#pragma once

#include <string>
#include <memory>
#include <vector>

namespace zipper {
  class Unzipper;
}

namespace Aezesel {
  class ZIP {
  public:
    ZIP(const std::string& filename);
    ~ZIP();

    std::vector<std::string>   getEntries();
    std::vector<unsigned char> getFile(std::string name);
  private:
    std::unique_ptr<zipper::Unzipper> _unzipper;
    std::string                       _filename;
  };
}