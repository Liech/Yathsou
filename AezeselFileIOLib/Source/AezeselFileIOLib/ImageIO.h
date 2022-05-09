#pragma once

#include <array>
#include <memory>
#include <vector>
#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"

namespace gli {
  class texture2d;
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

    static void                                              writeImage(const std::string& filename, const Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2> & img);
    static std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>               readImage(const std::string& filename);
    static std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>               readImage(ImageIO::Format,const std::vector<unsigned char>&);

    static bool                                                                               isDDSCube(const std::vector<unsigned char>&);
    static bool                                                                               isDDSCube(const std::string& filename);
    static std::vector<std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>>  readDDSCube(const std::string& filename);
    static std::vector<std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>>  readDDSCube(ImageIO::Format, const std::vector<unsigned char>&);

  private:
    static std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>  readPNG(const std::vector<unsigned char>&);
    static std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>  readPNG(const std::string& filename);
    static std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>  readPNG(int,int,std::vector<unsigned char>&);

    static std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>  readDDS(const std::vector<unsigned char>&);
    static std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>  readDDS(const std::string& filename);
    static std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>  readDDS(const gli::texture2d& tex);

  };
}