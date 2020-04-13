#pragma once

#include <array>
#include <memory>
#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"

namespace YolonaOss {
  class ImageIO
  {
  public:
    ImageIO();
    ~ImageIO();

    static void                                              writeImage(std::string filename, const Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2> & img);
    static std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>  readImage(std::string filename);


    static void                                              TEST_readwrite();
    static void                                              TEST_createNew();
  };
}