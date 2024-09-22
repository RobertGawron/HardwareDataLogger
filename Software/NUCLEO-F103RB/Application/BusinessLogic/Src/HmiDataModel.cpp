#include "HmiDataModel.hpp"

namespace BusinessLogic
{
  HmiDataModel::HmiDataModel(Device::DisplayBrightnessRegulator &_brightnessRegulator)
      : brightnessRegulator(_brightnessRegulator)
  {
  }

  bool HmiDataModel::initialize()
  {
    brightnessRegulator.init();
    return true;
  }

  bool HmiDataModel::start()
  {
    return true;
  }

  bool HmiDataModel::stop()
  {
    return true;
  }

  bool HmiDataModel::tick()
  {
    return true;
  }
}
