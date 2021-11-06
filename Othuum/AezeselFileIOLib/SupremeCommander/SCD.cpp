#include "SCD.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace Aezesel {
  SCD::SCD(const std::string& archivePath) {
    _archivePath = archivePath;
    _isArchive = archivePath.ends_with(".scd");
  }

  bool SCD::isArchive() const {
    return _isArchive;
  }

  std::string SCD::getPath() const {
    return _archivePath;
  }

  std::vector<std::string> SCD::getDirectories(const std::string& subPath ) const {
    std::vector<std::string> result;
    for (auto x : std::filesystem::directory_iterator(getPath() + "/" + subPath))
      result.push_back(x.path().string().substr(_archivePath.size()+1));
    return result;
  }

  bool SCD::fileExists(const std::string file) const {
    return std::filesystem::exists(_archivePath + "/" + file);
  }

  std::vector<unsigned char> SCD::loadBinaryFile(const std::string file) const {
    std::ifstream input(_archivePath + "/" + file, std::ios::binary);
    if (input.fail())
      throw std::runtime_error("Error opening " + _archivePath + "/" + file);
    return std::vector<unsigned char>(std::istreambuf_iterator<char>(input), {});
  }

  std::string SCD::loadTextFile(const std::string file) const {
    std::ifstream t(_archivePath + "/" + file);
    std::string str((std::istreambuf_iterator<char>(t)),
      std::istreambuf_iterator<char>());
    return str;
  }
}