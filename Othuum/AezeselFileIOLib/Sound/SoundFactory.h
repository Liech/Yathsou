#pragma once

#include <string>
#include <map>
#include <memory>
#include <vector>

namespace Iyathuum {
  class Sound;
}

namespace Aezesel {
  class SoundFactory {
  public:
    SoundFactory(std::string folder);

    std::shared_ptr<Iyathuum::Sound> load(std::string bank, std::string name);
    std::vector<std::string>         getAllBanks();
    std::vector<std::string>         getAllSoundsInBank(std::string bank);

  private:
    void loadBank(std::string bankName);
    std::vector<std::shared_ptr<Iyathuum::Sound>> loadSounds(std::string bank);

    std::string _folder;

    struct bank {
      std::map<std::string, std::shared_ptr<Iyathuum::Sound>> sounds    ;
      std::vector<std::string>                                soundNames;
    };
    std::map<std::string, bank> _banks    ;
    std::vector<std::string>    _bankNames;
  };
}