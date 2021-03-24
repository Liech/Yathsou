#pragma once

#include "Command.h"
//#include "IyathuumCoreLib/BaseTypes/Keys.h"

namespace Uyanah {
  namespace Commands {
    class KeyCmd : public Command {
    public:
      //virtual void apply(Scene&) override;
      virtual const std::string Name() const override { return "Key"; }

      //Iyathuum::Key       key      = Iyathuum::Key::KEY_SPACE;
      //Iyathuum::KeyStatus status   = Iyathuum::KeyStatus::PRESS;
      size_t              targetID = 0;

      virtual Vishala::BinaryPackage toBinary()                                  override;
      virtual void                   fromBinary(Vishala::BinaryPackage& Package) override;
      virtual nlohmann::json         toJson()                                    override;
      virtual void                   fromJson(nlohmann::json)                    override;

    };
  }
}