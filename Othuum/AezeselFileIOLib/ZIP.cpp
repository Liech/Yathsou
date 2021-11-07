#include "ZIP.h"

#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "lib/zipper/unzipper.h"

//does not work for supreme commander units.sca...
//eg UAL0401_Aactivate.sca is not found...
//useless :(
namespace Aezesel {
  ZIP::ZIP(const std::string& filename) {
    _filename = filename;

    std::ifstream input(filename, std::ios::binary);
    _data = std::vector<unsigned char>(std::istreambuf_iterator<char>(input), {});

    _unzipper = std::make_unique<zipper::Unzipper>(_data);    

    auto entries =  _unzipper->entries();
    for (auto x : entries)
      _entries.push_back(x.name);

    _entriesSet.insert(_entries.begin(), _entries.end());

    for (auto x : _entries) {
      _lowerCaseMap[toNormalForm(x)] = x;
    }
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
    std::string entry = toArchiveForm(name);
    std::vector<unsigned char> unzipped_entry;
    bool success= _unzipper->extractEntryToMemory(entry, unzipped_entry);
    if (!success) {
      std::cout << name << " -> " << entry << " not found in " << _filename << std::endl;
      throw std::runtime_error("Entry not found");
    }
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
    return _entriesSet.count(toArchiveForm(name)) != 0;
  }

  std::string ZIP::toNormalForm(const std::string& input) {
    std::string result = input;
    std::replace(result.begin(), result.end(), '\\', '/');
    std::transform(result.begin(), result.end(), result.begin(),
      [](unsigned char c) { return std::tolower(c); });
    return result;
  }

  std::string ZIP::toArchiveForm(const std::string& input) {
    return _lowerCaseMap[toNormalForm(input)];
  }
}