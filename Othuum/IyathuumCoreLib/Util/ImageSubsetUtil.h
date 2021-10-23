#pragma once

#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"
#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include <memory>
#include <vector>
#include "IyathuumCoreLib/Util/Geometry.h"

namespace Iyathuum {
  class ImageSubsetUtil {
  public:

    template<typename Type, size_t Dimension>
    static void drawCapsule(MultiDimensionalArray<Type, Dimension>* input, glm::vec<Dimension, float, glm::defaultp> start, glm::vec<Dimension, float, glm::defaultp> end, double radius, std::function<Type(double distance, Type val)> func) {
      std::array<size_t, Dimension> min;
      std::array<size_t, Dimension> size;
      for (size_t currentDimension = 0; currentDimension < Dimension; currentDimension++) {
        size_t minD = std::min(start[currentDimension], end[currentDimension]);
        size_t maxD = std::max(start[currentDimension], end[currentDimension]);
        if (radius > minD)
          minD = 0;
        else
          minD -= std::ceil(radius);
        maxD += std::ceil(radius);
        if (radius + maxD >= input->getDimension(currentDimension))
          maxD = input->getDimension(currentDimension) - 1;
        min[currentDimension] = minD;
        size[currentDimension] = maxD-minD;
      }

      input->applySubset(min, size, [start, end, radius, func](std::array<size_t, Dimension> position, Type& value) {
        std::array<double, Dimension> dPos;
        for (size_t i = 0; i < Dimension; i++) dPos[i] = position[i];
        double distance = Geometry<Dimension>::distancePoint2LineSegment(dPos,start,end);
        if (distance > radius)
          return;
        Type v = value;
        value = func(distance, v);
      });
    }

  public:

    //func is function that converts distance to actual value. E.g. for color interpolation
    //example for adding circle on doublefield
    //[](double distance, const Type old) {return old + distance; }
    template<typename Type, size_t Dimension>
    static void drawCircle(MultiDimensionalArray<Type, Dimension>* input, std::array<double, Dimension> center, double radius, std::function<Type(double distance, Type val)> func) {
      std::array<size_t, Dimension> start;
      std::array<size_t, Dimension> size;
      
      for (size_t i = 0; i < Dimension; i++) {
        double v = center[i] - radius;
        start[i] = v<0?0:std::floor(v);
        size[i] = std::ceil(radius * 2);
      }
      input->getRef(start) = 1;
      //input->applySubset(start,size, [center, radius,func](std::array<size_t,Dimension> position, Type& value) {
      //  double distance = 0;
      //  for (size_t i = 0; i < Dimension; i++)
      //    distance += ((double)center[i] - (double)position[i]) * ((double)center[i] - (double)position[i]);
      //  distance = std::sqrt(distance);
      //  if (distance > radius)
      //    return;
      //  Type v = value;
      //  value = func(distance, v);
      //});
    }

    template <typename Type, size_t Dimension>
    static std::unique_ptr<MultiDimensionalArray<Type, Dimension>> sub(MultiDimensionalArray<Type, Dimension>* input, std::array<size_t, Dimension> start, std::array<size_t, Dimension> size) {
      std::unique_ptr<MultiDimensionalArray<Type, Dimension>> result = std::make_unique<MultiDimensionalArray<Type, Dimension>>(size);
      result->apply([input,start](std::array<size_t, Dimension> resultPos, Type& val) {
        std::array<size_t, Dimension> pos = start;
        for (size_t i = 0; i < Dimension; i++)
          pos[i] += resultPos[i];
        val = input->getVal(pos);
      });
      return result;
    }

    template <typename Type, size_t Dimension>
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
        recurse_slice<Type, Dimension>(input, *result, slicePlane, sliceNumber, starter, startDepth + 1);
      }
      return result;
    }
  private:
    template <typename Type, size_t Dimension>
    static void recurse_slice(MultiDimensionalArray<Type, Dimension>* input, MultiDimensionalArray<Type, Dimension - 1> & output,
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
          recurse_slice<Type, Dimension>(input, output, deletedDimension, sliceNumber, currentCoordinate, currentDimension + 1);
        }
      }
    }
  };
}