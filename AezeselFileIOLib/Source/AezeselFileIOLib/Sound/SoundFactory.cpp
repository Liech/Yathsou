#include "SoundFactory.h"

#include <filesystem>
#include <set>

#include "IyathuumCoreLib/BaseTypes/Sound.h"

#include "Sound/XSB.h"
#include "Sound/XWB.h"


namespace Aezesel {
  SoundFactory::SoundFactory(std::string foldername) {
    _folder = foldername;

    std::vector<std::string> availableBanks;
    for (const auto& p : std::filesystem::recursive_directory_iterator(foldername)) {
      if (p.path().extension() == ".xwb") {
        std::string name = p.path().string().substr(foldername.size() + 1);
        name = name.substr(0, name.size() - 4);
        _bankNames.push_back(name);
      }
    }
  }

  bool SoundFactory::hasSound(const std::string& bank, const std::string& name) {    
    std::set<std::string> banks(getAllBanks().begin(), getAllBanks().end());
    if (!banks.contains(bank))
      return false;    
    loadBank(bank);
    return _banks[bank].sounds.count(name) != 0;
  }

  std::shared_ptr<Iyathuum::Sound> SoundFactory::load(const std::string& bank, const std::string& name) {
    loadBank(bank);
    return _banks[bank].sounds[name];
  }

  const std::vector<std::string>& SoundFactory::getAllBanks() const{
    return _bankNames;
  }

  std::vector<std::string> SoundFactory::getAllSoundsInBank(const std::string& bank) {
    loadBank(bank);
    return _banks[bank].soundNames;
  }

  void SoundFactory::loadBank(const std::string& bankName) {
    if (_banks.count(bankName) != 0)
      return;
    
    Aezesel::XSB xsb;
    std::vector<std::string> names = xsb.load(_folder + "\\" + bankName + ".xsb");
    auto sounds = loadSounds(bankName);
    while(names.size() > sounds.size())
      names.erase(names.begin() + names.size() - 1);
    for (int i = names.size(); i < sounds.size(); i++)
      names.push_back(std::to_string(i));

    
    _banks[bankName] = bank{};
    auto& b = _banks[bankName];

    b.soundNames = names;
    for (int i = 0; i < sounds.size(); i++)
      b.sounds[names[i]] = sounds[i];
  }

  std::vector<std::shared_ptr<Iyathuum::Sound>> SoundFactory::loadSounds(const std::string& bank) {
    std::vector<std::shared_ptr<Iyathuum::Sound>> result;
    Aezesel::XWB xwbReader;
    auto sounds = xwbReader.load(_folder + "\\" + bank + ".xwb");
    
    for (auto& x : sounds)
      result.push_back(std::move(x));
    return result;
  }
}