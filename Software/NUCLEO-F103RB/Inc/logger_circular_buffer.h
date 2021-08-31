#ifndef LOGGER_CIRCULAR_BUFFER_H_
#define LOGGER_CIRCULAR_BUFFER_H_

#include <stdbool.h>
#include "logger_measurement.h"

typedef enum Logger_CircularBuffer_GetElementStatus_t
{
    LOGGER_CIRCULAR_BUFFER_GETELEMENT_OK = 0
    , LOGGER_CIRCULAR_BUFFER_GETELEMENT_INDEX_OUT_OF_RANGE
} Logger_CircularBuffer_GetElementStatus_t;

typedef enum Logger_CircularBuffer_GetMinMaxElementStatus_t
{
    LOGGER_CIRCULAR_BUFFER_GETMINMAXELEMENT_OK = 0
    , LOGGER_CIRCULAR_BUFFER_GETMINMAXELEMENT_NO_MEASSUREMENTS
} Logger_CircularBuffer_GetMinMaxElementStatus_t;

void Logger_CircularBuffer_Init();

uint16_t Logger_CircularBuffer_GetElementCount();

void Logger_CircularBuffer_Insert(GMMeasurement_Value_t element);

Logger_CircularBuffer_GetElementStatus_t Logger_CircularBuffer_GetElement(GMMeasurement_Value_t *element, uint16_t index);

Logger_CircularBuffer_GetMinMaxElementStatus_t Logger_CircularBuffer_GetMinMaxElement(GMMeasurement_Value_t* minElement, GMMeasurement_Value_t* maxElement);

#endif
