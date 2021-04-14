#include "ZIP.h"

#include "lib/zipper/unzipper.h"


namespace Aezesel {
  ZIP::ZIP() {
    zipper::Unzipper unzipper("C:\\Users\\nicol\\Downloads\\BLZip-master.zip");
    std::vector<zipper::ZipEntry> entries = unzipper.entries();
    unzipper.close();
  }
}