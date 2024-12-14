#include "BusinessLogic/Inc/HmiFactory.hpp"
// #include "Device/Inc/KeyboardKeyActionState.hpp"
#include "Driver/Inc/KeyboardKeyIdentifier.hpp"

// for test of driver lib
#include <stdio.h>

namespace BusinessLogic
{
    // Define fonts/styles and UI elements
    muif_t muif_list[] = {
        MUIF_U8G2_FONT_STYLE(0, u8g2_font_helvR08_tr), /* style 0: small regular font */
        MUIF_U8G2_FONT_STYLE(1, u8g2_font_helvB10_tr), /* style 1: larger bold font for headings */
        MUIF_U8G2_LABEL(),                             /* allow MUI_LABEL command */
        MUIF_BUTTON("BN", mui_u8g2_btn_exit_wm_fi),    /* simple exit button definition */
        MUIF_BUTTON("BG", mui_u8g2_btn_goto_wm_fi),    /* assume a callback to go to a given form */
        //  Add more UI elements or callbacks as needed
    };

    // Define multiple forms
    fds_t fds_data[] =
        /* ----------- Form 1: A list of selectable items ----------- */
        MUI_FORM(1)
            MUI_STYLE(0)
                MUI_LABEL(5, 12, "Select measurement device")
                    MUI_XYT("BN", 30, 25, "Device #1")
                        MUI_XYT("BN", 30, 40, "Device #2")
                            MUI_XYT("BN", 30, 55, "Device #3")

        /* ----------- Form 2: A more complex layout ----------- */
        MUI_FORM(2)
        // Use a larger font style for the heading
        MUI_STYLE(1)
            MUI_LABEL(5, 10, "Complex Layout")
        // Switch back to smaller font for details
        MUI_STYLE(0)
            MUI_LABEL(5, 25, "Choose an Option:")
                MUI_XYT("BN", 64, 35, "Option A")
                    MUI_XYT("BN", 64, 45, "Option B")
                        MUI_XYT("BN", 64, 55, "Option C")

        // A separator or additional label
        MUI_LABEL(5, 70, "Navigation:")
        // Buttons to navigate to other forms (using a goto callback defined in MUIF_BUTTON "BG")
        // For example, pass form ID as a parameter with the string or implement logic in callback
        MUI_XYT("BG", 64, 90, "Go to Form 1")  /* The callback could interpret "Go to Form 1" as MUI_GOTO(1) */
        MUI_XYT("BG", 64, 110, "Go to Form 3") /* Similarly, callback sends user to Form 3 */

        /* ----------- Form 3: Another simple form ----------- */
        MUI_FORM(3)
            MUI_STYLE(0)
                MUI_LABEL(5, 15, "You are on Form 3")
                    MUI_XYT("BG", 64, 30, "Go Back") /* A button that returns to Form 1, again handled by callback */

        ; // end of fds_data array

    HmiMui::HmiMui(Device::IDisplay &_display,
                   Device::IDisplayBrightnessRegulator &_displayBrightnessRegulator,
                   Device::IKeyboard &_keyboard) : display(_display),
                                                   displayBrightnessRegulator(_displayBrightnessRegulator),
                                                   keyboard(_keyboard),
                                                   IHmi(_display,
                                                        _displayBrightnessRegulator,
                                                        _keyboard)
    {
    }

    bool HmiMui::initialize()
    {
        /*
        volatile int x = 0;
        // display.initialize();

        // for tests
        auto color = Driver::DisplayPixelColor::getColor(0x2f, 0xff, 0xff);
        // display.drawHorizontalLine(1, 1, 20, color);
        printf("hello drawHorizontalLine\n");
        */
        keyboard.init();
        displayBrightnessRegulator.init();

        display.initialize();

        return true;
    }

    bool HmiMui::start()
    {
        printf("START %s %d\n", __FILE__, __LINE__);

        display.begin(/* menu_select_pin= */ 5, /* menu_next_pin= */ 4, /* menu_prev_pin= */ 2, /* menu_up_pin= */ U8X8_PIN_NONE, /* menu_down_pin= */ U8X8_PIN_NONE, /* menu_home_pin= */ 3);

        mui.begin(display, fds_data, muif_list, sizeof(muif_list) / sizeof(muif_t));
        mui.gotoForm(/* form_id= */ 1, /* initial_cursor_position= */ 0);
        display.firstPage();
        display.setCursor(0, 0);

        do
        {
            mui.draw();
        } while (display.nextPage());

        return true;
    }

    bool HmiMui::tick()
    {
        keyboard.tick();
        displayBrightnessRegulator.tick();

        /*
        Maping between MUI and hw pins:

        menu_select_pin = right
        menu_next_pin   = down
        menu_prev_pin   = up
        menu_home_pin   = left
        */

        if ((keyboard.getKeyState(Driver::KeyboardKeyIdentifier::Up) == Device::KeyboardKeyActionState::PressEndShort) || (keyboard.getKeyState(Driver::KeyboardKeyIdentifier::Up) == Device::KeyboardKeyActionState::PressEndLong))
        {
            mui.prevField();
        }

        if ((keyboard.getKeyState(Driver::KeyboardKeyIdentifier::Down) == Device::KeyboardKeyActionState::PressEndShort) || (keyboard.getKeyState(Driver::KeyboardKeyIdentifier::Down) == Device::KeyboardKeyActionState::PressEndLong))
        {
            mui.nextField();
        }

        if ((keyboard.getKeyState(Driver::KeyboardKeyIdentifier::Left) == Device::KeyboardKeyActionState::PressEndShort) || (keyboard.getKeyState(Driver::KeyboardKeyIdentifier::Left) == Device::KeyboardKeyActionState::PressEndLong))
        {
            mui.leaveForm();
        }

        if ((keyboard.getKeyState(Driver::KeyboardKeyIdentifier::Right) == Device::KeyboardKeyActionState::PressEndShort) || (keyboard.getKeyState(Driver::KeyboardKeyIdentifier::Right) == Device::KeyboardKeyActionState::PressEndLong))
        {
            mui.sendSelect();
        }

        // display.clear();
        // mui.gotoForm(2, 0);
        // mui.nextField();
        // mui.sendSelect();
        display.clear();
        do
        {
            mui.draw();
        } while (display.nextPage());

        /*    printf("key state: %d %d %d %d\n",
                   keyboard.getKeyState(Driver::KeyboardKeyIdentifier::Up),
                   keyboard.getKeyState(Driver::KeyboardKeyIdentifier::Down),
                   keyboard.getKeyState(Driver::KeyboardKeyIdentifier::Left),
                   keyboard.getKeyState(Driver::KeyboardKeyIdentifier::Right));
          */
        return true;
    }

}