#include "HMI.h"

#ifdef __cplusplus
extern "C"
{
#endif

//#include "gfx.h"

#ifdef __cplusplus
}
#endif

namespace BusinessLogic
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
    prevUp(::Driver::KeboardKeyState::NotPressed),
    prevDown(::Driver::KeboardKeyState::NotPressed)
{
}

void HMI::init()
{
    displayBacklight.init();
    keyboard.init();
    display.init();
/*
    gfxInit();

    gwinSetDefaultFont(gdispOpenFont("UI2"));
    gwinSetDefaultStyle(&WhiteWidgetStyle, FALSE);
    gdispClear(Yellow);

    static GHandle ghLabel1;

    GWidgetInit wi;
    gwinWidgetClearInit(&wi);

    // Apply the label parameters
    wi.g.show = gTrue;
    wi.g.y = 1;
    wi.g.x = 1;
    wi.g.width = 100;
    wi.g.height = 20;
    wi.text = "Label 1";

    // Create the actual label
    ghLabel1 = gwinLabelCreate(NULL, &wi);

    gwinSetText(ghLabel1, "This is some text", gTrue);
*/
    //displayBacklight.setBrightnessPercentage(displayBrightnessDefault);
}

void HMI::tick()
{
    keyboard.tick();

    // BELOW IS A HORIBLE CODE FOR TEMPORARY TESTING OF BACKLIGHT ADJOUSTMENT
    // IT WILL BE REMOVED IN FINAL VERSION.

    ::Driver::KeboardKeyState currentUp = ::Driver::KeboardKeyState::NotPressed;
    ::Driver::KeboardKeyState currentDown = ::Driver::KeboardKeyState::NotPressed;

    uint16_t ambientLight = displayBacklight.getAmbientLightLevel();
    display.showBacklightConf_ForDebugOnly(ambientLight, displayBrightnessActual);

    currentUp = keyboard.getState(::Driver::KeboardKeyId::Left);

    if ((currentUp == ::Driver::KeboardKeyState::NotPressed)
        && (prevUp == ::Driver::KeboardKeyState::Pressed))
    {
        displayBrightnessActual += 1;

        displayBacklight.setBrightnessPercentage(displayBrightnessActual);
        //display.init();

    }

    currentDown = keyboard.getState(::Driver::KeboardKeyId::Right);

    if ((currentDown == ::Driver::KeboardKeyState::NotPressed)
        && (prevDown == ::Driver::KeboardKeyState::Pressed))
    {
        displayBrightnessActual -= 20;
        displayBacklight.setBrightnessPercentage(displayBrightnessActual);
        //display.showBacklightConf_ForDebugOnly(ambientLight, displayBrightnessActual);
    }

    prevUp = currentUp;
    prevDown = currentDown;

}

}
