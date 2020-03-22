#pragma once

#include <array>
#include <memory>
#include "../structs/MultiDimensionalArray.h"
#include "../structs/Color.h"

namespace YolonaOss {
  class ImageIO
  {
  public:
    ImageIO();
    ~ImageIO();

    static void                                              writeImage(std::string filename, const MultiDimensionalArray<Color, 2> & img);
    static std::unique_ptr<MultiDimensionalArray<Color, 2>>  readImage(std::string filename);
    static std::unique_ptr<MultiDimensionalArray<Color, 2>>  createEmpty(size_t width, size_t height);


    static void                                              TEST_readwrite();
    static void                                              TEST_createNew();
  };
}