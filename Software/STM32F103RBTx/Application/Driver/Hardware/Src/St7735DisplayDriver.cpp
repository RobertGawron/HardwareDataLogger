#include "Driver/Hardware/Inc/St7735DisplayDriver.hpp"
#include "Driver/Interface/DisplayPixelColor.hpp"
#include "Driver/Interface/IDisplayDriver.hpp"

// todo remove suppression when the lib is fully integrated
// codechecker_suppress [misc-include-cleaner]
#include "st7735.h"

#include <cstdint>
#include "st7735.h"
// #include "main.h"
#include "stm32f1xx_hal_dma.h"
#include "stm32f1xx_hal_spi.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal.h"

ST7735_IO_t hwDisplayIoDef;
ST7735_Object_t hwDisplayDriver;

extern SPI_HandleTypeDef hspi1;

/* Pin Definitions (Match your CubeMX setup) */
#define LCD_CS_PORT GPIOD
#define LCD_CS_PIN GPIO_PIN_2
#define LCD_DC_PORT GPIOA
#define LCD_DC_PIN GPIO_PIN_15
#define LCD_RST_PORT GPIOB
#define LCD_RST_PIN GPIO_PIN_2

// 1. Initialize IO(GPIOs are already initted by HAL_MspInit, so just wait)
int32_t LCD_IO_Init(void)
{
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET); // Deselect
    HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_RESET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);
    return 0;
}

// 2. Write Register (Command)
//    Sequence: CS Low -> DC Low -> SPI Transmit -> CS High
/*
 * LCD_IO_WriteReg
 *
 * Handle: Pointer to your SPI Handle (e.g., &hspi1)
 * Reg:    The Command Register address (e.g., 0x2A)
 * pData:  Pointer to the parameters/data to write
 * Length: Number of bytes in pData
 */
int32_t LCD_IO_WriteReg(uint8_t Reg, uint8_t *pData, uint32_t Length)
{
    /* 1. Select the LCD (CS Low) */
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);

    /* 2. Send the Command Byte (Reg) */
    // Set DC to Low for Command mode
    HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);

    // Transmit the 1-byte command
    HAL_SPI_Transmit(&hspi1, &Reg, 1, 100);

    /* 3. Send the Parameters/Data (if any) */
    if (Length > 0 && pData != NULL)
    {
        // Set DC to High for Data mode
        HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);

        // Transmit the buffer
        HAL_SPI_Transmit(&hspi1, pData, Length, 500);
    }

    /* 4. Deselect the LCD (CS High) */
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);

    /* 5. Return Success (0) */
    return 0;
}

int32_t LCD_IO_ST7735_ReadReg(uint8_t dummy1, uint8_t *dummy2)
{
    static_cast<void>(dummy1);
    static_cast<void>(dummy2);
    /* 5. Return Success (0) */
    return 0;
}

int32_t LCD_IO_ST7735_RecvData(uint8_t *dummy1, uint32_t dummy2)
{
    static_cast<void>(dummy1);
    static_cast<void>(dummy2);
    /* 5. Return Success (0) */
    return 0;
}

// 3. Write Data
//    Sequence: CS Low -> DC High -> SPI Transmit -> CS High
int32_t LCD_IO_WriteData(uint8_t *pData, uint32_t Length)
{
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET); // Select
    HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);   // Data Mode
    HAL_SPI_Transmit(&hspi1, pData, Length, 500);
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET); // Deselect
    return 0;
}

int32_t LCD_IO_GetTick()
{
    /*
     * HAL_GetTick() returns the time in milliseconds (uint32_t).
     * We cast it to int32_t to match the driver's signature.
     */
    return static_cast<int32_t>(HAL_GetTick());
}

namespace Driver
{
    bool St7735DisplayDriver::onInitialize()
    {
        hwDisplayIoDef.Init = LCD_IO_Init;
        hwDisplayIoDef.DeInit = NULL;
        hwDisplayIoDef.Address = NULL;
        hwDisplayIoDef.WriteReg = LCD_IO_WriteReg;
        hwDisplayIoDef.ReadReg = LCD_IO_ST7735_ReadReg; // dummy
        hwDisplayIoDef.SendData = LCD_IO_WriteData;
        hwDisplayIoDef.RecvData = LCD_IO_ST7735_RecvData; // dummy
        hwDisplayIoDef.GetTick = LCD_IO_GetTick;

        ST7735_RegisterBusIO(&hwDisplayDriver, &hwDisplayIoDef);
        ST7735_Init(&hwDisplayDriver, ST7735_ORIENTATION_PORTRAIT, ST7735_FORMAT_DEFAULT);
        ST7735_DisplayOn(&hwDisplayDriver);
        ST7735_FillRect(&hwDisplayDriver, 0, 0, 160, 128, 0x125425);

        return true;
    }

    bool St7735DisplayDriver::onStart()
    {
        const bool status = true;

        return status;
    }

    bool St7735DisplayDriver::onStop()
    {
        const bool status = true;

        return status;
    }

    bool St7735DisplayDriver::onReset()
    {
        return true;
    }

    IDisplayDriver::Status St7735DisplayDriver::displayOn()
    {
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::displayOff()
    {
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::setOrientation(IDisplayDriver::Orientation orientation)
    {
        static_cast<void>(orientation);
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::getOrientation(IDisplayDriver::Orientation &orientation) const
    {
        static_cast<void>(orientation);
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::setCursor(std::uint8_t xPosition, std::uint8_t yPosition)
    {
        static_cast<void>(xPosition);
        static_cast<void>(yPosition);
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::drawBitmap(std::uint8_t xPosition, std::uint8_t yPosition, std::uint8_t &bitmap)
    {
        static_cast<void>(xPosition);
        static_cast<void>(yPosition);
        static_cast<void>(bitmap);
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::fillRGBRectangle(std::uint8_t xPosition,
                                                                 std::uint8_t yPosition,
                                                                 std::uint8_t &data,
                                                                 std::uint8_t width,
                                                                 std::uint8_t height)
    {
        static_cast<void>(xPosition);
        static_cast<void>(yPosition);
        static_cast<void>(data);
        static_cast<void>(width);
        static_cast<void>(height);
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::fillRectangle(std::uint8_t xPosition,
                                                              std::uint8_t yPosition,
                                                              std::uint8_t width,
                                                              std::uint8_t height,
                                                              DisplayPixelColor::PixelColor color)
    {
        static_cast<void>(xPosition);
        static_cast<void>(yPosition);
        static_cast<void>(width);
        static_cast<void>(height);
        static_cast<void>(color);
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::setPixel(std::uint8_t xPosition,
                                                         std::uint8_t yPosition,
                                                         DisplayPixelColor::PixelColor color)
    {
        static_cast<void>(xPosition);
        static_cast<void>(yPosition);
        static_cast<void>(color);
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::getPixel(std::uint8_t xPosition,
                                                         std::uint8_t yPosition,
                                                         DisplayPixelColor::PixelColor &color) const
    {
        static_cast<void>(xPosition);
        static_cast<void>(yPosition);
        static_cast<void>(color);
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::getXSize(std::uint8_t &size) const
    {
        static_cast<void>(size);
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::getYSize(std::uint8_t &size) const
    {
        static_cast<void>(size);
        return IDisplayDriver::Status::Ok;
    }
}
