#include "Driver/Interface/DriverState.hpp"

#include <gtest/gtest.h>

// A mock or stub class inheriting from DriverState for testing purposes
class TestDriver : public Driver::DriverState
{
public:
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

class FailingResetDriver : public Driver::DriverState
{
public:
    bool onInitialize() override { return true; }
    bool onStart() override { return true; }
    bool onStop() override { return true; }

    // Simulate failure
    bool onReset() override { return false; }
};

// Test fixture class for DriverState
class DriverStateTest : public ::testing::Test
{
public:
    void SetUp() override
    {
        ASSERT_EQ(getDriver().getState(), Driver::DriverState::State::Reset);
    }

    void TearDown() override
    {
        // Any cleanup can go here
    }

    // Getter for accessing private member
    TestDriver &getDriver() { return driver; }

private:
    TestDriver driver;
};

// Test the initialize method
TEST_F(DriverStateTest, InitializeTest)
{
    EXPECT_TRUE(getDriver().initialize());
    EXPECT_EQ(getDriver().getState(), Driver::DriverState::State::Initialized);
}

// Test the start method
TEST_F(DriverStateTest, StartTest)
{
    getDriver().initialize();
    EXPECT_TRUE(getDriver().start());
    EXPECT_EQ(getDriver().getState(), Driver::DriverState::State::Running);
}

// Test the stop method
TEST_F(DriverStateTest, StopTest)
{
    getDriver().initialize();
    getDriver().start();
    EXPECT_TRUE(getDriver().stop());
    EXPECT_EQ(getDriver().getState(), Driver::DriverState::State::Stop);
}

// Test the reset method
TEST_F(DriverStateTest, ResetTest)
{
    getDriver().initialize();
    getDriver().start();
    getDriver().stop();
    EXPECT_TRUE(getDriver().reset());
    EXPECT_EQ(getDriver().getState(), Driver::DriverState::State::Reset);
}

// Test that start fails if not initialized
TEST_F(DriverStateTest, StartFailsIfNotInitialized)
{
    EXPECT_FALSE(getDriver().start());
    EXPECT_EQ(getDriver().getState(), Driver::DriverState::State::Reset);
}

// Test that stop fails if not running
TEST_F(DriverStateTest, StopFailsIfNotRunning)
{
    EXPECT_FALSE(getDriver().stop());
    EXPECT_EQ(getDriver().getState(), Driver::DriverState::State::Reset);

    getDriver().initialize();
    EXPECT_FALSE(getDriver().stop());
    EXPECT_EQ(getDriver().getState(), Driver::DriverState::State::Initialized);
}

TEST_F(DriverStateTest, IsInStateReflectsCurrentState)
{
    // Initially in Reset
    EXPECT_TRUE(getDriver().isInState(Driver::DriverState::State::Reset));

    getDriver().initialize();
    EXPECT_TRUE(getDriver().isInState(Driver::DriverState::State::Initialized));
    EXPECT_FALSE(getDriver().isInState(Driver::DriverState::State::Reset));

    getDriver().start();
    EXPECT_TRUE(getDriver().isInState(Driver::DriverState::State::Running));

    getDriver().stop();
    EXPECT_TRUE(getDriver().isInState(Driver::DriverState::State::Stop));

    getDriver().reset();
    EXPECT_TRUE(getDriver().isInState(Driver::DriverState::State::Reset));
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
