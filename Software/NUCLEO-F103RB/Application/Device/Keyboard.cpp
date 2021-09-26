#include <Keyboard.h>

namespace Device
{

Keyboard::Keyboard(::Driver::IKeyboardKeysDriver& _keyboardKeysDriver) :
	keyboardKeysDriver(_keyboardKeysDriver),
	keyUp(::Driver::KeboardKeyState::NotPressed), keyDown(
	::Driver::KeboardKeyState::NotPressed), keyLeft(
	::Driver::KeboardKeyState::NotPressed), keyRight(
	::Driver::KeboardKeyState::NotPressed)
{
}

void Keyboard::init()
{
	keyboardKeysDriver.init();
}

void Keyboard::tick()
{
	keyboardKeysDriver.tick();
}

::Driver::KeboardKeyState Keyboard::getState(::Driver::KeboardKeyId key)
{
	::Driver::KeboardKeyState state;
	state = keyboardKeysDriver.getState(key);
    return state;
}

}
