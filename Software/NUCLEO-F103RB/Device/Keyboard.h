#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "KeboardKeyState.h"
#include "KeboardKeyId.h"


namespace Device
{

class Keyboard
{
public:
	Keyboard();
	virtual ~Keyboard();
	void tick();
	KeboardKeyState getState(KeboardKeyId key);
private:
	KeboardKeyState	keyUp;
	KeboardKeyState	keyDown;
	KeboardKeyState	keyLeft;
	KeboardKeyState	keyRight;

};

}

#endif
