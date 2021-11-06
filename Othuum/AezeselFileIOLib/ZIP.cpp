#include "ZIP.h"

#include <iostream>

#include "lib/zipper/unzipper.h"

//does not work for supreme commander units.sca...
//eg UAL0401_Aactivate.sca is not found...
//useless :(
namespace Aezesel {
  ZIP::ZIP(const std::string& filename, bool fullUnzip) {
    _filename = filename;
    _unzipper = std::make_unique<zipper::Unzipper>(filename);
    
    auto entries =  _unzipper->entries();
    for (auto x : entries)
      _entries.push_back(x.name);

    _entriesSet.insert(_entries.begin(), _entries.end());
  }

  ZIP::~ZIP() {
    _unzipper->close();
  }

  void ZIP::unzip(const std::string& targetFolder) {
    _unzipper->extract(targetFolder);
  }

  std::vector<std::string> ZIP::getEntries() {
    return _entries; 
  }

  std::vector<unsigned char> ZIP::getFile(const std::string& name) {
    std::vector<unsigned char> unzipped_entry;
    bool success= _unzipper->extractEntryToMemory(name, unzipped_entry);
    if (!success)
      throw std::runtime_error("Entry not found");
    return unzipped_entry;
  }

  std::map<std::string, std::vector<unsigned char>> ZIP::getFolder(const std::string& name) {
    std::map<std::string, std::vector<unsigned char>> result;
    int len = (name + "/").length();
    for (auto entry : _entries) {
      if (!entry.starts_with(name + "/"))
        continue;
      if (entry.length() == len)
        continue;
      result[entry.substr(len)] = getFile(entry);
    }
    return result;
  }

  bool ZIP::hasFile(const std::string& name) {
    return _entriesSet.count(name) != 0;
  }
}