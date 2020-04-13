#pragma once

#include <string>
#include <vector>
#include <memory>
#include <set>
#include <map>

//some sort of dependencie injection stuff
//needs at least c++ magic lvl 17 to understand
//i had lvl 5 when i wrote this
//google is cool
//https://gamedev.stackexchange.com/questions/17746/entity-component-systems-in-c-how-do-i-discover-types-and-construct-component/17759#17759

//be careful. register commands in static libraries are ignored. 
//use manual registrationcalls instead: Factory<BaseType>::Register<SpecificType>();
#define REGISTER(BaseType,SpecificType,Name, Tags)\
   static inline YolonaOss::Factory<BaseType>::Registrator<SpecificType> Registrator{ Name, Tags };
#define CLASSNAME(type) #type

namespace YolonaOss {
  class IFactory {
    virtual std::set<std::string> _getAll() = 0;
    virtual std::set<std::string> _getNamesByTag(std::string tag) = 0;
  };

  template<typename BaseClass>
  class Factory : public IFactory {    
  public:
    template <typename T>
    class Registrator {
    public:
      Registrator(const std::string name, const std::set<std::string> tags) {
        Factory<BaseClass>::Register(name, tags, &Registrator<T>::create);
      }
    private:
      static std::shared_ptr<BaseClass> create() {
        return std::static_pointer_cast<BaseClass>(std::make_shared<T>());
      }
    };
    //function pointer with the name InstantiatorFun. Returns a shared pointer. To be exact the function above this comment
    typedef std::shared_ptr<BaseClass >(*InstantiatorFun)(void);
  private:

    //https://stackoverflow.com/questions/15858386/c-static-class-variable-without-cpp-file
    //inline has a meaning here
    static inline std::map<std::string, Factory<BaseClass>::InstantiatorFun>      registry;
    static inline std::map<std::string, std::set<std::string>>                    tagMap;

    template<typename T> void Register(const std::string name, const std::set<std::string> tags) {
      Factory<BaseType>::Registrator<T> registerMe(name, tags);
    }

    static void Register(const std::string name, const std::set<std::string> tags, Factory<BaseClass>::InstantiatorFun func) {
      registry[name] = func;
      for (auto t : tags)
        tagMap[t].insert(name);
    }



  public:
    static std::set<std::string> getAll() {
      std::set<std::string> result;
      for (std::pair<std::string, Factory<BaseClass>::InstantiatorFun> f : Factory<BaseClass>::registry)
        result.insert(f.first);
      return result;
    }

    static std::set<std::string> getNamesByTag(std::string tag) {
      if (tagMap.count(tag) == 0)
        return {};
      return tagMap[tag];
    }
    static std::shared_ptr<BaseClass> make(std::string name) {
      return registry[name]();
    }

    std::set<std::string> _getAll() {
      return Factory<BaseClass>::getAll();
    }

    std::set<std::string> _getNamesByTag(std::string tag) {
      return Factory<BaseClass>::getNamesByTag(tag);
    }
  };
}