#include "Driver/Interface/PulseCounterId.hpp"
#include "Driver/Hardware/Inc/PulseCounterDriver.hpp"

#include <gtest/gtest.h>
#include <cstdint>
#include <memory>

namespace
{
    constexpr Driver::PulseCounterId counterId = Driver::PulseCounterId::bncA;
}

// --- Test Fixture ---

class PulseCounterDriverTest : public ::testing::Test
{
private:
    // Encapsulated field
    std::unique_ptr<Driver::PulseCounterDriver> driver;

protected:
    void SetUp() override
    {
        driver = std::make_unique<Driver::PulseCounterDriver>(static_cast<Driver::PulseCounterId>(counterId));
    }

public:
    // Public Getter
    Driver::PulseCounterDriver &getDriver() { return *driver; }
};

// --- Test Cases ---

TEST_F(PulseCounterDriverTest, InitializeShouldResetCounters)
{
    EXPECT_TRUE(getDriver().onInitialize());
    EXPECT_EQ(getDriver().getMeasurement(), 0U);
}

TEST_F(PulseCounterDriverTest, StartShouldResetCounters)
{
    EXPECT_TRUE(getDriver().onStart());
    EXPECT_EQ(getDriver().getMeasurement(), 0U);
}

TEST_F(PulseCounterDriverTest, IncrementCounterIncreasesCorrectValue)
{
    const auto idOfCounter = static_cast<std::uint8_t>(counterId);

    EXPECT_TRUE(getDriver().onInitialize());
    EXPECT_TRUE(getDriver().onStart());

    incrementPulseCounter(idOfCounter);
    EXPECT_EQ(getDriver().getMeasurement(), 1U);

    incrementPulseCounter(idOfCounter);
    EXPECT_EQ(getDriver().getMeasurement(), 2U);
}

TEST_F(PulseCounterDriverTest, ClearMeasurementResetsCounter)
{
    const auto idOfCounter = static_cast<std::uint8_t>(counterId);

    EXPECT_TRUE(getDriver().onInitialize());
    EXPECT_TRUE(getDriver().onStart());

    incrementPulseCounter(idOfCounter);
    EXPECT_EQ(getDriver().getMeasurement(), 1U);

    getDriver().clearMeasurement();
    EXPECT_EQ(getDriver().getMeasurement(), 0U);
}

TEST_F(PulseCounterDriverTest, StopShouldClearCounter)
{
    const auto idOfCounter = static_cast<std::uint8_t>(counterId);

    getDriver().onInitialize();
    getDriver().onStart();

    incrementPulseCounter(idOfCounter);
    EXPECT_EQ(getDriver().getMeasurement(), 1U);

    EXPECT_TRUE(getDriver().onStop());
    EXPECT_EQ(getDriver().getMeasurement(), 0U); // Must be cleared
}

TEST_F(PulseCounterDriverTest, ResetShouldReturnTrue)
{
    EXPECT_TRUE(getDriver().onReset()); // Only verifies return value
}
