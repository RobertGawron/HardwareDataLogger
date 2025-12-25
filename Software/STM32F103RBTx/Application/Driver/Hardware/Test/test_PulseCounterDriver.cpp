#include "Driver/Interface/PulseCounterId.hpp"
#include "Driver/Hardware/Inc/PulseCounterDriver.hpp"

#include <gtest/gtest.h>
#include <cstdint>
#include <memory>

namespace
{
    constexpr Driver::PulseCounterId id = Driver::PulseCounterId::bncA;
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
        driver = std::make_unique<Driver::PulseCounterDriver>(static_cast<Driver::PulseCounterId>(id));
    }

public:
    // Public Getter
    Driver::PulseCounterDriver &getDriver() { return *driver; }
};

// --- Test Cases ---

TEST_F(PulseCounterDriverTest, InitializeShouldResetCounters)
{
    EXPECT_TRUE(getDriver().onInitialize());
    EXPECT_EQ(getDriver().getMeasurement(), 0u);
}

TEST_F(PulseCounterDriverTest, StartShouldResetCounters)
{
    EXPECT_TRUE(getDriver().onStart());
    EXPECT_EQ(getDriver().getMeasurement(), 0u);
}

TEST_F(PulseCounterDriverTest, IncrementCounterIncreasesCorrectValue)
{
    auto idOfCounter = static_cast<std::uint8_t>(id);

    EXPECT_TRUE(getDriver().onInitialize());
    EXPECT_TRUE(getDriver().onStart());

    incrementPulseCounter(idOfCounter);
    EXPECT_EQ(getDriver().getMeasurement(), 1u);

    incrementPulseCounter(idOfCounter);
    EXPECT_EQ(getDriver().getMeasurement(), 2u);
}

TEST_F(PulseCounterDriverTest, ClearMeasurementResetsCounter)
{
    auto idOfCounter = static_cast<std::uint8_t>(id);

    EXPECT_TRUE(getDriver().onInitialize());
    EXPECT_TRUE(getDriver().onStart());

    incrementPulseCounter(idOfCounter);
    EXPECT_EQ(getDriver().getMeasurement(), 1u);

    getDriver().clearMeasurement();
    EXPECT_EQ(getDriver().getMeasurement(), 0u);
}

TEST_F(PulseCounterDriverTest, StopShouldClearCounter)
{
    auto idOfCounter = static_cast<std::uint8_t>(id);

    getDriver().onInitialize();
    getDriver().onStart();

    incrementPulseCounter(idOfCounter);
    EXPECT_EQ(getDriver().getMeasurement(), 1u);

    EXPECT_TRUE(getDriver().onStop());
    EXPECT_EQ(getDriver().getMeasurement(), 0u); // Must be cleared
}

TEST_F(PulseCounterDriverTest, ResetShouldReturnTrue)
{
    EXPECT_TRUE(getDriver().onReset()); // Only verifies return value
}
