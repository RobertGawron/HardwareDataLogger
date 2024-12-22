#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Driver/Inc/PulseCounterDriver.hpp"
#include <cstdint>
#include <array>

constexpr Driver::PulseCounterIdentifier id = Driver::PulseCounterIdentifier::bncA;

class PulseCounterDriverTest : public ::testing::Test
{
protected:
    Driver::PulseCounterDriver *driver;

    void SetUp() override
    {
        driver = new Driver::PulseCounterDriver(static_cast<Driver::PulseCounterIdentifier>(id));
    }

    void TearDown() override
    {
        delete driver;
    }
};

TEST_F(PulseCounterDriverTest, InitializeShouldResetCounters)
{
    EXPECT_TRUE(driver->onInitialize());
    EXPECT_EQ(driver->getMeasurement(), 0u);
}

TEST_F(PulseCounterDriverTest, StartShouldResetCounters)
{
    EXPECT_TRUE(driver->onStart());
    EXPECT_EQ(driver->getMeasurement(), 0u);
}

TEST_F(PulseCounterDriverTest, IncrementCounterIncreasesCorrectValue)
{
    auto idOfCounter = static_cast<std::uint8_t>(id);

    EXPECT_TRUE(driver->onInitialize());
    EXPECT_TRUE(driver->onStart());

    incrementPulseCounter(idOfCounter);
    EXPECT_EQ(driver->getMeasurement(), 1u);

    incrementPulseCounter(idOfCounter);
    EXPECT_EQ(driver->getMeasurement(), 2u);
}

TEST_F(PulseCounterDriverTest, ClearMeasurementResetsCounter)
{
    auto idOfCounter = static_cast<std::uint8_t>(id);

    EXPECT_TRUE(driver->onInitialize());
    EXPECT_TRUE(driver->onStart());

    incrementPulseCounter(idOfCounter);
    EXPECT_EQ(driver->getMeasurement(), 1u);

    driver->clearMeasurement();
    EXPECT_EQ(driver->getMeasurement(), 0u);
}
