#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "main.h"
#include "stm32f1xx_hal_uart.h"
#include "Driver/Inc/UartDriver.hpp"

using namespace testing;
using namespace Driver;

// Global mock instance for HAL UART
MockHAL_UART *mockHAL_UART;

class UartDriverTest : public Test
{
protected:
    UART_HandleTypeDef huart;
    UartDriver *driver;
    MockHAL_UART mockHAL_UART_Instance;

    void SetUp() override
    {
        mockHAL_UART = &mockHAL_UART_Instance; // Assign the global mock instance
        driver = new UartDriver(huart);
    }

    void TearDown() override
    {
        delete driver;
        mockHAL_UART = nullptr; // Reset the global mock instance
    }
};

TEST_F(UartDriverTest, TransmitShouldSucceed)
{
    // Prepare the data to be transmitted
    std::uint8_t data[] = {0x01, 0x02, 0x03};
    std::uint16_t size = sizeof(data);
    std::uint32_t timeout = 1000; // Timeout period in milliseconds

    // Initialize the driver
    EXPECT_TRUE(driver->initialize());

    // Start the driver to make it active for transmitting/receiving data
    EXPECT_TRUE(driver->start());

    // Expect the HAL_UART_Transmit function to be called with the correct parameters
    EXPECT_CALL(mockHAL_UART_Instance, HAL_UART_Transmit(&huart, data, size, timeout))
        .WillOnce(DoAll(
            // Capture and validate the parameters passed to HAL_UART_Transmit
            WithArgs<1, 2>([=](std::uint8_t *sentData, std::uint16_t sentSize)
                           {
                // Check that the size passed to the HAL function matches the expected size
                EXPECT_EQ(sentSize, size);

                // Check that the data passed to the HAL function matches the expected data
                for (std::uint16_t i = 0; i < sentSize; ++i) {
                    EXPECT_EQ(sentData[i], data[i]);
                } }),
            Return(HAL_OK)));

    // Execute the transmit method and verify that it returns the expected status
    UartExchangeStatus status = driver->transmit(data, size, timeout);
    EXPECT_EQ(status, UartExchangeStatus::Ok);
}

TEST_F(UartDriverTest, TransmitShouldFailOnError)
{
    std::uint8_t data[] = {0x01, 0x02, 0x03};
    std::uint16_t size = sizeof(data);
    std::uint32_t timeout = 1000; // Timeout period in milliseconds

    // Initialize the driver
    EXPECT_TRUE(driver->initialize());

    // Start the driver to make it active for transmitting/receiving data
    EXPECT_TRUE(driver->start());

    // Simulate a HAL error
    EXPECT_CALL(mockHAL_UART_Instance, HAL_UART_Transmit(&huart, data, size, timeout))
        .WillOnce(Return(HAL_ERROR));

    // Execute the transmit method and check the result
    UartExchangeStatus status = driver->transmit(data, size, timeout);
    EXPECT_EQ(status, UartExchangeStatus::ErrorFromHal);
}

TEST_F(UartDriverTest, ReceiveShouldSucceed)
{
    std::uint8_t buffer[3];
    std::uint16_t size = sizeof(buffer);
    std::uint32_t timeout = 1000; // Timeout period in milliseconds

    // Initialize the driver
    EXPECT_TRUE(driver->initialize());

    // Start the driver to make it active for transmitting/receiving data
    EXPECT_TRUE(driver->start());

    // Expect the HAL_UART_Receive function to be called with the correct parameters
    EXPECT_CALL(mockHAL_UART_Instance, HAL_UART_Receive(&huart, buffer, size, timeout))
        .WillOnce(Return(HAL_OK));

    // Execute the receive method and check the result
    UartExchangeStatus status = driver->receive(buffer, size, timeout);
    EXPECT_EQ(status, UartExchangeStatus::Ok);
}

TEST_F(UartDriverTest, ReceiveShouldFailOnTimeout)
{
    std::uint8_t buffer[3];
    std::uint16_t size = sizeof(buffer);
    std::uint32_t timeout = 1000;

    // Initialize the driver
    EXPECT_TRUE(driver->initialize());

    // Start the driver to make it active for transmitting/receiving data
    EXPECT_TRUE(driver->start());

    // Simulate a HAL timeout
    EXPECT_CALL(mockHAL_UART_Instance, HAL_UART_Receive(&huart, buffer, size, timeout))
        .WillOnce(Return(HAL_TIMEOUT));

    // Execute the receive method and check the result
    UartExchangeStatus status = driver->receive(buffer, size, timeout);
    EXPECT_EQ(status, UartExchangeStatus::Timeout);
}

TEST_F(UartDriverTest, ReceiveShouldFailOnError)
{
    std::uint8_t buffer[3];
    std::uint16_t size = sizeof(buffer);
    std::uint32_t timeout = 1000;

    // Initialize the driver
    EXPECT_TRUE(driver->initialize());

    // Start the driver to make it active for transmitting/receiving data
    EXPECT_TRUE(driver->start());

    // Simulate a HAL error
    EXPECT_CALL(mockHAL_UART_Instance, HAL_UART_Receive(&huart, buffer, size, timeout))
        .WillOnce(Return(HAL_ERROR));

    // Execute the receive method and check the result
    UartExchangeStatus status = driver->receive(buffer, size, timeout);
    EXPECT_EQ(status, UartExchangeStatus::ErrorFromHal);
}

TEST_F(UartDriverTest, StopShouldSucceed)
{
    // Initialize the driver
    EXPECT_TRUE(driver->initialize());

    // Start the driver to make it active for transmitting/receiving data
    EXPECT_TRUE(driver->start());

    EXPECT_TRUE(driver->stop());
    EXPECT_TRUE(driver->isInState(DriverState::State::Stop));
}

TEST_F(UartDriverTest, ResetShouldSucceed)
{
    // Initialize the driver
    EXPECT_TRUE(driver->initialize());

    // Start the driver to make it active for transmitting/receiving data
    EXPECT_TRUE(driver->start());

    EXPECT_TRUE(driver->reset());
    EXPECT_TRUE(driver->isInState(DriverState::State::Reset));
}
