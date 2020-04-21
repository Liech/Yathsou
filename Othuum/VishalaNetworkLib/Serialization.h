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

  };
}