#pragma once

#include <memory>

#include "YolonaOss/OpenGL/Drawable.h"

#include "DialogPage.h"
#include "ClientConfiguration.h"

enum class OptionsPageStatus {
  Pending, Back
};

class OptionsPage : public YolonaOss::GL::Drawable {
public:
  OptionsPage(std::shared_ptr<ClientConfiguration> config);

  virtual void draw()                                  override;
  virtual void load(YolonaOss::GL::DrawSpecification*) override;
  void setVisible(bool visible);
  void reset();

  OptionsPageStatus getStatus();
private:
  void goBack();

  std::unique_ptr<DialogPage> _page;
  
  OptionsPageStatus                    _status = OptionsPageStatus::Pending;
  std::shared_ptr<ClientConfiguration> _config;
};