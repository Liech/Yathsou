#pragma once

namespace vr
{
  class IVRSystem;
}

//https://github.com/osudrl/CassieVrControls/wiki/OpenVR-Quick-Start
namespace Ahwassa {
  class VR {
  public:
    VR();
    ~VR();

    void update();

  private:
    vr::IVRSystem* vr_pointer = nullptr;
  };
}