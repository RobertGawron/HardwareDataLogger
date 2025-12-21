#include "Device/Inc/Keyboard.hpp"
#include "Driver/Interfaces/IKeyboardDriver.hpp"
#include "Driver/Inc/KeyboardKeyState.hpp"
#include "Driver/Inc/KeyboardKeyIdentifier.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

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
    MOCK_METHOD(Driver::KeyboardKeyState, getKeyState, (Driver::KeyboardKeyIdentifier key), (const, override));
};

class KeyboardTest : public ::testing::Test
{
protected:
    MockKeyboardDriver mockDriver;
    Device::Keyboard *keyboard;

    void SetUp() override
    {
        keyboard = new Device::Keyboard(mockDriver);
    }

    void TearDown() override
    {
        delete keyboard;
    }
};

TEST_F(KeyboardTest, InitSuccessWhenDriverInitAndStartSucceed)
{
    EXPECT_CALL(mockDriver, initialize()).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockDriver, start()).WillOnce(::testing::Return(true));
    EXPECT_TRUE(keyboard->init());
}

TEST_F(KeyboardTest, InitFailsWhenDriverInitFails)
{
    EXPECT_CALL(mockDriver, initialize()).WillOnce(::testing::Return(false));
    EXPECT_FALSE(keyboard->init());
}

TEST_F(KeyboardTest, TickTransitionsToPressStart)
{
    EXPECT_CALL(mockDriver, getKeyState(::testing::_))
        .Times(::testing::AtLeast(1))
        .WillRepeatedly(::testing::Return(Driver::KeyboardKeyState::NotPressed));

    EXPECT_CALL(mockDriver, getKeyState(Driver::KeyboardKeyIdentifier::Up))
        .WillOnce(::testing::Return(Driver::KeyboardKeyState::Pressed));

    keyboard->tick();

    EXPECT_EQ(keyboard->getKeyState(Driver::KeyboardKeyIdentifier::Up), Device::KeyboardKeyActionState::PressStart);
}

TEST_F(KeyboardTest, TickHandlesKeyHoldAndReleaseShort)
{
    EXPECT_CALL(mockDriver, getKeyState(::testing::_))
        .Times(::testing::AtLeast(1))
        .WillRepeatedly(::testing::Return(Driver::KeyboardKeyState::NotPressed));

    EXPECT_CALL(mockDriver, getKeyState(Driver::KeyboardKeyIdentifier::Down))
        .WillOnce(::testing::Return(Driver::KeyboardKeyState::Pressed))
        .WillOnce(::testing::Return(Driver::KeyboardKeyState::Pressed))
        .WillOnce(::testing::Return(Driver::KeyboardKeyState::NotPressed));

    keyboard->tick();
    keyboard->tick();
    keyboard->tick();

    EXPECT_EQ(keyboard->getKeyState(Driver::KeyboardKeyIdentifier::Down), Device::KeyboardKeyActionState::PressEndShort);
}

TEST_F(KeyboardTest, TickHandlesFailState)
{
    EXPECT_EQ(keyboard->getKeyState(static_cast<Driver::KeyboardKeyIdentifier>(99)), Device::KeyboardKeyActionState::Fail);
}
