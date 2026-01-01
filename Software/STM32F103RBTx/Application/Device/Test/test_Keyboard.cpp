#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

import Device.Keyboard;
import Device.KeyAction;
import Driver.KeyboardDriver;
import Driver.KeyState;
import Driver.KeyId;

// --- Mocks ---

class MockKeyboardDriver : public Driver::KeyboardDriver
{
public:
    MOCK_METHOD(bool, onInit, (), (noexcept));
    MOCK_METHOD(bool, onStart, (), (noexcept));
    MOCK_METHOD(bool, onStop, (), (noexcept));
    MOCK_METHOD(bool, tick, (), ());
    MOCK_METHOD(Driver::KeyState, getKeyState, (Driver::KeyId key), (const, override));
};

// --- Test Fixture ---

class KeyboardTest : public ::testing::Test
{
private:
    MockKeyboardDriver mockDriver;
    std::unique_ptr<Device::Keyboard> keyboard;

protected:
    void SetUp() override
    {
        keyboard = std::make_unique<Device::Keyboard>(mockDriver);
    }

public:
    MockKeyboardDriver &getMockDriver() { return mockDriver; }
    Device::Keyboard &getKeyboard() { return *keyboard; }
};

// --- Test Cases ---

TEST_F(KeyboardTest, InitCallsDriverInit)
{
    EXPECT_CALL(getMockDriver(), onInit()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(getKeyboard().init());
}

TEST_F(KeyboardTest, StartCallsDriverStart)
{
    // Must initialize first due to state machine
    EXPECT_CALL(getMockDriver(), onInit()).WillOnce(::testing::Return(true));
    ASSERT_TRUE(getKeyboard().init());

    EXPECT_CALL(getMockDriver(), onStart()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(getKeyboard().start());
}

TEST_F(KeyboardTest, TickTransitionsToPressStart)
{
    // Initialize and start the keyboard
    EXPECT_CALL(getMockDriver(), onInit()).WillOnce(::testing::Return(true));
    ASSERT_TRUE(getKeyboard().init());

    EXPECT_CALL(getMockDriver(), onStart()).WillOnce(::testing::Return(true));
    ASSERT_TRUE(getKeyboard().start());

    // Setup tick behavior
    EXPECT_CALL(getMockDriver(), tick()).WillOnce(::testing::Return(true));

    // Default behavior for other keys
    EXPECT_CALL(getMockDriver(), getKeyState(::testing::_))
        .Times(::testing::AtLeast(1))
        .WillRepeatedly(::testing::Return(Driver::KeyState::NotPressed));

    // Specific behavior for Up key
    EXPECT_CALL(getMockDriver(), getKeyState(Driver::KeyId::Up))
        .WillOnce(::testing::Return(Driver::KeyState::Pressed));

    EXPECT_TRUE(getKeyboard().tick());

    EXPECT_EQ(getKeyboard().getKeyState(Driver::KeyId::Up),
              Device::KeyAction::PRESS_START);
}

TEST_F(KeyboardTest, TickHandlesCompleteKeyPressSequence)
{
    // Initialize and start the keyboard
    EXPECT_CALL(getMockDriver(), onInit()).WillOnce(::testing::Return(true));
    ASSERT_TRUE(getKeyboard().init());

    EXPECT_CALL(getMockDriver(), onStart()).WillOnce(::testing::Return(true));
    ASSERT_TRUE(getKeyboard().start());

    // Setup tick behavior for all ticks
    EXPECT_CALL(getMockDriver(), tick())
        .Times(4)
        .WillRepeatedly(::testing::Return(true));

    // Default behavior for other keys
    EXPECT_CALL(getMockDriver(), getKeyState(::testing::_))
        .Times(::testing::AtLeast(1))
        .WillRepeatedly(::testing::Return(Driver::KeyState::NotPressed));

    // Specific behavior for Down key: press, hold, hold, release
    EXPECT_CALL(getMockDriver(), getKeyState(Driver::KeyId::Down))
        .WillOnce(::testing::Return(Driver::KeyState::Pressed))     // Tick 1: NotPressed -> PressStart
        .WillOnce(::testing::Return(Driver::KeyState::Pressed))     // Tick 2: PressStart -> PressHold
        .WillOnce(::testing::Return(Driver::KeyState::Pressed))     // Tick 3: PressHold -> PressHold
        .WillOnce(::testing::Return(Driver::KeyState::NotPressed)); // Tick 4: PressHold -> PressEndShort

    EXPECT_TRUE(getKeyboard().tick());
    EXPECT_EQ(getKeyboard().getKeyState(Driver::KeyId::Down),
              Device::KeyAction::PRESS_START);

    EXPECT_TRUE(getKeyboard().tick());
    EXPECT_EQ(getKeyboard().getKeyState(Driver::KeyId::Down),
              Device::KeyAction::PRESS_HOLD);

    EXPECT_TRUE(getKeyboard().tick());
    EXPECT_EQ(getKeyboard().getKeyState(Driver::KeyId::Down),
              Device::KeyAction::PRESS_HOLD);

    EXPECT_TRUE(getKeyboard().tick());
    EXPECT_EQ(getKeyboard().getKeyState(Driver::KeyId::Down),
              Device::KeyAction::PRESS_END_SHORT);
}

TEST_F(KeyboardTest, GetKeyStateReturnsFailForInvalidKey)
{
    const Driver::KeyId key = static_cast<Driver::KeyId>(99);

    EXPECT_EQ(getKeyboard().getKeyState(key), Device::KeyAction::FAIL);
}