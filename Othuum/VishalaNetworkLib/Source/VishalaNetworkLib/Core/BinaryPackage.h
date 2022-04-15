#pragma once

#include <vector>
#include <set>
#include <map>
#include <nlohmann/json.hpp>

namespace Vishala {
  struct BinaryPackage {
    std::vector<unsigned char> data;
    size_t                     position = 0;


    static BinaryPackage createDelta(const BinaryPackage& oldData, const BinaryPackage& newData);
    static BinaryPackage applyDelta(const BinaryPackage& oldData, BinaryPackage& delta);
    BinaryPackage compress();
    BinaryPackage decompress();

    void add(BinaryPackage p);

    template<typename type>
    static type bin2val(BinaryPackage& data);
    template<typename type>
    static void val2bin(BinaryPackage& data,const type& value);

    template<typename type>
    static std::vector<type> bin2vec(BinaryPackage& data) {
      std::vector<type> result;
      int size = bin2val(data);
      for (int i = 0; i < size; i++)
        result.push_back(bin2val<type>(data));
      return result;
    }

    template<typename type>
    static void vec2bin(BinaryPackage& data, const std::vector<type>& value) {
      int size = value.size();
      val2bin<int>(data, size);
      for (size_t i = 0; i < value.size(); i++)
        val2bin<type>(data, value[i]);
    }

    template<typename type>
    static std::set<type> bin2set(BinaryPackage& data) {
      std::set<type> result;
      int size = bin2val<int>(data);
      for (int i = 0; i < size; i++)
        result.insert(bin2val<type>(data));
      return result;
    }

    template<typename type>
    static void set2bin(BinaryPackage& data,const std::set<type>& value) {
      int size = value.size();
      val2bin<int>(data, size);
      for (auto v : value)
        val2bin<type>(data, v);
    }

    template<typename type1, typename type2>
    static std::map<type1, type2> bin2map(BinaryPackage& data) {
      std::map<type1, type2> result;
      int size = bin2val<int>(data);
      for (int i = 0; i < size; i++)
        result[bin2val<type1>(data)] = bin2val<type2>(data);
      return result;
    }

    template<typename type1, typename type2>
    static void map2bin(BinaryPackage& data,const std::map<type1, type2>& value) {
      int size = value.size();
      val2bin<int>(data, size);
      for (std::pair<type1, type2> v : value) {
        val2bin<type1>(data, v.first);
        val2bin<type2>(data, v.second);
      }
    }

    template<typename type, size_t SIZE>
    static std::array<type, SIZE> bin2arr(BinaryPackage& data) {
      std::array<type, SIZE> result;
      for (int i = 0; i < SIZE; i++)
        result[i] = bin2val<type>(data);
      return result;
    }

    template<typename type, size_t SIZE>
    static void arr2bin(BinaryPackage& data,const std::array<type, SIZE>& value) {
      for (size_t i = 0; i < SIZE; i++)
        val2bin<type>(data, value[i]);
    }
  };
}