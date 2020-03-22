#pragma once

#include <array>
#include <memory>
#include "../structs/MultiDimensionalArray.h"
#include "../structs/Color.h"

namespace YolonaOss {
  class ImageUtil
  {
  public:
    ImageUtil();
    ~ImageUtil();

    static std::unique_ptr<MultiDimensionalArray<Color, 2>>  createEmpty(size_t width, size_t height);


    template<typename SCALAR, size_t Dimension>
    static std::unique_ptr<MultiDimensionalArray<SCALAR, Dimension>> scale(MultiDimensionalArray<SCALAR, Dimension>* input, std::array<size_t, Dimension> newResolution) {      
      std::unique_ptr<MultiDimensionalArray<SCALAR, Dimension>> result = std::make_unique<MultiDimensionalArray<SCALAR, Dimension>>(newResolution);
      std::array<double, Dimension> scaleFactor;
      for (size_t i = 0; i < Dimension; i++)
        scaleFactor[i] = (double)input->getDimension(i) / (double)result->getDimension(i);      
      
      result->apply([input, scaleFactor](std::array<size_t, Dimension> resultPos, SCALAR& val) {
        std::array<double, Dimension> inputPos;
        for (size_t i = 0; i < Dimension; i++)
          inputPos[i] = scaleFactor[i] * (double)resultPos[i];


      });
    }

    template<typename SCALAR, size_t Dimension> 
    static std::unique_ptr<MultiDimensionalArray<Color, Dimension>>  toGrayscale(MultiDimensionalArray<SCALAR, Dimension>* input, SCALAR Min, SCALAR Max) {
      std::unique_ptr<MultiDimensionalArray<Color, Dimension>> result = std::make_unique<MultiDimensionalArray<Color, Dimension>>(input->getDimensionVector());
      result->apply([Min,Max,input](size_t pos, Color& val) {
        double v = (input->get_linearVal(pos) - Min) / (Max - Min);
        val = Color(std::numeric_limits<unsigned char>::max() * v, std::numeric_limits<unsigned char>::max() * v, std::numeric_limits<unsigned char>::max() * v);
      });
      return result;
    }

  };
}