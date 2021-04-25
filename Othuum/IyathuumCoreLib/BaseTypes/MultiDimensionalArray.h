#pragma once

#include <assert.h>
#include <array>
#include <vector>
#include <functional>
#include <memory>
#include <iomanip>
#include <numeric>
#include <execution>
#include <iostream>

namespace Iyathuum {
  enum memoryLayout {
    Reversed, Normal
  };

  template <typename Type, size_t Dimension, memoryLayout Layout = Normal, class = std::make_index_sequence<Dimension>>
  class MultiDimensionalArray;


  //Just takes care of the data storage. Should not contain any comfort features
  //This should be done by helper classes
  template <typename Type, size_t Dimension, memoryLayout Layout, size_t... Is>
  class MultiDimensionalArray<Type, Dimension, Layout, std::index_sequence<Is...> >
  {
  private:
    template <size_t >
    using input_ = size_t;
  public:
    MultiDimensionalArray(input_<Is>... vals)
    {
      _size = 1;
      size_t counter = 0;
      for (auto&& x : { vals... }) {
        _dimension[counter] = x;
        _size *= x;
        counter++;
      }
      _data.resize(getSize());
      assert(getSize() != 0);
    }

    MultiDimensionalArray(std::array<size_t,Dimension> dim) {
      assert(dim.size() == Dimension);
      _size = 1;
      for (int i = 0; i < Dimension; i++) {
        _dimension[i] = dim[i];
        _size *= dim[i];
      }
      _data.resize(getSize());
      assert(getSize() != 0);
    }

    MultiDimensionalArray(std::vector<size_t> dim) {
      assert(dim.size() == Dimension);
      _size = 1;
      for (int i = 0; i < dim.size(); i++) {
        _dimension[i] = dim[i];
        _size *= dim[i];
      }
      _data.resize(getSize());
      assert(getSize() != 0);
    }

    MultiDimensionalArray(const  MultiDimensionalArray<Type, Dimension>& copy) {
      _size = copy._size;
      _data.resize(getSize());
      for(size_t i = 0;i < Dimension;i++)
        _dimension[i] = copy._dimension[i];
      std::memcpy(_data.data(), copy._data.data(), (sizeof _data) * getSize());
      std::memcpy(&_dimension, &copy._dimension, (sizeof _dimension) * Dimension);
      assert(getSize() != 0);
    }


    virtual ~MultiDimensionalArray() {
    };

    Type& getRef(input_<Is>... vals) { return _data[transform(vals...)]; }
    Type  getVal(input_<Is>... vals) const { return _data[transform(vals...)]; }


    Type& getRef(std::array<size_t, Dimension> vals) { 
      auto pos = transformA(vals);
      return _data[pos]; 
    }

    Type  getVal(std::array<size_t, Dimension> vals) {
      auto pos = transformA(vals);
      return _data[pos];     
    }

    Type& get_linearRef(size_t pos) {
      return _data[pos];
    }
    Type get_linearVal(size_t pos) const {
      return _data[pos];
    }
    void set_linear(size_t pos, const Type val) {
      _data[pos] = val;
    }

    void fill(Type t) {
      apply([t](size_t pos, Type& a) {a = t; });
      //for (size_t i = 0; i < _size; i++) {
      //  get(i) = t;
      //}
    }

    size_t transform(input_<Is>... vals) const {  //use size_t
      size_t result = 0;
      size_t productSum = 1;
      std::array<size_t, sizeof...(vals)> list = { vals... };
      if constexpr (Reversed == Layout) {
        for (int i = (sizeof...(vals)) - 1; i >= 0; i--) {
          result += list[i] * productSum;
          productSum *= _dimension[i];
        }
      }
      else
      {
        for (int i = 0; i < (sizeof...(vals)); i++) {
          result += list[i] * productSum;
          productSum *= _dimension[i];
        }
      }
      return result;
    }

    size_t transformA(std::array<size_t, Dimension> coord) {
      size_t result = 0;
      size_t productSum = 1;
      if constexpr (Reversed == Layout) {
        for (int i = Dimension - 1; i >= 0; i--) {
          result += coord[i] * productSum;
          productSum *= _dimension[i];
        }
      }
      else
      {
        for (int i = 0; i < Dimension; i++) {
          result += coord[i] * productSum;
          productSum *= _dimension[i];
        }
      }
      return result;
    }

    std::array<size_t, Dimension> transformToCoordiante(size_t input) {
      //Inverse of transformA
      size_t pos = input;
      std::array<size_t, Dimension> result;
      if constexpr (Reversed == Layout) {
        for (size_t i = Dimension - 1; i >= 0; i--) {
          result[i] = pos % _dimension[i];
          pos -= result[i];
          pos /= _dimension[i];
        }
      }
      else {
        for (size_t i = 0; i < Dimension; i++) {
          result[i] = pos % _dimension[i];
          pos -= result[i];
          pos /= _dimension[i];
        }

      }
      return result;
    }

    size_t getSize() const {
      return _size;
    }

    std::vector<size_t> getDimensionVector() const {
      std::vector<size_t> result;
      for (int i = 0; i < Dimension; i++)
        result.push_back(getDimension(i));
      return result;
    }

    size_t getDimension(size_t dimension) const {
      assert(dimension >= 0);
      assert(dimension < Dimension);
      return _dimension[dimension];
    }

    template<typename Type2>
    std::shared_ptr<MultiDimensionalArray<Type2, Dimension>> map(std::function<Type2(Type const&)> func) {
      std::vector<size_t> dimension;
      for (size_t i = 0; i < Dimension; i++) dimension.push_back(_dimension[i]);
      std::shared_ptr<MultiDimensionalArray<Type2, Dimension>> result = std::make_shared<MultiDimensionalArray<Type2, Dimension>>(dimension);
      int chunkSize = 1000;
      int chunks = ((int)getSize() / chunkSize) +1;
#pragma omp parallel for
      for (int chunk = 0; chunk < chunks; chunk++) {
        size_t min = chunk * chunkSize;
        size_t max = (chunk + 1) * chunkSize;
        for (size_t i = min; i < max && i < getSize(); i++) {
          Type2 c = func(this->get_linearVal(i));
          result->set_linear(i,c);
        }
      }
      return result;
    }

    void apply(std::function<void(size_t, Type&)> func) {
      int chunkSize = 1000;
      int chunks = ((int)getSize() / chunkSize)+1;
      //if (chunks == 0) chunks = 1;
#pragma omp parallel for
      for (int chunk = 0; chunk < chunks; chunk++) {
        size_t min = chunk * chunkSize;
        size_t max = (chunk + 1) * chunkSize;
        if (max > getSize())
          max = getSize();
        for (size_t i = min; i < max; i++)
          func(i, get_linearRef(i));
      }
    }

    void apply(std::function<void(std::array<size_t, Dimension>, Type&)> func) {
      int chunkSize = 1000;
      int chunks = ((int)getSize() / chunkSize)+1;
      //if (chunks == 0) chunks = 1;
#pragma omp parallel for
      for (int chunk = 0; chunk < chunks; chunk++) {
        size_t min = chunk * chunkSize;
        size_t max = (chunk + 1) * chunkSize;
        for (size_t i = min; i < max && i < getSize(); i++)
          func(transformToCoordiante(i), get_linearRef(i));
      }
    }

    //on subset
    void applySubset(std::array<size_t, Dimension> start, std::array<size_t, Dimension> size, std::function<void(std::array<size_t, Dimension>, Type&)> func) {
      for (size_t i = 0; i < Dimension; i++)
        if (start[i] + size[i] >= getDimension(i)) 
          size[i] = getDimension(i) - start[i] - 1;

      size_t xSize;
      size_t startDimension;
      if constexpr (Layout == Reversed)
        startDimension = Dimension - 1;
      else 
        startDimension = 0;
      xSize = size[startDimension];

      #pragma omp parallel for
      for (int64_t x = 0; x < xSize; x++) {
        std::array<size_t, Dimension> currentPosition = start;
        currentPosition[startDimension] = start[startDimension] + x;
        apply_recursive(start, size, func, currentPosition, startDimension);
      }
    }
    private:
    void apply_recursive(const std::array<size_t, Dimension> start, const std::array<size_t, Dimension> size, std::function<void(std::array<size_t, Dimension>, Type&)> func, std::array<size_t, Dimension> currentPosition, size_t currentDimension) {
      if ((Layout == Reversed && currentDimension == 0) || (Layout == Normal && currentDimension == Dimension - 1)) {
        for (int64_t i = 0; i < size[currentDimension]; i++) {
          std::array<size_t, Dimension> pos = currentPosition;
          pos[currentDimension] += i;
          size_t index = transformA(pos);
          func(pos, get_linearRef(index));
        }
      }
      else
      {
        for (int64_t i = 0; i < size[currentDimension]; i++) {
          std::array<size_t, Dimension> pos = currentPosition;
          pos[currentDimension] += i;
          if constexpr (Layout == Reversed)
            apply_recursive(start, size, func, pos, currentDimension - 1);
          else
            apply_recursive(start, size, func, pos, currentDimension + 1);
        }
      }
    }
    public:

    Type reduce(Type startVal, std::function<Type(const Type, const Type)> binOp) {
      std::reduce(std::execution::par, _data.begin(), _data.end(), startVal,binOp);
    }

    void write() {
      const int numWidth = 14;
      const char separator = ' ';

      assert(Dimension == 2);
      for (size_t y = 0; y < getDimension(1); y++) {
        for (size_t x = 0; x < getDimension(0); x++)
          std::cout << std::left << std::setw(numWidth) << std::setfill(separator) << getVal(x, y);
        std::cout << std::endl;
      }

    }

    Type* data() { return _data.data(); }
    std::vector<Type>& vector() { return _data; }

  private:
    std::vector<Type> _data;
    size_t            _dimension[Dimension];
    size_t            _size;

    Type& get(size_t position) {
      assert(position >= 0);
      assert(position <= getSize());
      return _data[position];
    }
  };
}