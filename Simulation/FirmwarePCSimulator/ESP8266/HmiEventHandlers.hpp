#ifndef HmiEventHandlers_hpp
#define HmiEventHandlers_hpp

#include <functional>
#include <cstdint>
#include <queue>
#include <cstdint>

// from Software\STM32F103RBTx\Drivers\STM32F1xx_HAL_Driver\Inc\stm32f1xx_hal_def.h
// just for convenience, but we dont need to be compatible wih that
typedef enum
{
    HAL_OK = 0x00U,
    HAL_ERROR = 0x01U,
    HAL_BUSY = 0x02U,
    HAL_TIMEOUT = 0x03U
} HAL_StatusTypeDef;

enum class GPIO_ID
{
    GPIO1 = 13, // hack
    GPIO2 = 2,
    GPIO3 = 3
    // Add more GPIO IDs as necessary
};

// Type alias for the callback functions
using OnGpioChangeCallback = void (*)(GPIO_ID gpioId, bool state);
using OnSerialTxCallback = std::function<void(char *)>;

extern OnGpioChangeCallback onGpioChange;
extern std::deque<uint8_t> uartQueueTx; // Queue for UART transmission

void registerOnGpioChange(OnGpioChangeCallback callback);

void registerOnSerialTx(void (*callback)(char *));

void setPinState(GPIO_ID gpioId, bool state);

// esp8266 -> gui
void serialTx(char *data);

// gui -> esp8266
HAL_StatusTypeDef serialRx(
    const std::uint8_t *pData,
    std::uint16_t Size,
    std::uint32_t Timeout);

#endif
