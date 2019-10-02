#pragma once

#include <assert.h>
#include <array>
#include <vector>
#include <functional>
#include <memory>
#include <iomanip>


namespace YolonaOss {
  enum memoryLayout {
    Reversed, Normal
  };

  template <typename Type, size_t Dimension, memoryLayout Layout = Normal, class = std::make_index_sequence<Dimension>>
  class MultiDimensionalArray;


  //Just takes care of the data storage. Should not contain any comfort features to keep it clean
  //This should be done by helper classes like matrix or slicer
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
    }

    MultiDimensionalArray(std::vector<size_t> dim) {
      assert(dim.size() == Dimension);
      _size = 1;
      for (int i = 0; i < dim.size(); i++) {
        _dimension[i] = dim[i];
        _size *= dim[i];
      }
      _data.resize(getSize());
    }

    MultiDimensionalArray(const  MultiDimensionalArray<Type, Dimension>& copy) {
      _size = copy._size;
      _data = new Type[getSize()];
      std::memcpy(_data.data(), copy._data.data(), (sizeof _data) * getSize());
      std::memcpy(&_dimension, &copy._dimension, (sizeof _dimension) * Dimension);
    }


    virtual ~MultiDimensionalArray() {
    };

    Type& getRef(input_<Is>... vals) { return _data[transform(vals...)]; }
    Type  getVal(input_<Is>... vals) const { return _data[transform(vals...)]; }


    Type& getRef(std::array<size_t, Dimension> vals) { return _data[transformA(vals)]; }
    Type  getVal(std::array<size_t, Dimension> vals) { return _data[transformA(vals)]; }

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
      int chunks = (int)getSize() / chunkSize;
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
      int chunks = (int)getSize() / chunkSize;
      if (chunks == 0) chunks = 1;
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
      int chunks = (int)getSize() / chunkSize;
      if (chunks == 0) chunks = 1;
#pragma omp parallel for
      for (int chunk = 0; chunk < chunks; chunk++) {
        size_t min = chunk * chunkSize;
        size_t max = (chunk + 1) * chunkSize;
        for (size_t i = min; i < max && i < getSize(); i++)
          func(transformToCoordiante(i), get_linearRef(i));
      }
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