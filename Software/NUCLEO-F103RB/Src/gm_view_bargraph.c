#include <stdlib.h>
#include <string.h>
#include "gm_view_bargraph.h"
#include "gm_display_hw.h"
#include "gm_display_labels.h"
#include "logger_measurement.h"
#include "logger_circular_buffer.h"


#define LABEL_DOSE_LENGTH 16U
char labelDose[LABEL_DOSE_LENGTH];

// TOD move it somewhere
static const uint16_t DisplayUpdater_LCDHeightBlue = 48u;
static const uint16_t DisplayUpdater_LCDHeightYellow = 16u;
//static const uint16_t DisplayUpdater_LCDWidth = 128u;


static void GMViewBargraph_ShowDoseLabel();
static void GMViewBargraph_ShowBargraph();

void GMViewBargraph_Init()
{

}

void GMViewBargraph_Show()
{
    GMViewBargraph_ShowDoseLabel();
    GMViewBargraph_ShowBargraph();
}

void GMViewBargraph_ShowBargraph()
{
    LoggerMeasurement_Value_t minElement = 0u;
	LoggerMeasurement_Value_t maxElement = 0u;
    Logger_CircularBuffer_GetMinMaxElement(&minElement, &maxElement);
	// TODO check return value

    for(uint16_t i = 0; i < Logger_CircularBuffer_GetElementCount() ; i++)
    {
    	LoggerMeasurement_Value_t sampleValue;
        uint16_t indexInBuffer = (uint16_t)(Logger_CircularBuffer_GetElementCount() - (i + 1U));
        Logger_CircularBuffer_GetElementStatus_t status = Logger_CircularBuffer_GetElement(&sampleValue, indexInBuffer);

        if(status == LOGGER_CIRCULAR_BUFFER_GETELEMENT_OK)
        {
            const uint16_t DisplayUpdater_LCDHeight = (DisplayUpdater_LCDHeightBlue + DisplayUpdater_LCDHeightYellow);

            uint16_t y0 = DisplayUpdater_LCDHeight;

            uint16_t graphHeight = DisplayUpdater_LCDHeightBlue;
            uint16_t  normalizedSampleValue = (uint16_t)( ((float)(sampleValue) / (float)(maxElement)) * graphHeight);
            uint16_t y1 = (uint16_t)(DisplayUpdater_LCDHeight - normalizedSampleValue);

            GMDisplayHW_DrawLine(i, y0, i, y1);
        }
    }
}

void GMViewBargraph_ShowDoseLabel()
{
	LoggerMeasurement_Value_t latestSampleValue;
    uint16_t latestSampleIndex = 0U;
    Logger_CircularBuffer_GetElementStatus_t status = Logger_CircularBuffer_GetElement(&latestSampleValue, latestSampleIndex);

    uint16_t stringOffset = 0U;

    if (status == LOGGER_CIRCULAR_BUFFER_GETELEMENT_OK)
    {
        // TODO check string size to avoid buffer overflow

        uint16_t base = 10;
        itoa(latestSampleValue, &labelDose[stringOffset], base);

        stringOffset = strlen(labelDose);
        strcpy(&labelDose[stringOffset], labelMinuteCounter);
    }
    else
    {
        strcpy(&labelDose[stringOffset], labelError);
    }

    GMDisplayHW_DrawText(0, 0, labelDose);
}
