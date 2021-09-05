#ifndef LOGGER_KEYBOARD_H_
#define LOGGER_KEYBOARD_H_

#include <logger_keyboard_key_state.h>

void LoggerKeyboard_Init();
void LoggerKeyboard_OnKeyPressDetection(
    LoggerKeyboardKeys_Key_State_t keyUp,
    LoggerKeyboardKeys_Key_State_t keyDown,
    LoggerKeyboardKeys_Key_State_t keyLeft,
    LoggerKeyboardKeys_Key_State_t keyRight);

#endif
