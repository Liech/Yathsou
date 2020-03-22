#include "ImageUtil.h"

#include <stdexcept>

#include "../structs/Color.h"
#include "../Lib/lodepng/lodepng.h"

namespace YolonaOss {
  ImageUtil::ImageUtil()
  {
  }


  ImageUtil::~ImageUtil()
  {
  }

  std::unique_ptr<MultiDimensionalArray<Color, 2>>  ImageUtil::createEmpty(size_t width, size_t height) {
    std::unique_ptr<MultiDimensionalArray<Color, 2>> result = std::make_unique<MultiDimensionalArray<Color, 2>>(width, height);
    return result;
  }
}