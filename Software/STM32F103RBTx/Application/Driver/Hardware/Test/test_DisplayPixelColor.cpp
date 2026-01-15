#include "Driver/Interface/DisplayPixelColor.hpp"

#include <gtest/gtest.h>
#include <cstdint>

// Test fixture class for DisplayPixelColor
class DisplayPixelColorTest : public ::testing::Test
{
public:
    void SetUp() override
    {
        // Any common setup can go here
    }

    void TearDown() override
    {
        // Any cleanup can go here
    }

    [[nodiscard]] static std::uint8_t getMaxIntensity()
    {
        return maxIntensity;
    }

    [[nodiscard]] static std::uint8_t getMinIntensity()
    {
        return minIntensity;
    }

private:
    static constexpr std::uint8_t maxIntensity = 0xFF;
    static constexpr std::uint8_t minIntensity = 0x00;
};

// Test for the RGB565 conversion
TEST_F(DisplayPixelColorTest, TestColorConversion)
{
    // Test conversion of specific colors and check against known values

    // Test Black
    const std::uint16_t black = Device::DisplayPixelColor::getColor(getMinIntensity(), getMinIntensity(), getMinIntensity());
    EXPECT_EQ(black, Device::DisplayPixelColor::BLACK);

    // Test Blue
    const std::uint16_t blue = Device::DisplayPixelColor::getColor(getMinIntensity(), getMinIntensity(), getMaxIntensity());
    EXPECT_EQ(blue, Device::DisplayPixelColor::BLUE);

    // Test Red
    const std::uint16_t red = Device::DisplayPixelColor::getColor(getMaxIntensity(), getMinIntensity(), getMinIntensity());
    EXPECT_EQ(red, Device::DisplayPixelColor::RED);

    // Test Green
    const std::uint16_t green = Device::DisplayPixelColor::getColor(getMinIntensity(), getMaxIntensity(), getMinIntensity());
    EXPECT_EQ(green, Device::DisplayPixelColor::GREEN);

    // Test Cyan
    const std::uint16_t cyan = Device::DisplayPixelColor::getColor(getMinIntensity(), getMaxIntensity(), getMaxIntensity());
    EXPECT_EQ(cyan, Device::DisplayPixelColor::CYAN);

    // Test Magenta
    const std::uint16_t magenta = Device::DisplayPixelColor::getColor(getMaxIntensity(), getMinIntensity(), getMaxIntensity());
    EXPECT_EQ(magenta, Device::DisplayPixelColor::MAGENTA);

    // Test Yellow
    const std::uint16_t yellow = Device::DisplayPixelColor::getColor(getMaxIntensity(), getMaxIntensity(), getMinIntensity());
    EXPECT_EQ(yellow, Device::DisplayPixelColor::YELLOW);

    // Test White
    const std::uint16_t white = Device::DisplayPixelColor::getColor(getMaxIntensity(), getMaxIntensity(), getMaxIntensity());
    EXPECT_EQ(white, Device::DisplayPixelColor::WHITE);
}

// Additional tests for arbitrary colors using the public interface
TEST_F(DisplayPixelColorTest, TestCustomColors)
{
    // Example: Test some arbitrary colors and compare them with expected RGB565 values
    const std::uint16_t customColor1 = Device::DisplayPixelColor::getColor(0x12, 0x34, 0x56);
    const std::uint16_t expectedColor1 = (0x12 >> 3) << 11 | (0x34 >> 2) << 5 | (0x56 >> 3);
    EXPECT_EQ(customColor1, expectedColor1);

    const std::uint16_t customColor2 = Device::DisplayPixelColor::getColor(0xAA, 0xBB, 0xCC);
    const std::uint16_t expectedColor2 = (0xAA >> 3) << 11 | (0xBB >> 2) << 5 | (0xCC >> 3);
    EXPECT_EQ(customColor2, expectedColor2);
}
