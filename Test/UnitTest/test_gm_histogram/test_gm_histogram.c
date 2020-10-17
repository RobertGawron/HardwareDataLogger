#include <stdint.h>
#include "utest.h"
#include "gm_histogram.h"
#include "stub_gm_circular_buffer.h"

UTEST(GMHistogram_GetBinValue, GMHistogram_GetBinValue) 
{
    StubGMCircularBuffer_SetElement(1);
    StubGMCircularBuffer_SetElement(2);
    StubGMCircularBuffer_SetElement(3);
    StubGMCircularBuffer_SetElementCount(3);
    StubGMCircularBuffer_SetMinMaxElement(1, 3);

    uint8_t binIndex = 0;
    uint8_t totalBinAmount = 2;

    uint16_t binValue = GMHistogram_GetBinValue(binIndex, totalBinAmount);

    EXPECT_EQ(1, binValue);
}

UTEST_MAIN();
