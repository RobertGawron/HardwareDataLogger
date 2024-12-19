

#include "BusinessLogic/Inc/HmiMeasurementModel.hpp"
#include "Device/Interfaces/IMeasurementReader.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"

#include <cstdint>

namespace BusinessLogic
{

    HmiMeasurementModel::HmiMeasurementModel(Device::IMeasurementReader &_reader) : reader(_reader)
    {
    }

    std::uint32_t HmiMeasurementModel::getLatestMeasurement(Device::MeasurementDeviceId source) const
    {
        return reader.getLatestMeasurement(source);
    }
}
