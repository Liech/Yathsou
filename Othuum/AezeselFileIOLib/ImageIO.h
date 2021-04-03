#pragma once

#include <array>
#include <memory>
#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"

namespace Aezesel {
  class ImageIO
  {
  public:
    ImageIO();
    ~ImageIO();

    static void                                              writeImage(std::string filename, const Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2> & img);
    static std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>  readImage(std::string filename);


    static void                                              TEST_readwrite();
    static void                                              TEST_createNew();
  private:
    static std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>  readPNG(std::string filename);
    static std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>  readDDS(std::string filename);
  };
}