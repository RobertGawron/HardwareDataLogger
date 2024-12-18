

#include "BusinessLogic/Inc/HmiMeasurementModel.hpp"

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
