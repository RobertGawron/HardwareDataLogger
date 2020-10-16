#include <stdint.h>
#include "gm_view_histogram.h"
#include "gm_display_hw.h"
#include "gm_histogram.h"


static const uint8_t histogramBinAmount = 10;

// TOD move it somewhere
static const uint16_t DisplayUpdater_LCDHeightBlue = 48u;
static const uint16_t DisplayUpdater_LCDHeightYellow = 16u;
//static const uint16_t DisplayUpdater_LCDWidth = 128u;

void GMViewHistogram_Init()
{

}

void GMViewHistogram_Show()
{
    const uint8_t binWidthOnDisplay = GMDisplayHW_GetDisplayWidth() / histogramBinAmount;

    uint8_t graphHeight = DisplayUpdater_LCDHeightBlue;
    uint16_t maxBinValue = GMHistogram_GetMaxBinValue(histogramBinAmount);
    uint8_t x0 = 0;

    if (maxBinValue > 0u)
    {
        for (uint8_t i = 0U; i < histogramBinAmount; i++)
        {
            uint16_t binValue = GMHistogram_GetBinValue(i, histogramBinAmount);
            uint32_t normalizedBinValue = binValue * graphHeight/ maxBinValue;

            GMDisplayHW_DrawRectangle(x0, GMDisplayHW_GetDisplayHeight()-normalizedBinValue, binWidthOnDisplay, GMDisplayHW_GetDisplayHeight());

            x0 += binWidthOnDisplay;
        }
    }
}
