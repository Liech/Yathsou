#pragma once

#include <string>
#include <vector>

namespace Aezesel {
  /// <summary>
  /// Supreme Commander Gamedata Archive
  /// 
  /// scd files are zip files in disguise
  /// Some files magically appear only if you unzip it with e.g. 7z
  /// The zipper lib of this library is not able to unzip all hidden files
  /// 
  /// takes either unzipped folder or .scd file and offers an indistinguishable interface
  /// </summary>
  class SCD {
  public:
    SCD(const std::string& archivePath);

    std::vector<std::string>   getDirectories(const std::string& subPath = "") const ;
    bool                       fileExists    (const std::string file) const;
    std::vector<unsigned char> loadBinaryFile(const std::string file) const;
    std::string                loadTextFile  (const std::string file) const;

    std::string getPath()   const;
    bool        isArchive() const;
  private:

    bool        _isArchive;
    std::string _archivePath;
  };
}