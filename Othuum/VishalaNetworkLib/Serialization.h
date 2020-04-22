#pragma once

#include <map>
#include <string>

#include "json.hpp"
namespace Vishala {
  struct Serialization {
    virtual std::vector<unsigned char> toBinary() = 0;
    virtual void                       fromBinary(std::vector<unsigned char> data, size_t position) = 0;
    virtual nlohmann::json             toJson() = 0;
    virtual void                       fromJson(nlohmann::json) = 0;
            void                       toJsonFile(std::string filename);
            void                       fromJsonFile(std::string filename);
            void                       toBinFile(std::string filename);
            void                       fromBinFile(std::string filename); 

    template<typename type>
    type bin2val(std::vector<unsigned char>& data, size_t& position);
    template<typename type>
    void val2bin(std::vector<unsigned char>& data, type& value);

    template<typename type>
    std::vector<type> bin2vec(std::vector<unsigned char>& data, size_t& position) {
      std::vector<type> result;
      int size = bin2val(data, position);
      for (int i = 0; i < size; i++)
        result.push_back(bin2val<type>(data, position));
      return result;
    }

    template<typename type>
    void vec2bin(std::vector<unsigned char>& data, std::vector<type>& value) {
      int size = value.size();
      val2bin<int>(data, size);
      for (size_t i = 0; i < value.size(); i++)
        val2bin<type>(data, value[i]);
    }

    template<typename type, size_t SIZE>
    std::array<type, SIZE> bin2arr(std::vector<unsigned char>& data, size_t& position) {
      std::array<type, SIZE> result;
      for (int i = 0; i < SIZE; i++)
        result.push_back(bin2val<type>(data, position));
      return result;
    }

    template<typename type, size_t SIZE>
    void arr2bin(std::vector<unsigned char>& data, std::array<type, SIZE>& value) {
      for (size_t i = 0; i < SIZE; i++)
        val2bin<type>(data, value[i]);
    }
  };
}