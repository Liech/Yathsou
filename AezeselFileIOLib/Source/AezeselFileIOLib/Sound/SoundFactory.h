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

    bool                             hasSound(const std::string& bank, const std::string& name);
    std::shared_ptr<Iyathuum::Sound> load(const std::string& bank, const std::string& name);
    const std::vector<std::string>&  getAllBanks() const;
    std::vector<std::string>         getAllSoundsInBank(const std::string& bank);
  private:
    void loadBank(const std::string& bankName);
    std::vector<std::shared_ptr<Iyathuum::Sound>> loadSounds(const std::string& bank);

    std::string _folder;

    struct bank {
      std::map<std::string, std::shared_ptr<Iyathuum::Sound>> sounds    ;
      std::vector<std::string>                                soundNames;
    };
    std::map<std::string, bank> _banks    ;
    std::vector<std::string>    _bankNames;
  };
}