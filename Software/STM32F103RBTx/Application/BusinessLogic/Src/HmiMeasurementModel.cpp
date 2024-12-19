

#include "BusinessLogic/Inc/HmiMeasurementModel.hpp"
#include "Device/Interfaces/IMeasurementReader.hpp"

namespace BusinessLogic
{

    HmiMeasurementModel::HmiMeasurementModel(Device::IMeasurementReader &_reader) : reader(_reader)
    {
    }

    int HmiMeasurementModel::dummyGetData()
    {
        return reader.getDataDummy();
    }
}
