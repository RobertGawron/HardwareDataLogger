#include "logger_keyboard.h"
//#include "gm_display_updater.h"

void LoggerKeyboard_Init()
{

}


void LoggerKeyboard_OnKeyPressDetection(
		LoggerKeyboardKeys_Key_State_t keyUp,
		LoggerKeyboardKeys_Key_State_t keyDown,
		LoggerKeyboardKeys_Key_State_t keyLeft,
		LoggerKeyboardKeys_Key_State_t keyRight)
{
    //GMDisplayUpdater_ReactOnKeyPress(key);

	// for debug to check if it is executed
	if (keyUp == LOGGER_KEYBOARD_KEY_PRESS)
	{
		volatile int x = 0;
		x++;
	}
}
