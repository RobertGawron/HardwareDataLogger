#include "stm32f1xx_hal_uart.h"

// This will be taken by PlatformFactoryStm32.cpp, but this is only needed for compilation.
// We wont use this, instead we will use our stub implementation to send data to the simulation's HMI.
UART_HandleTypeDef huart3;
