#pragma once

#include <string>
#include <vector>
#include <memory>
#include <set>
#include <map>
#include <stdexcept>
#include <functional>

//Objects can enter themselves here to get some sort of service by other objects
//Very modular, very good at obscuring code structures
//e.g. menu is registered as toplevel gui item
//menu system fuels all registered menus with input

namespace YolonaOss {
  class DatabaseTerminator {
  public:
    static inline std::vector<std::function<void()>> toTerminate;
    static void terminateAll() {
      for (auto t : toTerminate)
        t();
    }
  };

  template<typename BaseClass, typename TagType = std::string>
  class Database {
  public:
  private:

    //https://stackoverflow.com/questions/15858386/c-static-class-variable-without-cpp-file
    //inline has a meaning here
    static inline std::map<BaseClass, std::set<TagType>>          dataAndTags;
    static inline std::map<TagType, std::set<BaseClass>>          tagMap;
    static inline bool                                            addedToTerminator;
  public:

    static void add(BaseClass object, const std::set<TagType> tags) {
      if (dataAndTags.count(object))
        throw std::runtime_error("Already registered");
      if (!addedToTerminator) {
        addedToTerminator = true;
        DatabaseTerminator::toTerminate.push_back(terminate);
      }

      dataAndTags[object] = tags;
      for (auto t : tags)
        tagMap[t].insert(object);
    }

    static void remove(BaseClass object) {
      if (!dataAndTags.count(object))
        throw std::runtime_error("Not registered here");
      std::set<TagType> tags = dataAndTags[object];
      for (auto t : tags)
        tagMap[t].erase(object);
      dataAndTags.erase(object);
    }

    static std::set<BaseClass> getByTag(TagType tag) {
      if (tagMap.count(tag) == 0)
        return {};
      return tagMap[tag];
    }

    static void terminate() {
      dataAndTags.clear();
      tagMap.clear();
    }

  };
}