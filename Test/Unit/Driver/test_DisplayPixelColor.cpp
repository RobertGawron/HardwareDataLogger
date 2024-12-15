#include <gtest/gtest.h>
#include "Driver/Inc/DisplayPixelColor.hpp"

namespace Driver
{
    // Test fixture class for DisplayPixelColor
    class DisplayPixelColorTest : public ::testing::Test
    {
    protected:
        // This function runs before each test
        void SetUp() override
        {
            // Any common setup can go here
        }

        // This function runs after each test
        void TearDown() override
        {
            // Any cleanup can go here
        }
    };

    // Test for the RGB565 conversion
    TEST_F(DisplayPixelColorTest, TestColorConversion)
    {
        // Test conversion of specific colors and check against known values

        // Test Black
        std::uint16_t black = DisplayPixelColor::getColor(0x00, 0x00, 0x00);
        EXPECT_EQ(black, DisplayPixelColor::BLACK);

        // Test Blue
        std::uint16_t blue = DisplayPixelColor::getColor(0x00, 0x00, 0xFF);
        EXPECT_EQ(blue, DisplayPixelColor::BLUE);

        // Test Red
        std::uint16_t red = DisplayPixelColor::getColor(0xFF, 0x00, 0x00);
        EXPECT_EQ(red, DisplayPixelColor::RED);

        // Test Green
        std::uint16_t green = DisplayPixelColor::getColor(0x00, 0xFF, 0x00);
        EXPECT_EQ(green, DisplayPixelColor::GREEN);

        // Test Cyan
        std::uint16_t cyan = DisplayPixelColor::getColor(0x00, 0xFF, 0xFF);
        EXPECT_EQ(cyan, DisplayPixelColor::CYAN);

        // Test Magenta
        std::uint16_t magenta = DisplayPixelColor::getColor(0xFF, 0x00, 0xFF);
        EXPECT_EQ(magenta, DisplayPixelColor::MAGENTA);

        // Test Yellow
        std::uint16_t yellow = DisplayPixelColor::getColor(0xFF, 0xFF, 0x00);
        EXPECT_EQ(yellow, DisplayPixelColor::YELLOW);

        // Test White
        std::uint16_t white = DisplayPixelColor::getColor(0xFF, 0xFF, 0xFF);
        EXPECT_EQ(white, DisplayPixelColor::WHITE);
    }

    // Additional tests for arbitrary colors using the public interface
    TEST_F(DisplayPixelColorTest, TestCustomColors)
    {
        // Example: Test some arbitrary colors and compare them with expected RGB565 values
        std::uint16_t customColor1 = DisplayPixelColor::getColor(0x12, 0x34, 0x56);
        std::uint16_t expectedColor1 = (0x12 >> 3) << 11 | (0x34 >> 2) << 5 | (0x56 >> 3);
        EXPECT_EQ(customColor1, expectedColor1);

        std::uint16_t customColor2 = DisplayPixelColor::getColor(0xAA, 0xBB, 0xCC);
        std::uint16_t expectedColor2 = (0xAA >> 3) << 11 | (0xBB >> 2) << 5 | (0xCC >> 3);
        EXPECT_EQ(customColor2, expectedColor2);
    }

} // namespace Driver
