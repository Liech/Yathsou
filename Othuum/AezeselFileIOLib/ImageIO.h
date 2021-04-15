#pragma once

#include <array>
#include <memory>
#include <vector>
#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"

namespace gli {
  class texture;
}
namespace Aezesel {
  class ImageIO
  {
  public:
    enum class Format {
      PNG, DDS
    };
      
    ImageIO();
    ~ImageIO();

    static void                                              writeImage(std::string filename, const Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2> & img);
    static std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>  readImage(std::string filename);
    static std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>  readImage(ImageIO::Format,const std::vector<unsigned char>&);


  private:
    static std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>  readPNG(const std::vector<unsigned char>&);
    static std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>  readPNG(std::string filename);
    static std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>  readPNG(int,int,std::vector<unsigned char>&);

    static std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>  readDDS(const std::vector<unsigned char>&);
    static std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>  readDDS(std::string filename);
    static std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>  readDDS(gli::texture& tex);

  };
}