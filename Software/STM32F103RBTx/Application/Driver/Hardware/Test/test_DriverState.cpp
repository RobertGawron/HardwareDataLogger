/**
 * @file test_DriverComponent.cpp
 * @brief Modern C++23 tests for DriverComponent state machine
 */

#include "Driver/Interface/DriverComponent.hpp"

#include <gtest/gtest.h>

// Mock driver for testing
class TestDriver : public Driver::DriverComponent
{
public:
    [[nodiscard]] bool onInit() noexcept override { return initResult; }
    [[nodiscard]] bool onStart() noexcept override { return startResult; }
    [[nodiscard]] bool onStop() noexcept override { return stopResult; }

    // Test control
    bool initResult{true};
    bool startResult{true};
    bool stopResult{true};
};

// Test fixture
class DriverComponentTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        ASSERT_EQ(driver.getState(), Driver::DriverComponent::State::IN_RESETING);
    }

    TestDriver driver;
};

// ==================== Initialization Tests ====================

TEST_F(DriverComponentTest, InitTransitionsToInitializing)
{
    EXPECT_TRUE(driver.init());
    // Note: After init(), state remains IN_INITIALIZING (not a final state)
    EXPECT_EQ(driver.getState(), Driver::DriverComponent::State::IN_INITIALIZING);
}

TEST_F(DriverComponentTest, InitFailsWhenOnInitFails)
{
    driver.initResult = false;
    EXPECT_FALSE(driver.init());
    EXPECT_EQ(driver.getState(), Driver::DriverComponent::State::IN_INITIALIZING);
}

// ==================== Start Tests ====================

TEST_F(DriverComponentTest, StartTransitionsToRunning)
{
    driver.init();
    EXPECT_TRUE(driver.start());
    EXPECT_EQ(driver.getState(), Driver::DriverComponent::State::RUNNING);
}

TEST_F(DriverComponentTest, StartFailsIfNotInitialized)
{
    EXPECT_FALSE(driver.start());
    EXPECT_EQ(driver.getState(), Driver::DriverComponent::State::IN_RESETING);
}

TEST_F(DriverComponentTest, StartFailsWhenOnStartFails)
{
    driver.init();
    driver.startResult = false;
    EXPECT_FALSE(driver.start());
    // State is IN_STARTING but onStart failed, so doesn't reach IN_RUNNING
    EXPECT_EQ(driver.getState(), Driver::DriverComponent::State::IN_STARTING);
}

// ==================== Stop Tests ====================

TEST_F(DriverComponentTest, StopTransitionsToStopping)
{
    driver.init();
    driver.start();
    EXPECT_TRUE(driver.stop());
    EXPECT_EQ(driver.getState(), Driver::DriverComponent::State::IN_STOPPING);
}

TEST_F(DriverComponentTest, StopFailsIfNotRunning)
{
    EXPECT_FALSE(driver.stop());
    EXPECT_EQ(driver.getState(), Driver::DriverComponent::State::IN_RESETING);

    driver.init();
    EXPECT_FALSE(driver.stop());
    EXPECT_EQ(driver.getState(), Driver::DriverComponent::State::IN_INITIALIZING);
}

TEST_F(DriverComponentTest, StopFailsWhenOnStopFails)
{
    driver.init();
    driver.start();
    driver.stopResult = false;
    EXPECT_FALSE(driver.stop());
    EXPECT_EQ(driver.getState(), Driver::DriverComponent::State::IN_STOPPING);
}

// ==================== State Transition Tests ====================

TEST_F(DriverComponentTest, FullLifecycle)
{
    // Reset -> Init -> Start -> Stop
    EXPECT_EQ(driver.getState(), Driver::DriverComponent::State::IN_RESETING);

    EXPECT_TRUE(driver.init());
    EXPECT_EQ(driver.getState(), Driver::DriverComponent::State::IN_INITIALIZING);

    EXPECT_TRUE(driver.start());
    EXPECT_EQ(driver.getState(), Driver::DriverComponent::State::RUNNING);

    EXPECT_TRUE(driver.stop());
    EXPECT_EQ(driver.getState(), Driver::DriverComponent::State::IN_STOPPING);
}

TEST_F(DriverComponentTest, StoppingAllowsRestart)
{
    driver.init();
    driver.start();
    driver.stop();
    EXPECT_EQ(driver.getState(), Driver::DriverComponent::State::IN_STOPPING);

    // From STOPPING, can restart: STOPPING -> STARTING -> RUNNING
    EXPECT_TRUE(driver.start());
    EXPECT_EQ(driver.getState(), Driver::DriverComponent::State::RUNNING);
}

// ==================== Invalid Transition Tests ====================

TEST_F(DriverComponentTest, InvalidTransitionsAreRejected)
{
    // Cannot start from RESET
    EXPECT_FALSE(driver.start());
    EXPECT_EQ(driver.getState(), Driver::DriverComponent::State::IN_RESETING);

    // Cannot stop from INITIALIZED
    driver.init();
    EXPECT_FALSE(driver.stop());
    EXPECT_EQ(driver.getState(), Driver::DriverComponent::State::IN_INITIALIZING);
}