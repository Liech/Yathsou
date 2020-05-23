#pragma once

#include <memory>

#include "YolonaOss/OpenGL/Drawable.h"

#include "DialogPage.h"
#include "ClientConfiguration.h"
#include "YolonaOss/Drawables/Widgets/Label.h"

enum class ErrorPageStatus {
  Pending, Back
};

class ErrorPage : public YolonaOss::GL::Drawable {
public:
  ErrorPage(std::shared_ptr<ClientConfiguration> config);

  virtual void draw()                                  override;
  virtual void load(YolonaOss::GL::DrawSpecification*) override;
  void setVisible(bool visible);
  void reset();
  void setMessage(std::string desc, std::string title = "ERROR");

  ErrorPageStatus getStatus();
private:
  void goBack();

  std::unique_ptr<DialogPage>                _page;
  std::shared_ptr<YolonaOss::Widgets::Label> _desc;
  std::shared_ptr<YolonaOss::Widgets::Label> _title;
  
  ErrorPageStatus                      _status = ErrorPageStatus::Pending;
  std::shared_ptr<ClientConfiguration> _config;
};