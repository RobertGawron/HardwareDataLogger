module;

#include "st7735.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_dma.h"
#include "stm32f1xx_hal_spi.h"
#include "stm32f1xx_hal_gpio.h"

#include <cstdint>

module Driver.DisplayDriver;

// import Driver.DisplayPixelColor;

// Hardware globals - required by ST7735 library
ST7735_IO_t hwDisplayIoDef{};
ST7735_Object_t hwDisplayDriver{};

extern SPI_HandleTypeDef hspi1;

namespace
{
    // Pin definitions (match CubeMX configuration)
    GPIO_TypeDef *const LCD_CS_PORT = GPIOD;
    constexpr std::uint16_t LCD_CS_PIN = GPIO_PIN_2;
    GPIO_TypeDef *const LCD_DC_PORT = GPIOA;
    constexpr std::uint16_t LCD_DC_PIN = GPIO_PIN_15;
    GPIO_TypeDef *const LCD_RST_PORT = GPIOB;
    constexpr std::uint16_t LCD_RST_PIN = GPIO_PIN_2;

    constexpr std::uint32_t SPI_TIMEOUT_MS = 500U;
    constexpr std::uint32_t RESET_DELAY_MS = 10U;
}

extern "C"
{
    int32_t LCD_IO_Init() noexcept
    {
        HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_RESET);
        HAL_Delay(RESET_DELAY_MS);
        HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);
        return 0;
    }

    int32_t LCD_IO_WriteReg(uint8_t Reg, uint8_t *pData, uint32_t Length) noexcept
    {
        // Select LCD (CS Low)
        HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);

        // Send command byte (DC Low)
        HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);
        HAL_SPI_Transmit(&hspi1, &Reg, 1U, SPI_TIMEOUT_MS);

        // Send data bytes if any (DC High)
        if (Length > 0U && pData != nullptr)
        {
            HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
            HAL_SPI_Transmit(&hspi1, pData, Length, SPI_TIMEOUT_MS);
        }

        // Deselect LCD (CS High)
        HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
        return 0;
    }

    int32_t LCD_IO_ST7735_ReadReg(uint8_t /*reg*/, uint8_t * /*data*/) noexcept
    {
        return 0; // Not implemented
    }

    int32_t LCD_IO_ST7735_RecvData(uint8_t * /*data*/, uint32_t /*length*/) noexcept
    {
        return 0; // Not implemented
    }

    int32_t LCD_IO_WriteData(uint8_t *pData, uint32_t Length) noexcept
    {
        HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
        HAL_SPI_Transmit(&hspi1, pData, Length, SPI_TIMEOUT_MS);
        HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
        return 0;
    }

    int32_t LCD_IO_GetTick() noexcept
    {
        return static_cast<int32_t>(HAL_GetTick());
    }
}

namespace Driver
{
    bool DisplayDriver::onInit() noexcept
    {
        // Configure IO function pointers
        hwDisplayIoDef.Init = LCD_IO_Init;
        hwDisplayIoDef.DeInit = nullptr;
        hwDisplayIoDef.Address = 0U;
        hwDisplayIoDef.WriteReg = LCD_IO_WriteReg;
        hwDisplayIoDef.ReadReg = LCD_IO_ST7735_ReadReg;
        hwDisplayIoDef.SendData = LCD_IO_WriteData;
        hwDisplayIoDef.RecvData = LCD_IO_ST7735_RecvData;
        hwDisplayIoDef.GetTick = LCD_IO_GetTick;

        // Initialize display
        ST7735_RegisterBusIO(&hwDisplayDriver, &hwDisplayIoDef);
        ST7735_Init(&hwDisplayDriver, ST7735_ORIENTATION_PORTRAIT, ST7735_FORMAT_DEFAULT);
        ST7735_DisplayOn(&hwDisplayDriver);
        ST7735_FillRect(&hwDisplayDriver, 0, 0, 160, 128, 0x125425);

        return true;
    }

    bool DisplayDriver::displayOn() noexcept
    {
        return true;
    }

    bool DisplayDriver::displayOff() noexcept
    {
        return true;
    }

    bool DisplayDriver::setOrientation(Orientation /*orientation*/) noexcept
    {
        return true;
    }

    bool DisplayDriver::getOrientation(Orientation & /*orientation*/) const noexcept
    {
        return true;
    }

    bool DisplayDriver::setCursor(std::uint8_t /*xPosition*/, std::uint8_t /*yPosition*/) noexcept
    {
        return true;
    }

    bool DisplayDriver::drawBitmap(std::uint8_t /*xPosition*/,
                                   std::uint8_t /*yPosition*/,
                                   std::uint8_t & /*bitmap*/) noexcept
    {
        return true;
    }

    bool DisplayDriver::fillRGBRectangle(std::uint8_t /*xPosition*/,
                                         std::uint8_t /*yPosition*/,
                                         std::uint8_t & /*data*/,
                                         std::uint8_t /*width*/,
                                         std::uint8_t /*height*/) noexcept
    {
        return true;
    }
#if 0
    bool DisplayDriver::fillRectangle(std::uint8_t /*xPosition*/,
                                                       std::uint8_t /*yPosition*/,
                                                       std::uint8_t /*width*/,
                                                       std::uint8_t /*height*/,
                                                       DisplayPixelColor::PixelColor /*color*/) noexcept
    {
        return true;
    }

    bool DisplayDriver::setPixel(std::uint8_t /*xPosition*/,
                                                  std::uint8_t /*yPosition*/,
                                                  DisplayPixelColor::PixelColor /*color*/) noexcept
    {
        return true;
    }

    bool DisplayDriver::getPixel(std::uint8_t /*xPosition*/,
                                                  std::uint8_t /*yPosition*/,
                                                  DisplayPixelColor::PixelColor & /*color*/) const noexcept
    {
        return true;
    }
#endif
    bool DisplayDriver::getXSize(std::uint8_t & /*size*/) const noexcept
    {
        return true;
    }

    bool DisplayDriver::getYSize(std::uint8_t & /*size*/) const noexcept
    {
        return true;
    }

} // namespace Driver