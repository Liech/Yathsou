#include "FileDropper.h"

namespace Ahwassa {
  FileDropper::FileDropper(std::function<void(const std::string& path)> call) {
    _callback = call;
  }

  bool FileDropper::dropEvent(const std::string filePath) {
    _callback(filePath);
    return true;
  }
}