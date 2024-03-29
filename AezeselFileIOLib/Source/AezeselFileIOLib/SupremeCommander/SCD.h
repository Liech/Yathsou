#pragma once

#include <string>
#include <vector>
#include <memory>

#include "AezeselFileIOLib/ZIP.h"

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
    SCD(const std::string& archiveOrFolderPath);
    virtual ~SCD() = default;

    std::vector<std::string>   getDirectories(const std::string& subPath = "") const;
    std::vector<std::string>   getFiles      (const std::string& subPath = "") const;
    bool                       fileExists    (const std::string file) const;
    std::vector<unsigned char> loadBinaryFile(const std::string file) const;
    std::string                loadTextFile  (const std::string file) const;

    std::string getPath()   const;
    bool        isArchive() const;
  private:

    bool                 _isArchive      ;
    std::string          _archivePath    ;
    std::unique_ptr<ZIP> _archive        ;
    std::string          _archiveFilename;
  };
}