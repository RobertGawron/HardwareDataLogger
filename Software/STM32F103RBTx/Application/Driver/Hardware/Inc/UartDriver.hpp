/**
 * @file UartDriver.hpp
 * @brief Modern C++23 UART driver using STM32 HAL
 */

#ifndef UartDriver_h
#define UartDriver_h

#include "Driver/Interface/UartDriverConcept.hpp"
#include "Driver/Interface/DriverComponent.hpp"
#include "Driver/Interface/UartStatus.hpp"

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_uart.h"

#include <span>
#include <cstdint>

namespace Driver
{
    /**
     * @class UartDriver
     * @brief Hardware abstraction for UART communication via STM32 HAL
     */
    class UartDriver final : public DriverComponent
    {
    public:
        explicit constexpr UartDriver(UART_HandleTypeDef &_uartHandler) noexcept
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

        UART_HandleTypeDef &uartHandler;
    };

    static_assert(Driver::Concepts::UartDriverConcept<UartDriver>,
                  "UartDriver must satisfy the concept requirements");

} // namespace Driver

#endif // UartDriver_h