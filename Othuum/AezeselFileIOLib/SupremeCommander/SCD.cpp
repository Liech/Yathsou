#include "SCD.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>


namespace Aezesel {
  SCD::SCD(const std::string& archivePath) {
    _archivePath = archivePath;
    _isArchive = archivePath.ends_with(".scd");

    if (isArchive()) {
      _archive = std::make_unique<Aezesel::ZIP>(archivePath);
      _archiveFilename = std::filesystem::path(archivePath).stem().string();
    }
  }

  bool SCD::isArchive() const {
    return _isArchive;
  }

  std::string SCD::getPath() const {
    return _archivePath;
  }

  std::vector<std::string> SCD::getDirectories(const std::string& subPath ) const {
    std::vector<std::string> result;
    if (isArchive()) {
      for (auto x : _archive->getEntries()) {
        std::string path = _archiveFilename + "/" + subPath;
        if (x.starts_with(path) && x != _archiveFilename + "/" + subPath) {
          std::string withoutPrefix = x.substr(_archiveFilename.size() + 1);          
          int firstSlash = withoutPrefix.find_first_of('/');
          if (firstSlash+1 != withoutPrefix.size())
            continue;
          result.push_back(withoutPrefix.substr(0,firstSlash));
        }
      }
    }
    else {
      for (auto x : std::filesystem::directory_iterator(getPath() + "/" + subPath))
        result.push_back(x.path().string().substr(_archivePath.size() + 1));
    }
    return result;
  }

  bool SCD::fileExists(const std::string file) const {
    if (isArchive()) {
      std::string s = file;
      std::replace(s.begin(), s.end(), '\\', '/');
      return _archive->hasFile(_archiveFilename + "/" + s);
    }
    else
      return std::filesystem::exists(_archivePath + "/" + file);
  }

  std::vector<unsigned char> SCD::loadBinaryFile(const std::string file) const {
    if (isArchive()) {
      std::string s = file;
      std::replace(s.begin(), s.end(), '\\', '/');
      return _archive->getFile(_archiveFilename + "/" + s);
    }
    else
    {
      std::ifstream input(_archivePath + "/" + file, std::ios::binary);
      if (input.fail())
        throw std::runtime_error("Error opening " + _archivePath + "/" + file);
      return std::vector<unsigned char>(std::istreambuf_iterator<char>(input), {});
    }
  }

  std::string SCD::loadTextFile(const std::string file) const {
    if (isArchive()) {
      std::string s = file;      
      std::replace(s.begin(),s.end(),'\\', '/');
      std::cout << " - Load " << file << std::endl;
      auto binary = _archive->getFile(_archiveFilename + "/" + s);
      return std::string((const char*)binary.data(),binary.size());
    }
    else {
      std::ifstream t(_archivePath + "/" + file);
      std::string str((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());
      return str;
    }
  }
}