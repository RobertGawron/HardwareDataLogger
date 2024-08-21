#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "st7735.h"
#include "St7735DisplayDriver.hpp"

// Define the global mock instance
MockLibST7735 *mockLibST7735;

namespace Driver
{
    class St7735DisplayDriverTest : public ::testing::Test
    {
    protected:
        St7735DisplayDriver *driver;
        MockLibST7735 MockLibST7735_Instance;
        void SetUp() override
        {
            // Assign the global mock instance
            mockLibST7735 = &MockLibST7735_Instance;
            driver = new St7735DisplayDriver();
        }

        void TearDown() override
        {
            delete driver;
            mockLibST7735 = nullptr; // Reset the global mock instance
        }
    };

    TEST_F(St7735DisplayDriverTest, TestDrawPixel)
    {
        EXPECT_CALL(MockLibST7735_Instance, ST7735_DrawPixel(10, 20, 0xF800)).Times(1); // Testing with arbitrary coordinates and color

        EXPECT_TRUE(driver->drawPixel(10, 20, 0xF800));
    }

    TEST_F(St7735DisplayDriverTest, TestWriteString)
    {
        EXPECT_CALL(MockLibST7735_Instance, ST7735_WriteString(5, 5, ::testing::StrEq("Hello"), ::testing::_, 0xFFFF, 0x0000)).Times(1);

        EXPECT_TRUE(driver->writeString(5, 5, "Hello", Font_7x10, 0xFFFF, 0x0000));
    }

    TEST_F(St7735DisplayDriverTest, TestFillRectangle)
    {
        EXPECT_CALL(MockLibST7735_Instance, ST7735_FillRectangle(0, 0, 50, 50, 0x07E0)).Times(1);

        EXPECT_TRUE(driver->fillRectangle(0, 0, 50, 50, 0x07E0));
    }

    TEST_F(St7735DisplayDriverTest, TestFillScreen)
    {
        EXPECT_CALL(MockLibST7735_Instance, ST7735_FillScreen(0x001F)).Times(1);

        EXPECT_TRUE(driver->fillScreen(0x001F));
    }

    TEST_F(St7735DisplayDriverTest, TestDrawImage)
    {
        uint16_t imageData[100] = {0}; // Example image data

        EXPECT_CALL(MockLibST7735_Instance, ST7735_DrawImage(0, 0, 10, 10, imageData)).Times(1);

        EXPECT_TRUE(driver->drawImage(0, 0, 10, 10, imageData));
    }

    TEST_F(St7735DisplayDriverTest, TestInvertColors)
    {
        EXPECT_CALL(MockLibST7735_Instance, ST7735_InvertColors(true)).Times(1);

        driver->invertColors(true);
    }
}