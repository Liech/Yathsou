#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <set>

namespace zipper {
  class Unzipper;
}

namespace Aezesel {
  class ZIP {
  public:
    ZIP(const std::string& filename, bool fullUnzip = true);
    ~ZIP();

    void unzip(const std::string& targetFolder);
    std::vector<std::string>                          getEntries();
    std::vector<unsigned char>                        getFile(const std::string& name);
    std::map<std::string, std::vector<unsigned char>> getFolder(const std::string& name);
    bool                                              hasFile(const std::string& name);
  private:
    std::unique_ptr<zipper::Unzipper> _unzipper;
    std::string                       _filename;
    std::vector<std::string>          _entries;
    std::set<std::string>             _entriesSet;
  };
}