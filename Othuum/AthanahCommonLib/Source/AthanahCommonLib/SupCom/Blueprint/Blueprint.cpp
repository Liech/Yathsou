#include "Blueprint.h"
#include "BlueprintGeneral.h"
#include "BlueprintDisplay.h"
#include "BlueprintPhysic.h"
#include <iostream>

namespace Athanah {
  Blueprint::Blueprint(const std::string id, const nlohmann::json& input) {
    std::cout << id << std::endl;
    if (input.find("Description") != input.end()) {
      _description = input["Description"];
      _description = _description.substr(_description.find_first_of('>')+1);
    }
    else if (input.find("Description") != input.end())
      _description = id;
    
    if (input.find("StrategicIconName") != input.end()) {
      _strategicIcon = input["StrategicIconName"];
    }
    else if (input.find("StrategicIconName") != input.end())
      _strategicIcon = "";

    readSize(input);
    _general = std::make_shared<BlueprintGeneral>(input["General"]);
    _display = std::make_shared<BlueprintDisplay>(input["Display"]);
    _physic  = std::make_unique<BlueprintPhysic >(input["Physics"]);
    _id = id;

    _raw = input;
  }

  Blueprint::Blueprint(const std::string id) {
    _description = id;
    _id = id;
    _general = std::make_shared<BlueprintGeneral>();
    _display = std::make_shared<BlueprintDisplay>();
  }

  std::string Blueprint::strategicIcon() const {
    return _strategicIcon;
  }

  std::string Blueprint::description() const {
    return _description;
  }

  BlueprintGeneral& Blueprint::general() const {
    return *_general;
  }

  BlueprintDisplay& Blueprint::display() const {
    return *_display;
  }

  BlueprintPhysic& Blueprint::physic() const {
    return *_physic;
  }

  nlohmann::json Blueprint::getRaw() const {
    return _raw;
  }

  glm::vec3 Blueprint::size() const {
    return _size;
  }

  glm::vec3 Blueprint::selectionSize() const {
    return _selectionSize;
  }

  void Blueprint::readSize(const nlohmann::json& input) {
    if (input.find("SizeX") != input.end())
      _size[0] = input["SizeX"];
    else
      _size[0] = 1;

    if (input.find("SizeY") != input.end())
      _size[1] = input["SizeY"];
    else
      _size[1] = 1;

    if (input.find("SizeZ") != input.end())
      _size[2] = input["SizeZ"];
    else
      _size[2] = 1;

    if (input.find("SelectionSizeX") != input.end())
      _selectionSize[0] = input["SelectionSizeX"];
    else
      _selectionSize[0] = 1;

    if (input.find("SelectionSizeY") != input.end())
      _selectionSize[1] = input["SelectionSizeY"];
    else
      _selectionSize[1] = 1;

    if (input.find("SelectionSizeZ") != input.end())
      _selectionSize[2] = input["SelectionSizeZ"];
    else
      _selectionSize[2] = 1;
  }
}