#pragma once

#include <map>
#include <string>
#include <set>

#include "VishalaNetworkLib/lib/json.hpp"

#include "BinaryPackage.h"

namespace Vishala {
  struct Serialization {
    virtual BinaryPackage              toBinary() = 0;
    virtual void                       fromBinary(BinaryPackage& Package) = 0;
    virtual nlohmann::json             toJson() = 0;
    virtual void                       fromJson(nlohmann::json) = 0;
            void                       toJsonFile(std::string filename);
            void                       fromJsonFile(std::string filename);
            void                       toBinFile(std::string filename);
            void                       fromBinFile(std::string filename); 

    template<typename type>
    type bin2val(BinaryPackage& data);
    template<typename type>
    void val2bin(BinaryPackage& data, type& value);

    template<typename type>
    std::vector<type> bin2vec(BinaryPackage& data) {
      std::vector<type> result;
      int size = bin2val(data);
      for (int i = 0; i < size; i++)
        result.push_back(bin2val<type>(data));
      return result;
    }

    template<typename type>
    void vec2bin(BinaryPackage& data, std::vector<type>& value) {
      int size = value.size();
      val2bin<int>(data, size);
      for (size_t i = 0; i < value.size(); i++)
        val2bin<type>(data, value[i]);
    }

    template<typename type>
    std::set<type> bin2set(BinaryPackage& data) {
      std::set<type> result;
      int size = bin2val<int>(data);
      for (int i = 0; i < size; i++)
        result.insert(bin2val<type>(data));
      return result;
    }

    template<typename type>
    void set2bin(BinaryPackage& data, std::set<type>& value) {
      int size = value.size();
      val2bin<int>(data, size);
      for (auto v : value)
        val2bin<type>(data, v);
    }

    template<typename type1,typename type2>
    std::map<type1,type2> bin2map(BinaryPackage& data) {
      std::map<type1,type2> result;
      int size = bin2val<int>(data);
      for (int i = 0; i < size; i++)
        result[bin2val<type1>(data)] = bin2val<type2>(data);
      return result;
    }

    template<typename type1, typename type2>
    void map2bin(BinaryPackage& data, std::map<type1,type2>& value) {
      int size = value.size();
      val2bin<int>(data, size);
      for (std::pair<type1,type2> v : value) {
        val2bin<type1>(data, v.first );
        val2bin<type2>(data, v.second);
      }
    }

    template<typename type, size_t SIZE>
    std::array<type, SIZE> bin2arr(BinaryPackage& data) {
      std::array<type, SIZE> result;
      for (int i = 0; i < SIZE; i++)
        result[i] = bin2val<type>(data);
      return result;
    }

    template<typename type, size_t SIZE>
    void arr2bin(BinaryPackage& data, std::array<type, SIZE>& value) {
      for (size_t i = 0; i < SIZE; i++)
        val2bin<type>(data, value[i]);
    }
  };
}