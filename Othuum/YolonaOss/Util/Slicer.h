#pragma once

#include "../structs/MultiDimensionalArray.h"
#include <memory>
#include <vector>

namespace YolonaOss {
  class Slicer {
  public:
    template <typename Type, int Dimension>
    static std::unique_ptr<MultiDimensionalArray<Type, Dimension - 1>> slice(MultiDimensionalArray<Type, Dimension> * input, size_t slicePlane, size_t sliceNumber) {
      std::vector<size_t> newDim;
      for (size_t i = 0; i < Dimension; i++)
        if (i != slicePlane)
          newDim.push_back(input->getDimension(i));

      std::unique_ptr<MultiDimensionalArray<Type, Dimension - 1>> result = std::make_unique<MultiDimensionalArray<Type, Dimension - 1>>(newDim);

      std::array<size_t, Dimension> starter;
      for (int i = 0; i < Dimension; i++)
        starter[i] = 0;
      starter[slicePlane] = sliceNumber;

      //#pragma omp parallel for

      size_t startDepth = slicePlane == 0 ? 1 : 0;
      for (size_t i = 0; i < input->getDimension(startDepth); i++) {
        starter[startDepth] = i;
        recurse<Type, Dimension>(input, *result, slicePlane, sliceNumber, starter, startDepth + 1);
      }
      return result;
    }

  private:

    template <typename Type, int Dimension>
    static void recurse(MultiDimensionalArray<Type, Dimension>* input, MultiDimensionalArray<Type, Dimension - 1> & output,
      size_t deletedDimension, size_t sliceNumber, std::array<size_t, Dimension> currentCoordinate, size_t currentDimension) {
      if (deletedDimension == currentDimension) {
        currentCoordinate[deletedDimension] = sliceNumber;
        currentDimension++;
      }
      if (currentDimension == Dimension)
      {
        size_t inputTransform = input->transformA(currentCoordinate);
        std::array<size_t, Dimension - 1> outputCoord;
        size_t counter = 0;
        for (int i = 0; i < Dimension; i++) {
          if (deletedDimension == i) continue;
          outputCoord[counter] = currentCoordinate[i];
          counter++;
        }
        size_t outputTransform = output.transformA(outputCoord);
        output.get_linearRef(outputTransform) = input->get_linearRef(inputTransform);
      }
      else {
        for (size_t i = 0; i < input->getDimension(currentDimension); i++) {
          currentCoordinate[currentDimension] = i;
          recurse<Type, Dimension>(input, output, deletedDimension, sliceNumber, currentCoordinate, currentDimension + 1);
        }
      }
    }
  };
}