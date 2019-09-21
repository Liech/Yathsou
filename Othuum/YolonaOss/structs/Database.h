#pragma once

#include <string>
#include <vector>
#include <memory>
#include <set>
#include <map>
#include <stdexcept>

//Objects can enter themselves here to get some sort of service by other objects
//Very modular, very good at obscuring code structures
//e.g. menu is registered as toplevel gui item
//menu system fuels all registered menus with input

template<typename BaseClass, typename TagType = std::string>
class Database {    
public:
private:
  
  //https://stackoverflow.com/questions/15858386/c-static-class-variable-without-cpp-file
  //inline has a meaning here
  static inline std::map<BaseClass, std::set<TagType>>          dataAndTags;
  static inline std::map<TagType, std::set<BaseClass>>          tagMap;
public:

  static void add(BaseClass object, const std::set<TagType> tags){
    if (dataAndTags.count(object))
      throw std::runtime_error("Already registered");
    dataAndTags[object] = tags;
    for (auto t : tags)
      tagMap[t].insert(object);
  }

  static void remove(BaseClass object) {
    if (!dataAndTags.count(object))
      throw std::runtime_error("Not registered here");
    std::set<TagType> tags = data[object];
    for (auto t : tags)
      tagMap[t].erase(object);
    dataAndTags.erase(object);
  }

  static std::set<BaseClass> getByTag(TagType tag) {
    if (tagMap.count(tag) == 0) 
      return {};
    return tagMap[tag];
  }
};