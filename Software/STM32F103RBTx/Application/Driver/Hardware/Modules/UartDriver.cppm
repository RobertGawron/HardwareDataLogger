module;

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_usart.h"

#include <span>
#include <cstdint>

export module Driver.UartDriver;

import Driver.DriverComponent;
import Driver.UartDriverConcept;

import Driver.UartStatus;

export namespace Driver
{
    /**
     * @class UartDriver
     * @brief Hardware abstraction for UART communication via STM32 HAL
     */
    class UartDriver final : public DriverComponent
    {
    public:
        explicit constexpr UartDriver(USART_HandleTypeDef &_uartHandler) noexcept
            : uartHandler(_uartHandler)
        {
        }

        ~UartDriver() = default;

        UartDriver() = delete;
        UartDriver(const UartDriver &) = delete;
        UartDriver &operator=(const UartDriver &) = delete;
        UartDriver(UartDriver &&) = delete;
        UartDriver &operator=(UartDriver &&) = delete;

        [[nodiscard]] UartStatus transmit(std::span<const std::uint8_t> data,
                                          std::uint32_t timeout) noexcept;
        [[nodiscard]] UartStatus receive(std::span<std::uint8_t> data,
                                         std::uint32_t timeout) noexcept;

    private:
        [[nodiscard]] static constexpr UartStatus getUartStatus(HAL_StatusTypeDef halStatus) noexcept
        {
            switch (halStatus)
            {
            case HAL_OK:
                return UartStatus::Ok;
            case HAL_ERROR:
                return UartStatus::ErrorFromHal;
            case HAL_BUSY:
                return UartStatus::Busy;
            case HAL_TIMEOUT:
                return UartStatus::Timeout;
            default:
                return UartStatus::ErrorUnknown;
            }
        }

        USART_HandleTypeDef &uartHandler;
    };

    static_assert(Driver::Concepts::UartDriverConcept<UartDriver>,
                  "UartDriver must satisfy the concept requirements");

} // namespace Driver