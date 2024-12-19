

#include "BusinessLogic/Inc/HmiMeasurementModel.hpp"
#include "Device/Interfaces/IMeasurementReader.hpp"

namespace BusinessLogic
{

    HmiMeasurementModel::HmiMeasurementModel(Device::IMeasurementReader &_reader) : reader(_reader)
    {
    }

    std::uint32_t HmiMeasurementModel::getLatestMeasurement(Device::MeasurementSource source) const
    {
        return reader.getLatestMeasurement(source);
    }
}
