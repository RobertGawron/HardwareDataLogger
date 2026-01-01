#include "Device/Inc/Keyboard.hpp"
#include "Device/Inc/KeyActionState.hpp"
#include "Driver/Interface/IKeyboardDriver.hpp"
#include "Driver/Interface/KeyState.hpp"
#include "Driver/Interface/KeyIdentifier.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// --- Mocks ---

class MockKeyboardDriver : public Driver::IKeyboardDriver
{
public:
    MOCK_METHOD(bool, initialize, (), (override));
    MOCK_METHOD(bool, start, (), (override));
    MOCK_METHOD(bool, stop, (), (override));
    MOCK_METHOD(bool, reset, (), (override));
    MOCK_METHOD(bool, onInitialize, (), (override));
    MOCK_METHOD(bool, onStart, (), (override));
    MOCK_METHOD(bool, onStop, (), (override));
    MOCK_METHOD(bool, onReset, (), (override));
    MOCK_METHOD(bool, tick, (), (override));
    MOCK_METHOD(Driver::KeyState, getKeyState, (Driver::KeyIdentifier key), (const, override));
};

// --- Test Fixture ---

class KeyboardTest : public ::testing::Test
{
private:
    // Encapsulated fields
    MockKeyboardDriver mockDriver;
    std::unique_ptr<Device::Keyboard> keyboard;

protected:
    void SetUp() override
    {
        keyboard = std::make_unique<Device::Keyboard>(mockDriver);
    }

public:
    // Public Getters
    MockKeyboardDriver &getMockDriver() { return mockDriver; }
    Device::Keyboard &getKeyboard() { return *keyboard; }
};

// --- Test Cases ---

TEST_F(KeyboardTest, InitSuccessWhenDriverInitAndStartSucceed)
{
    EXPECT_CALL(getMockDriver(), initialize()).WillOnce(::testing::Return(true));
    EXPECT_CALL(getMockDriver(), start()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(getKeyboard().init());
}

TEST_F(KeyboardTest, InitFailsWhenDriverInitFails)
{
    EXPECT_CALL(getMockDriver(), initialize()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(getKeyboard().init());
}

TEST_F(KeyboardTest, TickTransitionsToPressStart)
{
    // Default behavior for other keys
    EXPECT_CALL(getMockDriver(), getKeyState(::testing::_))
        .Times(::testing::AtLeast(1))
        .WillRepeatedly(::testing::Return(Driver::KeyState::NotPressed));

    // Specific behavior for Up key
    EXPECT_CALL(getMockDriver(), getKeyState(Driver::KeyIdentifier::Up))
        .WillOnce(::testing::Return(Driver::KeyState::Pressed));

    getKeyboard().tick();

    EXPECT_EQ(getKeyboard().getKeyState(Driver::KeyIdentifier::Up),
              Device::KeyActionState::PressStart);
}

TEST_F(KeyboardTest, TickHandlesKeyHoldAndReleaseShort)
{
    EXPECT_CALL(getMockDriver(), getKeyState(::testing::_))
        .Times(::testing::AtLeast(1))
        .WillRepeatedly(::testing::Return(Driver::KeyState::NotPressed));

    EXPECT_CALL(getMockDriver(), getKeyState(Driver::KeyIdentifier::Down))
        .WillOnce(::testing::Return(Driver::KeyState::Pressed))
        .WillOnce(::testing::Return(Driver::KeyState::Pressed))
        .WillOnce(::testing::Return(Driver::KeyState::NotPressed));

    getKeyboard().tick(); // PressStart
    getKeyboard().tick(); // PressHold
    getKeyboard().tick(); // PressEndShort

    EXPECT_EQ(getKeyboard().getKeyState(Driver::KeyIdentifier::Down),
              Device::KeyActionState::PressEndShort);
}
/*
TEST_F(KeyboardTest, TickHandlesFailState)
{
    // Accessing an invalid identifier should return Fail state

    const Driver::KeyIdentifier key = static_cast<Driver::KeyIdentifier>(99);

    EXPECT_EQ(
        getKeyboard().getKeyState(key),
        Device::KeyActionState::Fail);
}*/
