#include "Keyboard.hpp"
#include "KeyboardKeyState.hpp"
#include "KeyboardKeyActionState.hpp"

namespace Device
{

	Keyboard::Keyboard(::Driver::IKeyboardDriver &_keyboardDriver) : keyboardDriver(_keyboardDriver)
	{
		for (uint8_t i = 0u; i < AmountOfKeys; i++)
		{
			keyActionState[i] = KeyboardKeyActionState::PressNot;
		}
	}

	void Keyboard::init()
	{
		keyboardDriver.init();
	}

	void Keyboard::tick()
	{
		keyboardDriver.tick();

		for (uint8_t i = 0u; i < AmountOfKeys; i++)
		{
			::Driver::KeyboardKeyId keyId = static_cast<::Driver::KeyboardKeyId>(i);
			::Driver::KeyboardKeyState newState = keyboardDriver.getState(keyId);

			KeyboardKeyActionState stateToSet = KeyboardKeyActionState::PressNot;

			switch (keyActionState[i])
			{
			case KeyboardKeyActionState::PressNot:
			{
				// user ended pressing the button
				if (newState == Driver::KeyboardKeyState::Pressed)
				{
					stateToSet = KeyboardKeyActionState::PressStart;
				}
			}
			break;

			case KeyboardKeyActionState::PressStart:
			{
				// user ended pressing the button
				if (newState == Driver::KeyboardKeyState::NotPressed)
				{
					stateToSet = KeyboardKeyActionState::PressEndShort;
				}
			}
			break;

			case KeyboardKeyActionState::PressEndShort:
			{
				// user ended pressing the button
				if (newState == Driver::KeyboardKeyState::NotPressed)
				{
					stateToSet = KeyboardKeyActionState::PressNot;
				}
			}
			break;

			default:
				break;
			}

			keyActionState[i] = stateToSet;
		}
	}

	KeyboardKeyActionState Keyboard::getState(::Driver::KeyboardKeyId key)
	{
		KeyboardKeyActionState state;

		uint8_t index = static_cast<uint8_t>(key);
		if (index >= AmountOfKeys)
		{
			state = KeyboardKeyActionState::Fail;
		}
		else
		{
			state = keyActionState[index];
		}
		return state;
	}

}
