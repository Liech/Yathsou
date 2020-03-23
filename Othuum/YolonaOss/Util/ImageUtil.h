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
    static SCALAR sum(MultiDimensionalArray<SCALAR, Dimension>* input) {
      return input->reduce(0, [](SCALAR A, SCALAR B) {return A + B; });
    }

    template<typename SCALAR, size_t Dimension>
    static std::unique_ptr<MultiDimensionalArray<SCALAR, Dimension>> scaleUp(MultiDimensionalArray<SCALAR, Dimension>* input, std::array<size_t, Dimension> newResolution) {      
      std::unique_ptr<MultiDimensionalArray<SCALAR, Dimension>> result = std::make_unique<MultiDimensionalArray<SCALAR, Dimension>>(newResolution);
      std::array<double, Dimension> scaleFactor;
      for (size_t i = 0; i < Dimension; i++)
        scaleFactor[i] = (double)input->getDimension(i) / (double)result->getDimension(i);      
      
      result->apply([input, scaleFactor](std::array<size_t, Dimension> resultPos, SCALAR& val) {
        std::array<double, Dimension> inputPerc;
        std::array<size_t, Dimension> inputIndex;
        for (size_t i = 0; i < Dimension; i++) {
          inputPerc[i] = scaleFactor[i] * (double)resultPos[i];
          inputIndex[i] = std::floor(inputPerc[i]);
          inputPerc[i] -= inputIndex[i]; // value between 0 and 1
        }
        val = NLinearInterpolateRecursive(input, inputIndex, inputPerc);
      });
      return result;
    }
  private:
    template<typename SCALAR, size_t Dimension>
    static SCALAR NLinearInterpolateRecursive(MultiDimensionalArray<SCALAR, Dimension>* input, std::array<size_t, Dimension> position, std::array<double, Dimension> perc, size_t currentDimension = Dimension - 1) {
      if (currentDimension == 0)
        return input->getVal(position);
      else {
        std::array<size_t, Dimension> nextPos = position;
        nextPos[currentDimension]++;
        if (nextPos[currentDimension] >= input->getDimension(currentDimension))
          nextPos[currentDimension] = input->getDimension(currentDimension)-1;
        return NLinearInterpolateRecursive(input, position, perc, currentDimension - 1) * perc[currentDimension] + NLinearInterpolateRecursive(input,nextPos,perc,currentDimension-1) * (1.0-perc[currentDimension]);
      }
    }
  public:

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