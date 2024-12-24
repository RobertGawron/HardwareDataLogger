#include <gtest/gtest.h>
#include "Driver/Inc/DisplayPixelColor.hpp"

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
    std::uint16_t black = Driver::DisplayPixelColor::getColor(0x00, 0x00, 0x00);
    EXPECT_EQ(black, Driver::DisplayPixelColor::BLACK);

    // Test Blue
    std::uint16_t blue = Driver::DisplayPixelColor::getColor(0x00, 0x00, 0xFF);
    EXPECT_EQ(blue, Driver::DisplayPixelColor::BLUE);

    // Test Red
    std::uint16_t red = Driver::DisplayPixelColor::getColor(0xFF, 0x00, 0x00);
    EXPECT_EQ(red, Driver::DisplayPixelColor::RED);

    // Test Green
    std::uint16_t green = Driver::DisplayPixelColor::getColor(0x00, 0xFF, 0x00);
    EXPECT_EQ(green, Driver::DisplayPixelColor::GREEN);

    // Test Cyan
    std::uint16_t cyan = Driver::DisplayPixelColor::getColor(0x00, 0xFF, 0xFF);
    EXPECT_EQ(cyan, Driver::DisplayPixelColor::CYAN);

    // Test Magenta
    std::uint16_t magenta = Driver::DisplayPixelColor::getColor(0xFF, 0x00, 0xFF);
    EXPECT_EQ(magenta, Driver::DisplayPixelColor::MAGENTA);

    // Test Yellow
    std::uint16_t yellow = Driver::DisplayPixelColor::getColor(0xFF, 0xFF, 0x00);
    EXPECT_EQ(yellow, Driver::DisplayPixelColor::YELLOW);

    // Test White
    std::uint16_t white = Driver::DisplayPixelColor::getColor(0xFF, 0xFF, 0xFF);
    EXPECT_EQ(white, Driver::DisplayPixelColor::WHITE);
}

// Additional tests for arbitrary colors using the public interface
TEST_F(DisplayPixelColorTest, TestCustomColors)
{
    // Example: Test some arbitrary colors and compare them with expected RGB565 values
    std::uint16_t customColor1 = Driver::DisplayPixelColor::getColor(0x12, 0x34, 0x56);
    std::uint16_t expectedColor1 = (0x12 >> 3) << 11 | (0x34 >> 2) << 5 | (0x56 >> 3);
    EXPECT_EQ(customColor1, expectedColor1);

    std::uint16_t customColor2 = Driver::DisplayPixelColor::getColor(0xAA, 0xBB, 0xCC);
    std::uint16_t expectedColor2 = (0xAA >> 3) << 11 | (0xBB >> 2) << 5 | (0xCC >> 3);
    EXPECT_EQ(customColor2, expectedColor2);
}
