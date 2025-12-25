#include "Driver/Hardware/Inc/UartDriver.hpp"
#include "Driver/Interface/UartStatus.hpp"
#include "Driver/Interface/DriverState.hpp"

#include "stm32f1xx_hal_uart.h"
#include "stm32f1xx_hal_def.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdint>
#include <memory>
#include <array>
#include <span>
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
    const std::span<const std::uint8_t> txData{data.data(), data.size()};
    const Driver::UartStatus status = getDriver().transmit(txData, timeout);

    // Assert
    EXPECT_EQ(status, Driver::UartStatus::Ok);
}

TEST_F(UartDriverTest, TransmitShouldFailOnError)
{
    std::array<std::uint8_t, 3> data = {0x01, 0x02, 0x03};
    const std::uint32_t timeout = 1000;

    getDriver().initialize();
    getDriver().start();

    EXPECT_CALL(getMockHAL(), HAL_UART_Transmit(
                                  &getHuart(),
                                  ::testing::_,
                                  static_cast<std::uint16_t>(data.size()),
                                  timeout))
        .WillOnce(::testing::Return(HAL_ERROR));

    const std::span<const std::uint8_t> txData{data.data(), data.size()};
    const Driver::UartStatus status = getDriver().transmit(txData, timeout);
    EXPECT_EQ(status, Driver::UartStatus::ErrorFromHal);
}

TEST_F(UartDriverTest, ReceiveShouldSucceed)
{
    std::array<std::uint8_t, 3> buffer = {0x00, 0x00, 0x00};
    const std::uint32_t timeout = 1000;

    getDriver().initialize();
    getDriver().start();

    EXPECT_CALL(getMockHAL(), HAL_UART_Receive(
                                  &getHuart(),
                                  buffer.data(),
                                  static_cast<std::uint16_t>(buffer.size()),
                                  timeout))
        .WillOnce(::testing::Return(HAL_OK));

    const std::span<std::uint8_t> rxData{buffer.data(), buffer.size()};
    const Driver::UartStatus status = getDriver().receive(rxData, timeout);
    EXPECT_EQ(status, Driver::UartStatus::Ok);
}

TEST_F(UartDriverTest, ReceiveShouldFailOnTimeout)
{
    std::array<std::uint8_t, 3> buffer = {0x00, 0x00, 0x00};
    const std::uint32_t timeout = 1000;

    getDriver().initialize();
    getDriver().start();

    EXPECT_CALL(getMockHAL(), HAL_UART_Receive(
                                  &getHuart(),
                                  buffer.data(),
                                  static_cast<std::uint16_t>(buffer.size()),
                                  timeout))
        .WillOnce(::testing::Return(HAL_TIMEOUT));

    const std::span<std::uint8_t> rxData{buffer.data(), buffer.size()};
    const Driver::UartStatus status = getDriver().receive(rxData, timeout);
    EXPECT_EQ(status, Driver::UartStatus::Timeout);
}

TEST_F(UartDriverTest, TransmitShouldFailWhenNotRunning)
{
    std::array<std::uint8_t, 3> data = {0x01, 0x02, 0x03};
    const std::uint32_t timeout = 1000;

    // Don't start the driver
    getDriver().initialize();

    const std::span<const std::uint8_t> txData{data.data(), data.size()};
    const Driver::UartStatus status = getDriver().transmit(txData, timeout);
    EXPECT_EQ(status, Driver::UartStatus::DriverInIncorrectMode);
}

TEST_F(UartDriverTest, TransmitShouldFailOnEmptySpan)
{
    const std::uint32_t timeout = 1000;

    getDriver().initialize();
    getDriver().start();

    const std::span<const std::uint8_t> emptySpan{};
    const Driver::UartStatus status = getDriver().transmit(emptySpan, timeout);
    EXPECT_EQ(status, Driver::UartStatus::ErrorFromHal);
}