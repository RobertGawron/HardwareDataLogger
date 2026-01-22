module;

#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_dma.h"
#include "stm32f1xx_hal_spi.h"
#include "stm32f1xx_hal_gpio.h"

#include "st7735.h"

#include <cstdint>

extern SPI_HandleTypeDef LCD_SPI_Handle;

module Driver.DisplayDriver;

namespace
{
    // Hardware globals required by the ST7735 library
    ST7735_IO_t hwDisplayIoDef{};
    ST7735_Object_t hwDisplayDriver{};

    constexpr std::uint32_t SPI_TIMEOUT_MS = 500U;
}

extern "C"
{
    int32_t LCD_IO_Init() noexcept
    {
        // HAL limitation: these functions return void, so success is assumed.

        constexpr std::uint32_t LCD_RESET_LOW_DELAY_MS = 50U;
        constexpr std::uint32_t LCD_RESET_POST_DELAY_MS = 150U;

        HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);

        HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
        HAL_Delay(LCD_RESET_LOW_DELAY_MS);

        HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
        HAL_Delay(LCD_RESET_POST_DELAY_MS);

        return ST7735_OK;
    }

    int32_t LCD_IO_WriteReg(uint8_t reg, uint8_t *pData, uint32_t len) noexcept
    {
        // Note: HAL limitation: only HAL_SPI_Transmit returns a status.

        int32_t status = ST7735_OK;

        HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);

        HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);
        if (HAL_SPI_Transmit(&LCD_SPI_Handle, &reg, 1U, SPI_TIMEOUT_MS) != HAL_OK)
        {
            status = ST7735_ERROR;
        }

        if ((status == ST7735_OK) && (len != 0U) && (pData != nullptr))
        {
            HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
            if (HAL_SPI_Transmit(&LCD_SPI_Handle, pData, len, SPI_TIMEOUT_MS) != HAL_OK)
            {
                status = ST7735_ERROR;
            }
        }

        HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);

        return status;
    }

    int32_t LCD_IO_ST7735_ReadReg(uint8_t /*reg*/, uint8_t * /*data*/) noexcept
    {
        // Implementation not needed; required by the ST7735 library API.
        return ST7735_OK;
    }

    int32_t LCD_IO_ST7735_RecvData(uint8_t * /*data*/, uint32_t /*length*/) noexcept
    {
        // Implementation not needed; required by the ST7735 library API.
        return ST7735_OK;
    }

    int32_t LCD_IO_WriteData(uint8_t *pData, uint32_t Length) noexcept
    {
        // Note: HAL limitation: only HAL_SPI_Transmit returns a status.

        HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);

        const HAL_StatusTypeDef status = HAL_SPI_Transmit(&LCD_SPI_Handle,
                                                          pData,
                                                          Length,
                                                          SPI_TIMEOUT_MS);

        HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);

        return (status == HAL_OK) ? ST7735_OK : ST7735_ERROR;
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
        bool status = true;
        int32_t driverStatus = ST7735_OK;

        // Configure IO function pointers
        hwDisplayIoDef.Init = LCD_IO_Init;
        hwDisplayIoDef.DeInit = nullptr;
        hwDisplayIoDef.Address = 0U;
        hwDisplayIoDef.WriteReg = LCD_IO_WriteReg;
        hwDisplayIoDef.ReadReg = LCD_IO_ST7735_ReadReg;
        hwDisplayIoDef.SendData = LCD_IO_WriteData;
        hwDisplayIoDef.RecvData = LCD_IO_ST7735_RecvData;
        hwDisplayIoDef.GetTick = LCD_IO_GetTick;

        if (status)
        {
            driverStatus = ST7735_RegisterBusIO(&hwDisplayDriver,
                                                &hwDisplayIoDef);

            status = (driverStatus == ST7735_OK);
        }

        if (status)
        {
            driverStatus = ST7735_Init(&hwDisplayDriver,
                                       ST7735_FORMAT_DEFAULT,
                                       ST7735_ORIENTATION_LANDSCAPE);

            status = (driverStatus == ST7735_OK);
        }

        if (status)
        {
            driverStatus = ST7735_DisplayOn(&hwDisplayDriver);
            status = (driverStatus == ST7735_OK);
        }

        if (status)
        {
            // Fill the screen with black (RGB565)
            driverStatus = ST7735_FillRect(&hwDisplayDriver, 0U, 0U, 128U, 160U, 0x0000U);
            status = (driverStatus == ST7735_OK);
        }

        return status;
    }

    bool DisplayDriver::onStart() noexcept
    {
        // Draw test rectangles. This is only a test; return values are ignored.

        ST7735_FillRect(&hwDisplayDriver, 10, 10, 55, 155, 0xFE000);
        ST7735_FillRect(&hwDisplayDriver, 5, 5, 100, 100, 0x20FE);

        return true;
    }

    bool DisplayDriver::setCursor(std::uint8_t /*xPosition*/,
                                  std::uint8_t /*yPosition*/) noexcept
    {
        // TBD: implement
        return true;
    }

    bool DisplayDriver::drawBitmap(std::uint8_t /*xPosition*/,
                                   std::uint8_t /*yPosition*/,
                                   std::uint8_t & /*bitmap*/) noexcept
    {
        // TBD: implement
        return true;
    }

    bool DisplayDriver::fillRGBRectangle(std::uint8_t /*xPosition*/,
                                         std::uint8_t /*yPosition*/,
                                         std::uint8_t & /*data*/,
                                         std::uint8_t /*width*/,
                                         std::uint8_t /*height*/) noexcept
    {
        // TBD: implement
        return true;
    }

} // namespace Driver