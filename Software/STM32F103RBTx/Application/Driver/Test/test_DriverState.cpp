#include <gtest/gtest.h>
#include "Driver/Inc/DriverState.hpp"

// A mock or stub class inheriting from DriverState for testing purposes
class TestDriver : public Driver::DriverState
{
protected:
    bool onInitialize() override
    {
        // Custom initialization logic for testing
        return true;
    }

    bool onStart() override
    {
        // Custom start logic for testing
        return true;
    }

    bool onStop() override
    {
        // Custom stop logic for testing
        return true;
    }

    bool onReset() override
    {
        // Custom reset logic for testing
        return true;
    }
};

// Test fixture class for DriverState
class DriverStateTest : public ::testing::Test
{
protected:
    TestDriver driver;

    void SetUp() override
    {
        ASSERT_EQ(driver.getState(), Driver::DriverState::State::Reset);
    }
};

class FailingResetDriver : public Driver::DriverState
{
protected:
    bool onInitialize() override { return true; }
    bool onStart() override { return true; }
    bool onStop() override { return true; }

    // Simulate failure
    bool onReset() override { return false; }
};

// Test the initialize method
TEST_F(DriverStateTest, InitializeTest)
{
    EXPECT_TRUE(driver.initialize());
    EXPECT_EQ(driver.getState(), Driver::DriverState::State::Initialized);
}

// Test the start method
TEST_F(DriverStateTest, StartTest)
{
    driver.initialize();
    EXPECT_TRUE(driver.start());
    EXPECT_EQ(driver.getState(), Driver::DriverState::State::Running);
}

// Test the stop method
TEST_F(DriverStateTest, StopTest)
{
    driver.initialize();
    driver.start();
    EXPECT_TRUE(driver.stop());
    EXPECT_EQ(driver.getState(), Driver::DriverState::State::Stop);
}

// Test the reset method
TEST_F(DriverStateTest, ResetTest)
{
    driver.initialize();
    driver.start();
    driver.stop();
    EXPECT_TRUE(driver.reset());
    EXPECT_EQ(driver.getState(), Driver::DriverState::State::Reset);
}

// Test that start fails if not initialized
TEST_F(DriverStateTest, StartFailsIfNotInitialized)
{
    EXPECT_FALSE(driver.start());
    EXPECT_EQ(driver.getState(), Driver::DriverState::State::Reset);
}

// Test that stop fails if not running
TEST_F(DriverStateTest, StopFailsIfNotRunning)
{
    EXPECT_FALSE(driver.stop());
    EXPECT_EQ(driver.getState(), Driver::DriverState::State::Reset);

    driver.initialize();
    EXPECT_FALSE(driver.stop());
    EXPECT_EQ(driver.getState(), Driver::DriverState::State::Initialized);
}


TEST_F(DriverStateTest, IsInStateReflectsCurrentState)
{
    // Initially in Reset
    EXPECT_TRUE(driver.isInState(Driver::DriverState::State::Reset));

    driver.initialize();
    EXPECT_TRUE(driver.isInState(Driver::DriverState::State::Initialized));
    EXPECT_FALSE(driver.isInState(Driver::DriverState::State::Reset));

    driver.start();
    EXPECT_TRUE(driver.isInState(Driver::DriverState::State::Running));

    driver.stop();
    EXPECT_TRUE(driver.isInState(Driver::DriverState::State::Stop));

    driver.reset();
    EXPECT_TRUE(driver.isInState(Driver::DriverState::State::Reset));
}

TEST(DriverStateNegativeTest, ResetFailsWhenOnResetFails)
{
    FailingResetDriver driver;
    driver.initialize();
    driver.start();
    driver.stop();

    EXPECT_FALSE(driver.reset());
    // State should remain unchanged from last successful state
    EXPECT_EQ(driver.getState(), Driver::DriverState::State::Stop);
}
