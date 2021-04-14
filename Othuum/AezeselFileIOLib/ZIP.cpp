#include "ZIP.h"

#include <iostream>

#include "lib/zipper/unzipper.h"


namespace Aezesel {
  ZIP::ZIP(const std::string& filename) {
    _filename = filename;
    _unzipper = std::make_unique<zipper::Unzipper>(filename);
  }

  ZIP::~ZIP() {
    _unzipper->close();
  }

  std::vector<std::string> ZIP::getEntries() {
    std::vector<zipper::ZipEntry> entries = _unzipper->entries();
    std::vector<std::string> result;
    for (auto x : entries)
      result.push_back(x.name);
    return result;
  }

  std::vector<unsigned char> ZIP::getFile(std::string name) {
    std::vector<unsigned char> unzipped_entry;
    bool success= _unzipper->extractEntryToMemory(name, unzipped_entry);
    if (!success)
      throw std::runtime_error("Entry not found");
    return unzipped_entry;
  }

}