#include "Driver/Hardware/Inc/UartDriver.hpp"
#include "Driver/Interface/UartExchangeStatus.hpp"
#include "Driver/Interface/DriverState.hpp"

#include "stm32f1xx_hal_uart.h"
#include "stm32f1xx_hal_def.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdint>
#include <memory>
#include <array>
#include <algorithm>
#include <ostream>

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

// --- Matcher Class ---
class UartDataMatcher
{
public:
    explicit UartDataMatcher(const std::array<std::uint8_t, 3> &expectedData)
        : expected(expectedData) {}

    // GMOCK REQUIREMENT: This method name is mandated by the library.
    // It must be "MatchAndExplain" (PascalCase) to compile.
    bool MatchAndExplain(std::uint8_t *arg, ::testing::MatchResultListener *listener) const
    {
        if (arg == nullptr)
        {
            // Using 'listener' here prevents the "unused parameter" error
            *listener << "the received pointer was null";
            return false;
        }

        return std::equal(expected.begin(), expected.end(), arg);
    }

    // GMOCK REQUIREMENT: Must be "DescribeTo" (PascalCase).
    static void DescribeTo(std::ostream *os)
    {
        *os << "is data equal to expected array";
    }

    // GMOCK REQUIREMENT: Must be "DescribeNegationTo" (PascalCase).
    static void DescribeNegationTo(std::ostream *os)
    {
        *os << "is data NOT equal to expected array";
    }

private:
    std::array<std::uint8_t, 3> expected;
};

// --- Factory Function (Forward Declaration) ---
namespace
{
    ::testing::PolymorphicMatcher<UartDataMatcher> isDataEqualTo(const std::array<std::uint8_t, 3> &data);
}

// --- Factory Function Implementation ---
namespace
{
    ::testing::PolymorphicMatcher<UartDataMatcher> isDataEqualTo(const std::array<std::uint8_t, 3> &data)
    {
        return ::testing::MakePolymorphicMatcher(UartDataMatcher(data));
    }
}

// --- Test Cases ---

TEST_F(UartDriverTest, TransmitShouldSucceed)
{
    // Arrange
    std::array<std::uint8_t, 3> data = {0x01, 0x02, 0x03};
    const std::uint32_t timeout = 1000;

    getDriver().initialize();
    getDriver().start();

    EXPECT_CALL(getMockHAL(), HAL_UART_Transmit(
                                  &getHuart(),
                                  isDataEqualTo(data),
                                  static_cast<std::uint16_t>(data.size()),
                                  timeout))
        .WillOnce(::testing::Return(HAL_OK));

    // Act
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
