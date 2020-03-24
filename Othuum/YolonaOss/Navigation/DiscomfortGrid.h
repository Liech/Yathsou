#pragma once

#include "structs/MultiDimensionalArray.h"
#include "DiscomfortArea.h"
#include <set>
#include "Util/Geometry.h"

namespace YolonaOss {
  template<size_t Dimension>
  class DiscomfortGrid {
  public:
    DiscomfortGrid(std::array<size_t, Dimension> dimension, double scale) : _discomfortField(dimension) {
      _discomfortField.fill(0);
      _scale = scale;
    }

    std::array<double, Dimension> getGradient(std::array<double, Dimension> position) {
      vec scaled = _scale * currentPosition;
      std::array<size_t, Dimension> index;
      for (int i = 0; i < Dimension; i++)
        index[i] = scaled[i] > 0 ? (size_t)scaled[i] : 0;
      return getDirectionSuggestion_recurse(index);
    }

    double getDiscomfort(std::array<double, Dimension> position) {
      std::array<size_t, Dimension> index;
      for (size_t i = 0; i < Dimension; i++)
        index[i] = (double)position[i] * _scale;
      return _discomfortField.getVal(position);
    }

    void addDiscomfortArea(std::shared_ptr<DiscomfortArea<Dimension>> area) {
      _discomfortAreas.insert(area);
    }

    void removeDiscomfortArea(std::shared_ptr<DiscomfortArea<Dimension>> area) {
      _discomfortAreas.erase(area);
    }

    void updateDiscomfort() {
      _discomfortField.fill(0);
      for (auto area : _discomfortAreas) {
        area->addDiscomfort(&_discomfortField, _scale);
      }
    }

  private:
    std::array<double, Dimension> getDirectionSuggestion_recurse(std::array<size_t, Dimension> position, std::array<double, Dimension> dir, size_t currentDimension = Dimension - 1) {
      std::array<double, Dimension> result;
      for (size_t i = 0; i < Dimension; i++)
        result[i] = 0;
      for (int i = -1; i <= 1; i++) {
        auto newP = position;
        if ((!(newP[currentDimension] == 0 && i == -1)) && (!(newP[currentDimension] == _discomfortMap->getDimension(currentDimension) - 1 && i == 1)))
          newP[currentDimension] += i;
        dir[currentDimension] = i;
        if (currentDimension != 0)
          result += getDirectionSuggestion_recurse(newP, dir, currentDimension - 1);
        else {
          float val = _discomfortField.getVal(newP);
          result = GeometryND<Dimension>::Add(result, GeometryND<Dimension>::Multiply(dir, -val));
        }
      }
      return result;
    }


    double                                      _scale;
    MultiDimensionalArray<double, Dimension>    _discomfortField;
    std::set<std::shared_ptr<DiscomfortArea<Dimension>>>   _discomfortAreas;
  };
}