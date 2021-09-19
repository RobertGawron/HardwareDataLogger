#include <HMI.h>
#ifdef __cplusplus
extern "C"
{
#endif

//#include "gos.h"

uint_least32_t gfxSystemTicks(void){}
uint_least32_t	 gfxMillisecondsToTicks(uint_least32_t ms){}

#include "gfx.h"

#ifdef __cplusplus
}
#endif

namespace Application
{

HMI::HMI(
			Device::DisplayBacklight &_displayBacklight,
			Device::Keyboard &_keyboard,
			Device::IDisplay &_display
		) :
		displayBacklight(_displayBacklight),
		keyboard(_keyboard),
		display(_display),
		displayBrightnessActual(0),
		prevUp(KeboardKeyState::NotPressed),
		prevDown(KeboardKeyState::NotPressed)
{
}

void HMI::init()
{
	displayBacklight.init();
	keyboard.init();
	display.init();

	gfxInit();

	//displayBacklight.setBrightnessPercentage(displayBrightnessDefault);
}

void HMI::tick()
{
	keyboard.tick();


	// BELOW IS A HORIBLE CODE FOR TEMPORARY TESTING OF BACKLIGHT ADJOUSTMENT
	// IT WILL BE REMOVED IN FINAL VERSION.

	KeboardKeyState currentUp = KeboardKeyState::NotPressed;
	KeboardKeyState currentDown = KeboardKeyState::NotPressed;

	uint16_t ambientLight = displayBacklight.getAmbientLightLevel();
	display.showBacklightConf_ForDebugOnly(ambientLight, displayBrightnessActual);

	currentUp = keyboard.getState(KeboardKeyId::Left);

	if ((currentUp == KeboardKeyState::NotPressed)
			&& (prevUp == KeboardKeyState::Pressed))
	{
		displayBrightnessActual += 1;

		displayBacklight.setBrightnessPercentage(displayBrightnessActual);
		//display.init();

	}

	currentDown = keyboard.getState(KeboardKeyId::Right);

	if ((currentDown == KeboardKeyState::NotPressed)
			&& (prevDown == KeboardKeyState::Pressed))
	{
		displayBrightnessActual -= 20;
		displayBacklight.setBrightnessPercentage(displayBrightnessActual);
		//display.showBacklightConf_ForDebugOnly(ambientLight, displayBrightnessActual);
	}

	prevUp = currentUp;
	prevDown = currentDown;

}

}
