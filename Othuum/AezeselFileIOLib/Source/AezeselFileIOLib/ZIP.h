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
    ZIP(const std::string& filename);
    ~ZIP();

    void unzip(const std::string& targetFolder);
    std::vector<std::string>                          getEntries();
    std::vector<unsigned char>                        getFile(const std::string& name);
    std::map<std::string, std::vector<unsigned char>> getFolder(const std::string& name);
    bool                                              hasFile(const std::string& name);
  private:

    //lower case, upper case, backslashes and slashes are wildly mixed in supcom paths
    //to handle those these are introduced
    std::string toArchiveForm(const std::string&); //as in archive, wildly mixed
    std::string toNormalForm(const std::string&); //lower case & slash 'path/path/path'

    std::unique_ptr<zipper::Unzipper> _unzipper;
    std::string                       _filename;
    std::vector<std::string>          _entries;
    std::set<std::string>             _entriesSet;
    std::vector<unsigned char>        _data;
    std::map<std::string, std::string> _lowerCaseMap;
  };
}