#include "stm32f1xx_hal_uart.h"
#include "stm32f1xx_hal_def.h"
#include "Driver/Hardware/Inc/UartDriver.hpp"
#include "Driver/Interface/UartExchangeStatus.hpp"
#include "Driver/Interface/DriverState.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include <memory>

// Global mock instance pointer for the HAL C-linkage
MockHAL_UART *mockHAL_UART = nullptr;

// --- Test Fixture ---

class UartDriverTest : public ::testing::Test
{
private:
    // All fields are now private
    UART_HandleTypeDef huart{};
    MockHAL_UART mockHAL_UART_Instance;
    std::unique_ptr<Driver::UartDriver> driver;

protected:
    void SetUp() override
    {
        // Assign the global mock pointer to the instance inside this fixture
        mockHAL_UART = &mockHAL_UART_Instance;
        driver = std::make_unique<Driver::UartDriver>(huart);
    }

    void TearDown() override
    {
        mockHAL_UART = nullptr;
    }

public:
    // Public Getters
    Driver::UartDriver &getDriver() { return *driver; }
    MockHAL_UART &getMockHAL() { return mockHAL_UART_Instance; }
    UART_HandleTypeDef &getHuart() { return huart; }
};

// --- Test Cases ---

TEST_F(UartDriverTest, TransmitShouldSucceed)
{
    // Arrange
    // 1. Use std::array instead of raw C-array
    std::array<std::uint8_t, 3> data = {0x01, 0x02, 0x03};
    const std::uint32_t timeout = 1000;

    getDriver().initialize();
    getDriver().start();

    EXPECT_CALL(getMockHAL(), HAL_UART_Transmit(&getHuart(), ::testing::_, ::testing::_, timeout))
        .WillOnce(::testing::DoAll(
            ::testing::WithArgs<1, 2>([&data](std::uint8_t *sentData, std::uint16_t sentSize)
                                      {
                // 2. Validate pointer is not null to satisfy static analysis
                EXPECT_NE(sentData, nullptr);
                
                // 3. Check size match
                EXPECT_EQ(sentSize, data.size());

                // 4. Use std::equal instead of manual loop
                // This prevents "unsafe buffer access" warnings because the STL handles the iteration logic
                if (sentData != nullptr && sentSize == data.size()) {
                    EXPECT_TRUE(std::equal(data.begin(), data.end(), sentData));
                } }),
            ::testing::Return(HAL_OK)));

    // Act
    // 5. Use .data() to get the raw pointer required by the C interface
    const Driver::UartExchangeStatus status = getDriver().transmit(data.data(), data.size(), timeout);

    // Assert
    EXPECT_EQ(status, Driver::UartExchangeStatus::Ok);
}

TEST_F(UartDriverTest, TransmitShouldFailOnError)
{
    std::uint8_t data[] = {0x01, 0x02, 0x03};
    const std::uint16_t size = sizeof(data);
    const std::uint32_t timeout = 1000;

    getDriver().initialize();
    getDriver().start();

    EXPECT_CALL(getMockHAL(), HAL_UART_Transmit(&getHuart(), data, size, timeout))
        .WillOnce(::testing::Return(HAL_ERROR));

    const Driver::UartExchangeStatus status = getDriver().transmit(data, size, timeout);
    EXPECT_EQ(status, Driver::UartExchangeStatus::ErrorFromHal);
}

TEST_F(UartDriverTest, ReceiveShouldSucceed)
{
    std::uint8_t buffer[3];
    const std::uint16_t size = sizeof(buffer);
    const std::uint32_t timeout = 1000;

    getDriver().initialize();
    getDriver().start();

    EXPECT_CALL(getMockHAL(), HAL_UART_Receive(&getHuart(), buffer, size, timeout))
        .WillOnce(::testing::Return(HAL_OK));

    const Driver::UartExchangeStatus status = getDriver().receive(buffer, size, timeout);
    EXPECT_EQ(status, Driver::UartExchangeStatus::Ok);
}

TEST_F(UartDriverTest, ReceiveShouldFailOnTimeout)
{
    std::uint8_t buffer[3];
    const std::uint16_t size = sizeof(buffer);
    const std::uint32_t timeout = 1000;

    getDriver().initialize();
    getDriver().start();

    EXPECT_CALL(getMockHAL(), HAL_UART_Receive(&getHuart(), buffer, size, timeout))
        .WillOnce(::testing::Return(HAL_TIMEOUT));

    const Driver::UartExchangeStatus status = getDriver().receive(buffer, size, timeout);
    EXPECT_EQ(status, Driver::UartExchangeStatus::Timeout);
}

TEST_F(UartDriverTest, StopShouldSucceed)
{
    getDriver().initialize();
    getDriver().start();

    EXPECT_TRUE(getDriver().stop());
    EXPECT_TRUE(getDriver().isInState(Driver::DriverState::State::Stop));
}

TEST_F(UartDriverTest, ResetShouldSucceed)
{
    getDriver().initialize();
    getDriver().start();

    EXPECT_TRUE(getDriver().reset());
    EXPECT_TRUE(getDriver().isInState(Driver::DriverState::State::Reset));
}
