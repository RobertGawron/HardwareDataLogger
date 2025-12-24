#include "BusinessLogic/Inc/HmiMui.hpp"
#include "BusinessLogic/Inc/HmiMuiHandlers.hpp"
#include "BusinessLogic/Inc/HmiMeasurementModel.hpp"
#include "Device/Interface/IDisplay.hpp"
#include "Device/Interface/IDisplayBrightnessRegulator.hpp"
#include "Device/Interface/IKeyboard.hpp"
#include "Device/Inc/KeyboardKeyActionState.hpp"
#include "Driver/Interface/KeyboardKeyIdentifier.hpp"

#include "mui.h"
#include "u8g2.h"
#include "mui_u8g2.h"

// #include <iostream>

namespace BusinessLogic
{

// Can't fix, MUI related implementation.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"
#pragma clang diagnostic ignored "-Wold-style-cast"

    // Define fonts/styles and UI elements
    muif_t muif_list[] = {
        MUIF_U8G2_FONT_STYLE(0, u8g2_font_helvR08_tr), /* style 0: small regular font */
        MUIF_U8G2_FONT_STYLE(1, u8g2_font_helvB10_tr), /* style 1: larger bold font for headings */
        MUIF_U8G2_LABEL(),                             /* allow MUI_LABEL command */
        MUIF_BUTTON("BN", mui_u8g2_btn_exit_wm_fi),    /* simple exit button definition */
        MUIF_BUTTON("BG", mui_u8g2_btn_goto_wm_fi),    /* assume a callback to go to a given form */
                                                       //  {"DL", mui_dynamic_label_handler},             /* Custom handler for dynamic labels */
                                                       //        MUIF_LABEL(mui_u8g2_draw_text)
        MUIF_RO("CT", device1_printLastReading),

        //  Add more UI elements or callbacks as needed
    };

    // Define multiple forms
    fds_t fds_data[] =
        /* ----------- Form 1: A list of selectable items ----------- */
        MUI_FORM(1)
            MUI_STYLE(0)
                MUI_LABEL(5, 12, "Layout Name")
                    MUI_LABEL(5, 25, "Devices readings:")
                        MUI_LABEL(20, 40, "Device #1")
                            MUI_XY("CT", 80, 40)
                                MUI_LABEL(20, 55, "Device #2")
                                    MUI_LABEL(20, 70, "Device #3")

        //   MUI_XY("CT", 50, 24)

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

#pragma clang diagnostic pop

    HmiMui::HmiMui(HmiMeasurementModel &_hmiMeasurementModel,
                   Device::IDisplay &_display,
                   Device::IDisplayBrightnessRegulator &_displayBrightnessRegulator,
                   Device::IKeyboard &_keyboard) : hmiMeasurementModel(_hmiMeasurementModel),
                                                   display(_display),
                                                   displayBrightnessRegulator(_displayBrightnessRegulator),
                                                   keyboard(_keyboard)
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
#if 0
        display.begin();

        mui.begin(display, fds_data, muif_list, sizeof(muif_list) / sizeof(muif_t));

        registerMuiToItsObjects(mui.getMUI(), &display, &hmiMeasurementModel);

        mui.gotoForm(/* form_id= */ 1, /* initial_cursor_position= */ 0);
        display.firstPage();
        display.setCursor(0, 0);
        // #endif

        do
        {
            mui.draw();
        } while (display.nextPage() > 0u);

        return true;
#endif
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
        /*
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
        */
        /*   display.clear();
           mui.gotoForm(2, 0);
           mui.nextField();
           mui.sendSelect();
           display.clear();
          */

        if (
            (keyboard.getKeyState(Driver::KeyboardKeyIdentifier::Up) == Device::KeyboardKeyActionState::PressEndShort) || (keyboard.getKeyState(Driver::KeyboardKeyIdentifier::Up) == Device::KeyboardKeyActionState::PressEndLong) || (keyboard.getKeyState(Driver::KeyboardKeyIdentifier::Down) == Device::KeyboardKeyActionState::PressEndShort) || (keyboard.getKeyState(Driver::KeyboardKeyIdentifier::Down) == Device::KeyboardKeyActionState::PressEndLong) || (keyboard.getKeyState(Driver::KeyboardKeyIdentifier::Left) == Device::KeyboardKeyActionState::PressEndShort) || (keyboard.getKeyState(Driver::KeyboardKeyIdentifier::Left) == Device::KeyboardKeyActionState::PressEndLong) || (keyboard.getKeyState(Driver::KeyboardKeyIdentifier::Right) == Device::KeyboardKeyActionState::PressEndShort) || (keyboard.getKeyState(Driver::KeyboardKeyIdentifier::Right) == Device::KeyboardKeyActionState::PressEndLong))
        {

        /*   display.clear();
           do
           {
               mui.draw();
           } while (display.nextPage() > 0u);
      */ }

        static int i = 0;
        i++;
        if (i == 100)
        {
            if (mui.isFormActive())
            {
                i = 0;

                display.clear();
                do
                {
                    //   std::cout << "==============================================> redraw" << std::endl;
                    mui.draw();
                } while (display.nextPage() > 0u);
            }
        }

        /*    printf("key state: %d %d %d %d\n",
                   keyboard.getKeyState(Driver::KeyboardKeyIdentifier::Up),
                   keyboard.getKeyState(Driver::KeyboardKeyIdentifier::Down),
                   keyboard.getKeyState(Driver::KeyboardKeyIdentifier::Left),
                   keyboard.getKeyState(Driver::KeyboardKeyIdentifier::Right));
          */
        return true;
    }

}
