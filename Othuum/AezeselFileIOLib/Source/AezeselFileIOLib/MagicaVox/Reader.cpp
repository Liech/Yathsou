#include "Reader.h"
#include "ChunkFactory.h"
#include "Chunk.h"
#include <stdexcept>

namespace Aezesel {
  namespace MagicaVoxImporter {
    Reader::Reader(std::vector<unsigned char> content) {
      _content = content;
    }

    bool Reader::endOfBufferReached() {
      return _content.size() <= _currentPosition;
    }

    void Reader::assertCanRead() {
      if (endOfBufferReached())
        throw std::runtime_error("End of Buffer Reached!");
    }

    Reader Reader::read(size_t numberOfBytes) {
      return Reader(readChars(numberOfBytes));
    }

    std::vector<unsigned char> Reader::readChars(size_t numberOfBytes) {
      assertCanRead();
      std::vector<unsigned char> subVector(_content.begin() + _currentPosition, _content.begin() + _currentPosition + numberOfBytes);
      _currentPosition += numberOfBytes;
      return subVector;
    }

    std::string Reader::readChunkID() {
      assertCanRead();
      std::string id(_content.begin() + _currentPosition, _content.begin() + _currentPosition + 4);
      _currentPosition += 4;
      return id;
    }

    int Reader::readInt() {
      std::vector<unsigned char> bytes = readChars(4);

      int result = int((unsigned char)(bytes[0]) |
        (unsigned char)(bytes[1]) << 8 |
        (unsigned char)(bytes[2]) << 16 |
        (unsigned char)(bytes[3] << 24));
      return result;
    }

    std::shared_ptr<Chunk> Reader::readChunk() {
      std::string id = readChunkID();
      int ownContent = readInt();
      int childContent = readInt();
      Reader own;
      if (ownContent > 0) own = read(ownContent);
      Reader child;
      if (childContent > 0) child = read(childContent);
      std::shared_ptr<Chunk> result = ChunkFactory::make(id);
      result->read(own, child);
      return result;
    }

    std::string Reader::readString() {
      //int32: buffer size(in bytes)
      //int8xN : buffer(without the ending "\0")
      int size = readInt();
      std::vector<unsigned char> msg = readChars(size);
      return std::string(msg.begin(), msg.end());
    }

    std::map<std::string, std::string> Reader::readDict() {
      //int32: num of key - value pairs

      //  // for each key-value pair
      //{
      //STRING: key
      //STRING : value
      //}xN
      int numberOfPairs = readInt();
      std::map<std::string, std::string> result;

      for (int i = 0; i < numberOfPairs; i++) {
        std::string key = readString();
        std::string value = readString();
        result[key] = value;
      }
      return result;
    }

    Rotation Reader::readRotation() {
      //bit | value
      //0-1 : 1 : index of the non-zero entry in the first row
      //2-3 : 2 : index of the non-zero entry in the second row
      //4   : 0 : the sign in the first row (0 : positive; 1 : negative)
      //5   : 1 : the sign in the second row (0 : positive; 1 : negative)
      //6   : 1 : the sign in the third row (0 : positive; 1 : negative)

      Rotation result;
      unsigned char raw = readChars(1)[0];

      //maybe the endian order is reversed here?
      int firstRowPos = (0b11000000 & raw) >> 6;
      int secondRowPos = (0b00110000 & raw) >> 4;
      bool signFirstRow = (0b00001000 & raw) != 0;
      bool signSecondRow = (0b00000100 & raw) != 0;
      bool signThirdRow = (0b00000010 & raw) != 0;

      if (firstRowPos == 0) result.v00 = signFirstRow ? -1 : 1;
      if (firstRowPos == 1) result.v10 = signFirstRow ? -1 : 1;
      if (firstRowPos == 2) result.v20 = signFirstRow ? -1 : 1;
      if (secondRowPos == 0) result.v01 = signSecondRow ? -1 : 1;
      if (secondRowPos == 1) result.v11 = signSecondRow ? -1 : 1;
      if (secondRowPos == 2) result.v21 = signSecondRow ? -1 : 1;

      if (firstRowPos + secondRowPos == 3) result.v02 = signThirdRow ? -1 : 1;
      if (firstRowPos + secondRowPos == 2) result.v12 = signThirdRow ? -1 : 1;
      if (firstRowPos + secondRowPos == 1) result.v22 = signThirdRow ? -1 : 1;
      return result;
    }
  }
}